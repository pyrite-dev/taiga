#include <taiga.h>

static void describe(const char* path, const char* what) {
	char space[64];
	int  i;

	memset(space, 0, sizeof(space));
	for(i = 0; i < (32 - strlen(path)); i++) space[i] = ' ';

	printf("%s%s# %s\n", path, space, what);
}

int action_seed(int argc, char** argv) {
	FILE* f;

	io_mkdir("site", 0755);
	io_mkdir("site/content", 0755);

	if((f = fopen("site/skinconf.xml", "w")) == NULL) {
		fprintf(stderr, "Failed to open site/skinconf.xml\n");
		return 1;
	}
	fprintf(f, "<?xml version=\"1.0\"?>\n");
	fprintf(f, "<skinconfig>\n");
	fprintf(f, "	<search domain=\"example.com\" />\n");
	fprintf(f, "	<breadcrumb>\n");
	fprintf(f, "		<link name=\"Example Co, Ltd\" href=\"https://example.com\" />\n");
	fprintf(f, "		<link name=\"Example Project\" href=\"https://example.com\" />\n");
	fprintf(f, "	</breadcrumb>\n");
	fprintf(f, "	<copyright>\n");
	fprintf(f, "		<holder>Example Co, Ltd</holder>\n");
	fprintf(f, "		<year>2026</year>\n");
	fprintf(f, "		<link href=\"https://example.com\" />\n");
	fprintf(f, "	</copyright>\n");
	fprintf(f, "</skinconfig>\n");
	fclose(f);

	if((f = fopen("site/content/index.xml", "w")) == NULL) {
		fprintf(stderr, "Failed to open site/content/index.xml\n");
		return 1;
	}
	fprintf(f, "<?xml version=\"1.0\"?>\n");
	fprintf(f, "<document>\n");
	fprintf(f, "	<header>\n");
	fprintf(f, "		<title><![CDATA[Welcome to template]]></title>\n");
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
