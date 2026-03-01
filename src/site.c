#include <taiga.h>

static void scan(const char* path){
	char* in = u_strvacat("site/content/", path, NULL);
	char* out = u_strvacat("build/", path, NULL);
	IO_DIR* dir;
	
	io_mkdir(out, 0755);
	if((dir = io_opendir(in)) != NULL){
		struct io_dirent* d;

		while((d = io_readdir(dir)) != NULL){
			char* p;
			struct io_stat s;

			if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) continue;

			p = u_strvacat(in, d->d_name, NULL);
			if(io_stat(p, &s) == 0){
				if(IO_S_ISDIR(s.st_mode)){
					char* p2 = u_strvacat(d->d_name, "/", NULL);
					scan(p2);
					free(p2);
				}else if(strcmp(d->d_name, "index.xml") == 0){
					process(out, p);
					printf("%s\n", p);
				}
			}
			free(p);
		}

		io_closedir(dir);
	}
	
	free(out);
	free(in);
}

int action_site(int argc, char** argv){
	io_mkdir("build", 0755);

	scan("");

	return 0;
}
