#include <taiga.h>

static FILE*  out;
static int    indent	 = 0;
static int    mode	 = 0;
static char*  title	 = NULL;
static int    in_title	 = 0;
static int    in_section = 0;
static int    in_message = 0;
static int in_pre = 0;
static char** mapping;
static int    mapping_len;
static char*  argin    = NULL;
static char*  argout   = NULL;
static char*  argbase  = NULL;
static char*  argbase2 = NULL;

static void setup_parser(MD_PARSER* parser);

static void print_indent(void) {
	int i;

	for(i = 0; i < indent; i++) fprintf(out, "\t");
}

static char* encode(const char* str, int len) {
	int   actlen = (len == -1 ? strlen(str) : len);
	char* r	     = malloc(actlen * 5 + 1);
	int   n	     = 0;
	int   i;

	for(i = 0; i < actlen; i++) {
		if(str[i] == '<') {
			r[n++] = '&';
			r[n++] = 'l';
			r[n++] = 't';
			r[n++] = ';';
		} else if(str[i] == '>') {
			r[n++] = '&';
			r[n++] = 'g';
			r[n++] = 't';
			r[n++] = ';';
		} else if(str[i] == '&') {
			r[n++] = '&';
			r[n++] = 'a';
			r[n++] = 'm';
			r[n++] = 'p';
			r[n++] = ';';
		} else {
			r[n++] = str[i];
		}
	}
	r[n] = 0;

	return r;
}

static int enter_block(MD_BLOCKTYPE type, void* detail, void* user) {
	if(mode == 0 && type == MD_BLOCK_H && ((MD_BLOCK_H_DETAIL*)detail)->level == 1 && title == NULL) {
		in_title = 1;
	}

	if(!mode) return 0;

	if(type == MD_BLOCK_H) {
		MD_BLOCK_H_DETAIL* det = detail;

		if(det->level <= 2) {
			if(title != NULL) free(title);
			title = NULL;

			in_title = 1;
		} else {
			print_indent();
			fprintf(out, "<h%d>\n", det->level);
			indent++;
		}
	} else if(type == MD_BLOCK_P) {
		print_indent();
		fprintf(out, "<p>\n");
		indent++;
	} else if(type == MD_BLOCK_UL) {
		print_indent();
		fprintf(out, "<ul>\n");
		indent++;
	} else if(type == MD_BLOCK_OL) {
		print_indent();
		fprintf(out, "<ol>\n");
		indent++;
	} else if(type == MD_BLOCK_LI) {
		print_indent();
		fprintf(out, "<li>\n");
		indent++;
	} else if(type == MD_BLOCK_HR) {
		print_indent();
		fprintf(out, "<hr>\n");
		indent++;
	} else if(type == MD_BLOCK_CODE) {
		MD_BLOCK_CODE_DETAIL* det = detail;
		char		      lang[2048];

		memcpy(lang, det->lang.text, det->lang.size);
		lang[det->lang.size] = 0;

		if(strcmp(lang, "warn") == 0) {
			print_indent();
			fprintf(out, "<warning>\n");
			indent++;

			in_message = 1;
		} else if(strcmp(lang, "note") == 0) {
			print_indent();
			fprintf(out, "<note>\n");
			indent++;

			in_message = 1;
		} else {
			print_indent();
			fprintf(out, "<pre>");
			fprintf(out, "<code>");

			in_pre = 1;
		}
	} else if(type == MD_BLOCK_TABLE) {
		print_indent();
		fprintf(out, "<table>\n");
		indent++;
	} else if(type == MD_BLOCK_TR) {
		print_indent();
		fprintf(out, "<tr>\n");
		indent++;
	} else if(type == MD_BLOCK_TH) {
		print_indent();
		fprintf(out, "<th>\n");
		indent++;
	} else if(type == MD_BLOCK_TD) {
		print_indent();
		fprintf(out, "<td>\n");
		indent++;
	} else if(type == MD_BLOCK_QUOTE) {
		print_indent();
		fprintf(out, "<blockquote>\n");
		indent++;
	}
	return 0;
}

