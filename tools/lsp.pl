#!/usr/bin/env perl
# Does this script even work under Windows?

use FindBin;

use lib "$FindBin::Bin/lib";

use FileHandle;
use IPC::Open3;
use JSON;
use Cwd;

my $incr = 1;

sub notify {
	my @args = @_;
	my $hash = {
		jsonrpc => "2.0",
		method => $args[0],
		params => $args[1]
	};
	my $json = JSON->new();
	my $str = $json->encode($hash);
	my $len = 0;

	print(Writer "Content-Length: " . length($str) . "\r\n");
	print(Writer "\r\n");
	print(Writer $str);
}

sub request {
	my @args = @_;
	my $hash = {
		jsonrpc => "2.0",
		id => $incr,
		method => $args[0],
		params => $args[1]
	};
	my $json = JSON->new();
	my $str = $json->encode($hash);
	my $len = 0;

	print(Writer "Content-Length: " . length($str) . "\r\n");
	print(Writer "\r\n");
	print(Writer $str);

	do {
		while(my $l = <Reader>){
			$l =~ s/\r?\n$//;

			if(length($l) == 0){
				last;
			}else{
				$l =~ /^(.+?):[ ]*(.*?)$/;

				if(lc($1) eq "content-length"){
					$len = +$2;
				}
			}
		}

		read Reader, $str, $len;
		$hash = $json->decode($str);
	}while($hash->{id} != $incr);

	$incr += 1;

	return $hash;
}

if(@ARGV < 3){
	print(STDERR "Usage: ./tools/lsp.pl lsp input output [strip_path...]\n");
	exit(1);
}

my $pid = open3(\*Writer, \*Reader, \*Error, $ARGV[0]);
Writer->autoflush();

request("initialize", {
	rootUri => undef,
	capabilities => {
		textDocument => {
			documentSymbol => {
				symbolKind => {
					valueSet => [
						12
					]
				},
				hierarchicalDocumentSymbolSupport => JSON::true,
				labelSupport => JSON::true
			},
			hover => {
				contentFormat => [
					"plaintext"
				]
			}
		}
	}
});

$ARGV[1] =~ /\.(.*)$/;

my $ext = $1;
my $exts = {
	h => "c",
	c => "c",
	cpp => "cpp",
	hpp => "cpp"
};

open(IN, $ARGV[1]);
my $data = do {local $/; <IN>};
close(IN);

open(IN, $ARGV[1]);
my @lines = <IN>;
close(IN);

my $uri = "file://" . Cwd::abs_path($ARGV[1]);

notify("textDocument/didOpen", {
	textDocument => {
		uri => $uri,
		languageId => $exts->{$ext},
		version => 1,
		text => $data
	}
});

sub markdown {
	my @args = @_;
	my $str = escape($args[0]);

	$str =~ s/\*\*\*(.*)\*\*\*/<b><i>\1<\/i><\/b>/g;
	$str =~ s/\*\*(.*)\*\*/<b>\1<\/b>/g;
	$str =~ s/\*(.*)\*/<i>\1<\/i>/g;
	$str =~ s/`(.*)`/<code>\1<\/code>/g;

	if(!(substr($str, length($str) - 1, 1) eq ".")){
		$str = $str . ".";
	}

	return $str;
}

sub get_line {
	my @args = @_;
	my $range = $args[0];

	return substr($lines[$range->{start}->{line}], $range->{start}->{character}, $range->{end}->{character} - $range->{start}->{character});
}

sub escape {
	my @args = @_;
	my $str = $args[0];

	$str =~ s/&/&amp;/g;
	$str =~ s/</&lt;/g;
	$str =~ s/>/&gt;/g;

	return $str;
}

sub directive {
	my @args = @_;
	my $dir = $args[0];

	$dir =~ /^([^ ]+?)(?: +(.*))?$/;

	return ($1, $2);
}

