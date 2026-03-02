#include <taiga.h>

#ifdef _WIN32
/* reason why this is included here, is because it makes compilation REALLY slow */
#include <windows.h>

typedef struct io_dir {
	HANDLE		 hFind;
	WIN32_FIND_DATA	 ffd;
	struct io_dirent dirent;
	int		 first;
} io_dir_t;

IO_DIR* io_opendir(const char* path) {
	char*	  p = u_strvacat(path, "/*", NULL);
	io_dir_t* dir;

	dir = malloc(sizeof(*dir));
	if((dir->hFind = FindFirstFile(p, &dir->ffd)) == INVALID_HANDLE_VALUE) {
		free(p);
		free(dir);

		return NULL;
	}
	free(p);
	dir->first = 1;

	return dir;
}

struct io_dirent* io_readdir(IO_DIR* dir) {
	io_dir_t*	  d	 = dir;
	struct io_dirent* dirent = &d->dirent;

	if(d->first) {
		d->first = 0;
	} else if(FindNextFile(d->hFind, &d->ffd) == 0) {
		return NULL;
	}

	strcpy(dirent->d_name, d->ffd.cFileName);
	dirent->d_namlen = strlen(dirent->d_name);

	return dirent;
}

void io_closedir(IO_DIR* dir) {
	io_dir_t* d = dir;

	FindClose(d->hFind);
	free(d);
}
#endif
