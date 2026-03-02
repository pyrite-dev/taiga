#include <taiga.h>

#include "image/fill.h"
#include "image/valid-html401.h"
#include "image/valid-css.h"
#include "image/fixme.h"
#include "image/warning.h"
#include "image/note.h"
#include "image/logo1.h"
#include "image/logo2.h"

static void describe(const char* path, const char* what) {
	char space[64];
	int  i;

	memset(space, 0, sizeof(space));
	for(i = 0; i < (48 - strlen(path)); i++) space[i] = ' ';

	printf("%s%s# %s\n", path, space, what);
}

#define IMAGE(token, path) \
	if((f = fopen("site/content/image/" path, "wb")) == NULL) { \
		fprintf(stderr, "Failed to open site/content/image/%s\n", path); \
		return 1; \
	} \
	fwrite(image_##token, 1, image_##token##_len, f); \
	fclose(f);

int action_seed(int argc, char** argv) {
	FILE* f;

	io_mkdir("site", 0755);
	io_mkdir("site/content", 0755);
	io_mkdir("site/content/image", 0755);

	IMAGE(fill, "fill.gif");
	IMAGE(valid_html401, "valid-html401.png");
	IMAGE(valid_css, "valid-css.png");
	IMAGE(fixme, "fixme.png");
	IMAGE(warning, "warning.png");
	IMAGE(note, "note.png");
	IMAGE(logo1, "group-logo.png");
	IMAGE(logo2, "project-logo.png");

	if((f = fopen("site/skinconf.xml", "w")) == NULL) {
		fprintf(stderr, "Failed to open site/skinconf.xml\n");
		return 1;
	}
	fprintf(f, "<?xml version=\"1.0\"?>\n");
	fprintf(f, "<!--\n");
	fprintf(f, "	NOTE!\n");
	fprintf(f, "	  - Relative path in this config is relative to site/content\n");
	fprintf(f, "	  - If relative path starts from ./ or ../, it's relative to URL when accessed\n");
	fprintf(f, "-->\n");
	fprintf(f, "<skinconfig>\n");
	fprintf(f, "	<search domain=\"example.com\" />\n");
	fprintf(f, "	<breadcrumb>\n");
	fprintf(f, "		<link name=\"Example Co, Ltd\" href=\"https://example.com\" />\n");
	fprintf(f, "		<link name=\"Example Project\" href=\"https://example.com\" />\n");
	fprintf(f, "	</breadcrumb>\n");
	fprintf(f, "	<group>\n");
	fprintf(f, "		<name>Example Co, Ltd</name>\n");
	fprintf(f, "		<description>Example Co, Ltd Description</description>\n");
	fprintf(f, "		<link href=\"https://example.com\" />\n");
	fprintf(f, "		<image src=\"image/group-logo.png\" />\n");
	fprintf(f, "	</group>\n");
	fprintf(f, "	<project>\n");
	fprintf(f, "		<name>Example Project</name>\n");
	fprintf(f, "		<description>Example Project Description</description>\n");
	fprintf(f, "		<link href=\"https://example.com\" />\n");
	fprintf(f, "		<image src=\"image/project-logo.png\" />\n");
	fprintf(f, "	</project>\n");
	fprintf(f, "	<nav>\n");
	fprintf(f, "		<group title=\"Example Project\">\n");
	fprintf(f, "			<link name=\"Home\" href=\"/\" />\n");
	fprintf(f, "			<link name=\"Example Co, Ltd.\" href=\"https://example.com\" />\n");
	fprintf(f, "			<group title=\"Example Project\">\n");
	fprintf(f, "				<link name=\"Home\" href=\"/\" />\n");
	fprintf(f, "				<link name=\"Example Co, Ltd.\" href=\"https://example.com\" />\n");
	fprintf(f, "			</group>\n");
	fprintf(f, "		</group>\n");
	fprintf(f, "	</nav>\n");
	fprintf(f, "	<favicon></favicon>\n");
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
	fprintf(f, "		<title>Welcome to template</title>\n");
	fprintf(f, "	</header>\n");
	fprintf(f, "	<body>\n");
	fprintf(f, "		<fixme>\n");
	fprintf(f, "			Please read this!\n");
	fprintf(f, "		</fixme>\n");
	fprintf(f, "		<warning>\n");
	fprintf(f, "			Please read this!\n");
	fprintf(f, "		</warning>\n");
	fprintf(f, "		<note>\n");
	fprintf(f, "			Please read this!\n");
	fprintf(f, "		</note>\n");
	fprintf(f, "		<section title=\"Congratulations\">\n");
	fprintf(f, "			<p>\n");
	fprintf(f, "				You have successfully generated and rendered a website using Taiga - static website generator.\n");
	fprintf(f, "				This page is from the site template. It is found in <code>site/content/index.xml</code>.\n");
	fprintf(f, "				Please edit it and replace this text with content of your own.\n");
	fprintf(f, "			</p>\n");
	fprintf(f, "		</section>\n");
	fprintf(f, "	</body>\n");
	fprintf(f, "</document>\n");
	fclose(f);

	printf("Template project created!\n");
	printf("\n");
	printf("Here is an outline of the generated files:\n");
	describe("site/skinconf.xml", "Skin configuration");
	describe("site/content/index.xml", "Example index file");
	describe("site/content/image/group-logo.png", "Group logo");
	describe("site/content/image/project-logo.png", "Project logo");

	return 0;
}
