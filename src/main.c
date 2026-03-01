#include <taiga.h>

int main(int argc, char** argv){
	int i;
	char* action;
	int target_argc = 0;
	char** target_argv = malloc(sizeof(*target_argv));
	target_argv[0] = NULL;

	for(i = 1; i < argc; i++){
		if(argv[i][0] == '-'){
			if(action != NULL) continue;
		}else{
			if(action != NULL) continue;
			action = argv[i];
			
			free(target_argv);
			target_argc = argc - i - 1;
			target_argv = &argv[i + 1];
		}
	}

	if(action == NULL) action = "site";
}
