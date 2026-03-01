#include <taiga.h>

static void describe(const char* path, const char* what){
	char space[64];
	int i;

	memset(space, 0, sizeof(space));
	for(i = 0; i < (32 - strlen(path)); i++) space[i] = ' ';

	printf("%s%s# %s\n", path, space, what);
}

int action_seed(int argc, char** argv){
	FILE* f;

	io_mkdir("site", 0755);
	io_mkdir("site/content", 0755);

	if((f = fopen("site/skinconf.xml", "w")) == NULL){
		fprintf(stderr, "Failed to open site/skinconf.xml\n");
		return 1;
	}
	fprintf(f, "<?xml version=\"1.0\"?>\n");
	fprintf(f, "<skinconfig>\n");
	fprintf(f, "	<search domain=\"example.com\" />\n");
	fprintf(f, "	<vendor>Example Co, Ltd.</vendor>\n");
	fprintf(f, "	<year>2026</vendor>\n");
	fprintf(f, "	<copyright-link>https://example.com</copyright-link>\n");
	fprintf(f, "</skinconfig>\n");
	fclose(f);

	if((f = fopen("site/content/index.xml", "w")) == NULL){
		fprintf(stderr, "Failed to open site/content/index.xml\n");
		return 1;
	}
	fprintf(f, "<?xml version=\"1.0\"?>\n");
	fprintf(f, "<document>\n");
	fprintf(f, "	<header>\n");
	fprintf(f, "		<title>Welcome to template</title>\n");
	fprintf(f, "	</header>\n");
	fprintf(f, "	<body>\n");
	fprintf(f, "		<section id=\"status\">\n");
	fprintf(f, "			<title>Congratulations</title>\n");
	fprintf(f, "		</section>\n");
	fprintf(f, "	</body>\n");
	fprintf(f, "</document>\n");
	fclose(f);

	printf("Template project created!\n");
	printf("\n");
	printf("Here is an outline of the generated files:\n");
	describe("site/skinconf.xml", "Skin configuration");
	describe("site/content/index.xml", "Example index file");

	return 0;
}
