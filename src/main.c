#include <taiga.h>

int main(int argc, char** argv){
	int i;
	char* action = NULL;
	int target_argc = 0;
	char** target_argv = malloc(sizeof(*target_argv));
	target_argv[0] = NULL;

	printf("Taiga, static website generator - run `%s help' for help\n\n", argv[0]);

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

	if(strcmp(action, "site") == 0){
		return action_site(target_argc, target_argv);
	}else if(strcmp(action, "help") == 0){
		return action_help(target_argc, target_argv);
	}else if(strcmp(action, "seed") == 0){
		return action_seed(target_argc, target_argv);
	}

	fprintf(stderr, "Unknown action\n");
	return 1;
}