sub recursive {
	my @args = @_;
	my $arr = $args[0];

	foreach my $symbol (@$arr){
		if($symbol->{kind} == 3){
			recursive($symbol->{children});
		}elsif($symbol->{kind} == 12){
			my $json = request("textDocument/hover", {
				textDocument => {
					uri => $uri
				},
				position => $symbol->{selectionRange}->{start}
			});

			if($json->{result} && $json->{result}->{contents}->{value}){
				my $l = $json->{result}->{contents}->{value};

				$l =~ s/\r?\n/\n/g;
				$l =~ s/^[^@].*\n//gm;

				my @dirs = split(/\n/, $l);

				my $c = $l;

				$c =~ s/^/    /gm;

				my $t = 0;
				foreach my $dir (@dirs){
					my ($key, $val) = directive($dir);

					if($key eq "\@param"){
						$t += 1;
					}
				}

				print(OUT "		<section title=\"$symbol->{name}\">\n");

				foreach my $dir (@dirs){
					my ($key, $val) = directive($dir);

					if($key eq "\@brief"){
						print(OUT "			<p>\n");
						print(OUT "				" . markdown($val) . "\n");
						print(OUT "			</p>\n");
					}
				}

				print(OUT "			<table>\n");
				print(OUT "				<tr>\n");
				print(OUT "					<th width=\"100\">\n");
				print(OUT "						Definition\n");
				print(OUT "					</th>\n");
				print(OUT "					<td colspan=\"2\">\n");
				print(OUT "						<code>" . escape(get_line($symbol->{range})) . "</code>\n");
				print(OUT "					</td>\n");
				print(OUT "				</tr>\n");

				$c = 0;
				foreach my $dir (@dirs){
					my ($key, $val) = directive($dir);

					if($key eq "\@param"){
						($key, $val) = directive($val);

						print(OUT "				<tr>\n");
						if($c == 0){
							print(OUT "					<th width=\"100\" rowspan=\"$t\">\n");
							print(OUT "						Parameters\n");
							print(OUT "					</th>\n");
						}
						print(OUT "					<th>\n");
						print(OUT "						$key\n");
						print(OUT "					</th>\n");
						print(OUT "					<td width=\"70%\">\n");
						print(OUT "						" . markdown($val) . "\n");
						print(OUT "					</td>\n");
						print(OUT "				</tr>\n");

						$c += 1;
					}
				}

				foreach my $dir (@dirs){
					my ($key, $val) = directive($dir);

					if($key eq "\@return"){
						print(OUT "				<tr>\n");
						print(OUT "					<th width=\"100\">\n");
						print(OUT "						Return\n");
						print(OUT "					</th>\n");
						print(OUT "					<td colspan=\"2\">\n");
						print(OUT "						" . markdown($val) . "\n");
						print(OUT "					</td>\n");
						print(OUT "				</tr>\n");

						$c += 1;
					}
				}

				print(OUT "			</table>\n");

				foreach my $dir (@dirs){
					my ($key, $val) = directive($dir);

					if(($key eq "\@warning") || ($key eq "\@note")){
						$key = substr($key, 1);

						print(OUT "			<$key>\n");
						print(OUT "				" . markdown($val) . "\n");
						print(OUT "			</$key>\n");
					}
				}

				print(OUT "		</section>\n");
			}
		}
	}
}

my $json = request("textDocument/documentSymbol", {
	textDocument => {
		uri => $uri
	}
});

my $input = $ARGV[1];

for(my $i = 3; $i < @ARGV; $i += 1){
	$input =~ s/^\Q$ARGV[$i]\E\/?//;
}

open(OUT, ">", $ARGV[2]);
print(OUT "<?xml version=\"1.0\"?>\n");
print(OUT "<document>\n");
print(OUT "	<header>\n");
print(OUT "		<title>Documentation of $input</title>\n");
print(OUT "	</header>\n");
print(OUT "	<body>\n");

recursive($json->{result});

print(OUT "	</body>\n");
print(OUT "</document>\n");
close(OUT);

close(Reader);
close(Writer);
close(Error);
waitpid($pid, 0);