static int leave_block(MD_BLOCKTYPE type, void* detail, void* user) {
	if(mode == 0 && type == MD_BLOCK_H && ((MD_BLOCK_H_DETAIL*)detail)->level == 1 && in_title) {
		in_title = 0;
	}

	if(!mode) return 0;

	if(type == MD_BLOCK_H) {
		MD_BLOCK_H_DETAIL* det = detail;

		in_title = 0;

		if(det->level == 2) {
			char* buf;

			if(in_section) {
				indent--;
				print_indent();
				fprintf(out, "</section>\n");
			}

			buf = encode(title == NULL ? "" : title, -1);

			print_indent();
			fprintf(out, "<section title=\"%s\">\n", buf);
			indent++;

			in_section = 1;

			free(buf);
		} else if(det->level != 1) {
			indent--;
			print_indent();
			fprintf(out, "</h%d>\n", det->level);
		}
	} else if(type == MD_BLOCK_P) {
		indent--;
		print_indent();
		fprintf(out, "</p>\n");
	} else if(type == MD_BLOCK_UL) {
		indent--;
		print_indent();
		fprintf(out, "</ul>\n");
	} else if(type == MD_BLOCK_OL) {
		indent--;
		print_indent();
		fprintf(out, "</ol>\n");
	} else if(type == MD_BLOCK_LI) {
		indent--;
		print_indent();
		fprintf(out, "</li>\n");
	} else if(type == MD_BLOCK_CODE) {
		MD_BLOCK_CODE_DETAIL* det = detail;
		char		      lang[2048];

		memcpy(lang, det->lang.text, det->lang.size);
		lang[det->lang.size] = 0;

		if(strcmp(lang, "warn") == 0) {
			indent--;
			print_indent();
			fprintf(out, "</warning>\n");

			in_message = 0;
		} else if(strcmp(lang, "note") == 0) {
			indent--;
			print_indent();
			fprintf(out, "</note>\n");

			in_message = 0;
		} else {
			in_pre = 0;

			fprintf(out, "</code></pre>\n");
		}
	} else if(type == MD_BLOCK_TABLE) {
		indent--;
		print_indent();
		fprintf(out, "</table>\n");
	} else if(type == MD_BLOCK_TR) {
		indent--;
		print_indent();
		fprintf(out, "</tr>\n");
	} else if(type == MD_BLOCK_TH) {
		indent--;
		print_indent();
		fprintf(out, "</th>\n");
	} else if(type == MD_BLOCK_TD) {
		indent--;
		print_indent();
		fprintf(out, "</td>\n");
	} else if(type == MD_BLOCK_QUOTE) {
		indent--;
		print_indent();
		fprintf(out, "</blockquote>\n");
	}

	return 0;
}

static int enter_span(MD_SPANTYPE type, void* detail, void* user) {
	if(!mode) return 0;

	if(type == MD_SPAN_EM) {
		print_indent();
		fprintf(out, "<em>\n");
		indent++;
	} else if(type == MD_SPAN_STRONG) {
		print_indent();
		fprintf(out, "<strong>\n");
		indent++;
	} else if(type == MD_SPAN_A) {
		MD_SPAN_A_DETAIL* det	  = detail;
		char*		  href	  = encode(det->href.text, det->href.size);
		char*		  href_wd = href;
		int		  i;
		char*		  str;

		while((str = strstr(href_wd, "./")) == href_wd) href_wd += 2;

		if(strstr(href_wd, "://") == NULL) {
			for(i = 0; i < mapping_len; i++) {
				char* key   = u_strdup(mapping[i]);
				char* value = strchr(key, '=');
				char* path_abs;
				char* href_abs;

				if(value != NULL) {
					value[0] = 0;
					value++;
				}

				path_abs = u_path_combine(argbase, key);

				if(href_wd[0] == '/') {
					href_abs = u_path_combine(argbase, href_wd);
				} else {
					href_abs = u_path_combine(argbase2, href_wd);
				}

				if(value != NULL && strcmp(path_abs, href_abs) == 0) {
					free(path_abs);
					free(href_abs);
					free(href);
					href = encode(value, -1);
					free(key);
					break;
				}
				free(path_abs);
				free(href_abs);

				free(key);
			}
		}

		print_indent();
		fprintf(out, "<a href=\"%s\">\n", href);
		indent++;

		free(href);
	} else if(type == MD_SPAN_IMG) {
		MD_SPAN_IMG_DETAIL* det = detail;
		char*		    src = encode(det->src.text, det->src.size);

		print_indent();
		fprintf(out, "<img src=\"%s\" alt=\"", src);

		in_title = 1;
		if(title != NULL) free(title);
		title = NULL;

		free(src);
	} else if(type == MD_SPAN_CODE) {
		print_indent();
		fprintf(out, "<code>\n");
		indent++;
	} else if(type == MD_SPAN_DEL) {
		print_indent();
		fprintf(out, "<del>\n");
		indent++;
	} else if(type == MD_SPAN_U) {
		print_indent();
		fprintf(out, "<u>\n");
		indent++;
	}

	return 0;
}

static int leave_span(MD_SPANTYPE type, void* detail, void* user) {
	if(!mode) return 0;

	if(type == MD_SPAN_EM) {
		indent--;
		print_indent();
		fprintf(out, "</em>\n");
	} else if(type == MD_SPAN_STRONG) {
		indent--;
		print_indent();
		fprintf(out, "</strong>\n");
	} else if(type == MD_SPAN_A) {
		indent--;
		print_indent();
		fprintf(out, "</a>\n");
	} else if(type == MD_SPAN_IMG) {
		char* buf = encode(title, -1);

		fprintf(out, "%s\" />\n", buf);
		free(buf);

		in_title = 0;
	} else if(type == MD_SPAN_CODE) {
		indent--;
		print_indent();
		fprintf(out, "</code>\n");
	} else if(type == MD_SPAN_DEL) {
		indent--;
		print_indent();
		fprintf(out, "</del>\n");
	} else if(type == MD_SPAN_U) {
		indent--;
		print_indent();
		fprintf(out, "</u>\n");
	}

	return 0;
}

