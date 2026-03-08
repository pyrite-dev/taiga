#include <taiga.h>

xemil_t* skinconf;
void (*site_stylesheet)(FILE* out, const char* top); /* also create files here if you need one */
void (*site_head)(FILE* out, const char* top, xl_node_t* header);
void (*site_body)(FILE* out, const char* top, const char* title, xl_node_t* body);

static int scan(const char* top, int mode, const char* path) {
	char*	in  = u_strvacat("site/content/", path, NULL);
	char*	out = u_strvacat("build/", path, NULL);
	IO_DIR* dir;

	io_mkdir(out, 0755);
	if((dir = io_opendir(in)) != NULL) {
		struct io_dirent* d;

		while((d = io_readdir(dir)) != NULL) {
			char*	       p;
			struct io_stat s;

			if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) continue;

			p = u_strvacat(in, d->d_name, NULL);
			if(io_stat(p, &s) == 0) {
				if(IO_S_ISDIR(s.st_mode)) {
					char* p2 = u_strvacat(d->d_name, "/", NULL);
					char* t	 = u_strvacat(top, "../", NULL);
					char* o	 = u_strvacat(out, d->d_name, NULL);

					io_mkdir(o, 0755);
					free(o);
					if(!scan(t, mode, p2)) {
						free(t);
						free(p2);
						free(p);
						io_closedir(dir);
						free(out);
						free(in);

						return 0;
					}
					free(t);
					free(p2);
				} else if(mode && strcmp(d->d_name, "index.xml") == 0) {
					printf("%s:\n", p);
					if(!process(top, out, p)) {
						free(p);
						io_closedir(dir);
						free(out);
						free(in);

						return 0;
					}
				} else if(!mode) {
					char* po   = u_strvacat(out, d->d_name, NULL);
					FILE* fin  = fopen(p, "rb");
					FILE* fout = fopen(po, "wb");
					char  buffer[4096];
					int   s;

					while((s = fread(buffer, 1, sizeof(buffer), fin)) != 0) {
						fwrite(buffer, 1, s, fout);
					}

					fclose(fout);
					fclose(fin);
				}
			}
			free(p);
		}

		io_closedir(dir);
	}

	free(out);
	free(in);

	return 1;
}

#define USE_THEME(x) \
	site_stylesheet = x##_stylesheet; \
	site_head	= x##_head; \
	site_body	= x##_body;

int action_site(int argc, char** argv) {
	int	    st = 0;
	FILE*	    css;
	xl_node_t** nodes;

	io_mkdir("build", 0755);

	if((skinconf = xl_open_file("site/skinconf.xml")) == NULL || !xl_parse(skinconf)) {
		fprintf(stderr, "Failed to parse site/skinconf.xml!\n");
		st = 1;
		goto cleanup;
	}

	USE_THEME(classic);
	if((nodes = xl_get_path(skinconf->root, "skin")) != NULL) {
		if(nodes[0]->text != NULL) {
			if(strcmp(nodes[0]->text, "classic") == 0) {
				USE_THEME(classic);
			} else if(strcmp(nodes[0]->text, "simple") == 0) {
				USE_THEME(simple);
			} else {
				fprintf(stderr, "Unknown skin: %s\n", nodes[0]->text);
				st = 1;
				goto cleanup;
			}
		}

		free(nodes);
	}

	if((css = fopen("build/style.css", "w")) == NULL) {
		st = 1;
		goto cleanup;
	}
	site_stylesheet(css, "build/");

	if((nodes = xl_get_path(skinconf->root, "extra-css")) != NULL) {
		if(nodes[0]->text != NULL) {
			fwrite("\n", 1, 1, css);
			fwrite(nodes[0]->text, 1, strlen(nodes[0]->text), css);
		}

		free(nodes);
	}

	fclose(css);

	if(!scan("", 0, "")) {
		st = 1;
		goto cleanup;
	}

	if(!scan("", 1, "")) {
		st = 1;
		goto cleanup;
	}

cleanup:;
	if(skinconf != NULL) xl_close(skinconf);

	if(st == 0) {
		fprintf(stderr, "\nBuild successful\n");
	} else {
		fprintf(stderr, "\nBuild failed!\n");
	}

	return 0;
}
