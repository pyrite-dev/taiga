#include <taiga.h>

int action_help(int argc, char** argv) {
	printf("Actions:\n");
	printf("  help     Show this help\n");
	printf("  seed     Creates a new website\n");
	printf("  site     Builds an website (default action)\n");
	return 0;
}