static int text(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* user) {
	if(in_title && (type == MD_TEXT_NORMAL || type == MD_TEXT_ENTITY || type == MD_TEXT_CODE)) {
		if(title == NULL) {
			title = malloc(size + 1);

			memcpy(title, text, size);
			title[size] = 0;
		} else {
			char* old = title;
			char* buf = malloc(size + 1);

			memcpy(buf, text, size);
			buf[size] = 0;

			title = u_strvacat(old, " ", buf, NULL);
			free(old);

			free(buf);
		}
	}

	if(!mode) return 0;

	if(in_title) return 0;

	if(type == MD_TEXT_BR) {
		print_indent();
		fprintf(out, "<br />\n");
	} else if(type == MD_TEXT_NORMAL || type == MD_TEXT_ENTITY || type == MD_TEXT_CODE) {
		if(in_message) {
			MD_PARSER parser;
			int	  s;

			setup_parser(&parser);

			in_message = 0;
			s	   = md_parse(text, size, &parser, NULL);
			in_message = 1;

			return s;
		} else {
			char* buf;

			if(!in_pre) print_indent();

			buf = encode(text, size);
			fwrite(buf, 1, strlen(buf), out);
			free(buf);

			if(!in_pre) fprintf(out, "\n");
		}
	}

	return 0;
}

static void setup_parser(MD_PARSER* parser) {
	memset(parser, 0, sizeof(*parser));
	parser->flags	    = MD_FLAG_COLLAPSEWHITESPACE | MD_FLAG_TABLES | MD_FLAG_STRIKETHROUGH | MD_FLAG_UNDERLINE;
	parser->enter_block = enter_block;
	parser->leave_block = leave_block;
	parser->enter_span  = enter_span;
	parser->leave_span  = leave_span;
	parser->text	    = text;
}

int action_markdown(int argc, char** argv) {
	FILE*	  f;
	char*	  buffer;
	int	  size;
	MD_PARSER parser;
	int	  i;
	char*	  s;

	setup_parser(&parser);

	argin	    = NULL;
	argout	    = NULL;
	argbase	    = NULL;
	mapping	    = NULL;
	mapping_len = 0;
	for(i = 0; i < argc; i++) {
		if(argin == NULL) {
			argin = argv[i];
		} else if(argout == NULL) {
			argout = argv[i];
		} else if(argbase == NULL) {
			argbase = argv[i];
		} else if(mapping == NULL) {
			mapping	    = &argv[i];
			mapping_len = argc - i;
		}
	}

	if(argin == NULL || argout == NULL) {
		fprintf(stderr, "Usage: markdown input output [base [linksrc=linkdest ...]]\n");
		return 1;
	}

	if(argbase2 != NULL) free(argbase2);
	argbase2 = u_strdup(argin);

	if((s = strrchr(argbase2, '/')) != NULL) s[0] = 0;

	if((f = fopen(argin, "r")) == NULL) {
		fprintf(stderr, "Failed to open input\n");
		return 1;
	}

	if((out = fopen(argout, "w")) == NULL) {
		fprintf(stderr, "Failed to open output\n");
		return 1;
	}

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);

	buffer = malloc(size);
	fread(buffer, 1, size, f);
	fclose(f);

	fprintf(out, "<document>\n");
	indent++;

	in_title   = 0;
	in_section = 0;
	in_message = 0;
	in_pre = 0;
	mode	   = 0;
	if(md_parse(buffer, size, &parser, NULL)) {
		free(buffer);
		fclose(out);
		remove(argout);
		fprintf(stderr, "Failed to parse Markdown\n");
		return 1;
	}

	fprintf(out, "	<header>\n");
	indent++;
	if(title != NULL) fprintf(out, "		<title>%s</title>\n", title);
	fprintf(out, "	</header>\n");
	indent--;

	fprintf(out, "	<body>\n");
	indent++;

	in_title   = 0;
	in_section = 0;
	in_message = 0;
	in_pre = 0;
	mode	   = 1;
	if(md_parse(buffer, size, &parser, NULL)) {
		free(buffer);
		fclose(out);
		remove(argout);
		fprintf(stderr, "Failed to parse Markdown\n");
		return 1;
	}

	if(in_section) {
		indent--;
		print_indent();
		fprintf(out, "</section>\n");
	}

	fprintf(out, "	</body>\n");
	indent--;
	fprintf(out, "</document>\n");
	indent--;

	if(title != NULL) free(title);
	title = NULL;

	free(buffer);

	fclose(out);

	return 0;
}
