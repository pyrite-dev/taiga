#include <taiga.h>

void process(const char* out, const char* full){
	char* f = strrchr(full, '/');

	if(f != NULL) f = f + 1;

	if(f != NULL){
		char* n;

		f = u_strdup(f);
		if((n = strrchr(f, '.')) != NULL) n[0] = 0;

		free(f);
	}
}
