#include <taiga.h>

static const char* inp;
static const char* oup;

typedef struct stringkv {
	char* key;
	char* value;
} stringkv_t;

static stringkv_t* paths = NULL;

#define IS_INDEX(x) (strcmp((x), "README.md") == 0)

static void populate(const char* path) {
	char*	in = u_strvacat(inp, "/", path, NULL);
	IO_DIR* dir;

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
					char* p2 = u_strvacat(path, d->d_name, "/", NULL);
					populate(p2);
					free(p2);
				} else if(is_md) {
					char* p2 = u_strvacat(path, d->d_name, NULL);
					char* pathv;

					if(IS_INDEX(d->d_name)) {
						pathv = u_strdup(path);
					} else {
						char* n = u_strdup(d->d_name);
						char* str;
						if((str = strchr(n, '.')) != NULL) str[0] = 0;

						pathv = u_strvacat(path, n, "/", NULL);

						free(n);
					}
					shput(paths, p2, pathv);

					free(p2);
				}
			}
			free(p);
		}
	}
}

static int scan(const char* top, const char* path) {
	char*	in  = u_strvacat(inp, "/", path, NULL);
	char*	out = u_strvacat(oup, path, NULL);
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
					char* p2 = u_strvacat(path, d->d_name, "/", NULL);
					char* o	 = u_strvacat(out, d->d_name, NULL);
					char* t	 = u_strvacat(top, "../", NULL);

					io_mkdir(o, 0755);
					free(o);
					if(!scan(t, p2)) {
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
				} else if(is_md) {
					char** argv = NULL;
					char*  o    = NULL;
					int    i;

					printf("%s:\n", p);

					arrput(argv, p);
					if(IS_INDEX(d->d_name)) {
						o = u_strvacat(out, "index.xml", NULL);
					} else {
						char* n = u_strdup(d->d_name);
						char* str;
						char* pathd;
						if((str = strchr(n, '.')) != NULL) str[0] = 0;

						pathd = u_strvacat(out, n, NULL);
						o     = u_strvacat(pathd, "/index.xml", NULL);
						io_mkdir(pathd, 0755);
						free(pathd);

						free(n);
					}

					arrput(argv, o);
					arrput(argv, (char*)inp);

					for(i = 0; i < shlen(paths); i++) {
						char* t;
						char* v;

						if(IS_INDEX(d->d_name)) {
							t = u_strdup(top);
						} else {
							t = u_strvacat(top, "../", NULL);
						}

						v = u_strvacat(paths[i].key, "=", t, paths[i].value, NULL);
						arrput(argv, v);

						free(t);
					}

					if(action_markdown(arrlen(argv), argv)) {
						for(i = 3; i < arrlen(argv); i++) free(argv[i]);
						free(o);
						arrfree(argv);
						free(p);
						io_closedir(dir);
						free(out);
						free(in);
						return 0;
					}
					free(o);
					for(i = 3; i < arrlen(argv); i++) free(argv[i]);
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
	int i;
	if(argc < 1) {
		fprintf(stderr, "Usage: markdown-dir input [output]\n");

		return 1;
	}

	inp = argv[0];
	oup = (argc >= 2) ? argv[1] : "site/content/";

	paths = NULL;
	sh_new_strdup(paths);

	populate("");

	if(!scan("", "")) {
		for(i = 0; i < shlen(paths); i++) free(paths[i].value);
		shfree(paths);
		return 1;
	}

	for(i = 0; i < shlen(paths); i++) free(paths[i].value);
	shfree(paths);

	return 0;
}
