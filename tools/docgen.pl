#!/usr/bin/env perl

use FindBin;
use File::Path;

if(@ARGV < 3){
	print("Usage ./tools/docgen.pl lsp outdir indir ...\n");
	exit(1);
}

sub scan {
	my @args = @_;
	my $path = $args[0];
	my $top = $args[1];
	my $dirname = $args[2];

	opendir(my $dh, $path);

	my @files = readdir($dh);
	foreach my $file (@files){
		if(($file eq ".") || ($file eq "..")){
			next;
		}

		if(-d "$path/$file"){
			scan("$path/$file", $top, $dirname . $file . "/");
		}else{
			print("$path/$file\n");

			my $dir = "$ARGV[1]/$dirname$file";

			$dir =~ s/\..*$//;

			mkpath($dir);

			system("$FindBin::Bin/lsp.pl \"$ARGV[0]\" \"$path/$file\" \"$dir/index.xml\" \"$top\"\n");
		}
	}

	closedir($dh);
}

for(my $i = 2; $i < @ARGV; $i += 1){
	scan($ARGV[$i], $ARGV[$i], "");
}
