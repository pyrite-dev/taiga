#include <taiga.h>

static int scan(const char* inp, const char* path) {
	char*	in  = u_strvacat(inp, "/", path, NULL);
	char*	out = u_strvacat("site/content/", path, NULL);
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
				char* str;
				int   is_md = 0;

				str = strrchr(d->d_name, '.');
				if(str != NULL && strcmp(str, ".md") == 0) is_md = 1;

				if(IO_S_ISDIR(s.st_mode)) {
					char* p2 = u_strvacat(d->d_name, "/", NULL);
					char* o	 = u_strvacat(out, d->d_name, NULL);

					io_mkdir(o, 0755);
					free(o);
					if(!scan(inp, p2)) {
						free(p2);
						free(p);
						io_closedir(dir);
						free(out);
						free(in);

						return 0;
					}
					free(p2);
				} else if(is_md) {
					char** argv = NULL;
					char*  o    = NULL;

					printf("%s:\n", p);

					arrput(argv, p);
					if(strcmp(d->d_name, "README.md") == 0) {
						o = u_strvacat(out, "index.xml", NULL);
					} else {
						char* n = u_strdup(d->d_name);
						char* str;
						char* d;
						if((str = strchr(n, '.')) != NULL) str[0] = 0;

						d = u_strvacat(out, n, NULL);
						o = u_strvacat(d, "/index.xml", NULL);
						io_mkdir(d, 0755);
						free(d);

						free(n);
					}

					if(o != NULL) arrput(argv, o);

					if(action_markdown(arrlen(argv), argv)) {
						free(o);
						arrfree(argv);
						free(p);
						io_closedir(dir);
						free(out);
						free(in);
						return 0;
					}
					free(o);
					arrfree(argv);
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

int action_markdown_dir(int argc, char** argv) {
	if(argc != 1) {
		fprintf(stderr, "Usage: markdown-dir input\n");

		return 1;
	}

	if(!scan(argv[0], "")) {
		return 1;
	}

	return 0;
}
