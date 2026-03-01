#include <taiga.h>

static void scan(const char* path){
	char* in = u_strvacat("site/content/", path, NULL);
	char* out = u_strvacat("build/", path, NULL);
	IO_DIR* dir;
	
	if((dir = io_opendir(in)) != NULL){
		struct io_dirent* d;

		while((d = io_readdir(dir)) != NULL){
			char* p;
			struct io_stat s;

			if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) continue;

			p = u_strvacat(in, d->d_name, "/", NULL);
			if(io_stat(p, &s) == 0){
				if(IO_S_ISDIR(s.st_mode)){
					scan(p);
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
