#include <taiga.h>

void simple_stylesheet(FILE* out, const char* top) {
	char* messages[] = {
	    "fixme",   /**/
	    "warning", /**/
	    "note"     /**/
	};
	int i;

	fprintf(out, "body {\n");
	fprintf(out, "	padding: 0;\n");
	fprintf(out, "	margin: 0;\n");
	fprintf(out, "	background-color: #c0c0c0;\n");
	fprintf(out, "	color: #000000;\n");
	fprintf(out, "	font-family: \"Times New Roman\", Times, serif;\n");
	fprintf(out, "	font-size: 16px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:link {\n");
	fprintf(out, "	color: #0000ee;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:visited {\n");
	fprintf(out, "	color: #551a8b;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:hover {\n");
	fprintf(out, "	color: #ff0000;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#page {\n");
	fprintf(out, "	width: 760px;\n");
	fprintf(out, "	margin: 12px auto;\n");
	fprintf(out, "	background-color: #ffffff;\n");
	fprintf(out, "	border: 2px solid #808080;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#banner {\n");
	fprintf(out, "	background-color: #000080;\n");
	fprintf(out, "	color: #ffffff;\n");
	fprintf(out, "	padding: 12px;\n");
	fprintf(out, "	border-bottom: 2px solid #808080;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "h1, h2, h3, h4, h5, h6, .linkgrouptitle {\n");
	fprintf(out, "	font-family: Arial, Helvetica, sans-serif;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#banner h1, .box h2 {\n");
	fprintf(out, "	margin: 0;\n");
	fprintf(out, "	padding: 0;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#banner p {\n");
	fprintf(out, "	margin-top: 6px;\n");
	fprintf(out, "	margin-bottom: 0;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#nav {\n");
	fprintf(out, "	width: 190px;\n");
	fprintf(out, "	background-color: #dcdcdc;\n");
	fprintf(out, "	border-right: 1px solid #808080;\n");
	fprintf(out, "	padding: 12px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".box {\n");
	fprintf(out, "	margin-bottom: 16px;\n");
	fprintf(out, "	border: 1px solid #808080;\n");
	fprintf(out, "	background-color: #f4f4f4;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".box h2 {\n");
	fprintf(out, "	padding: 6px 8px;\n");
	fprintf(out, "	background-color: #c0c0c0;\n");
	fprintf(out, "	border-bottom: 1px solid #808080;\n");
	fprintf(out, "	font-size: 15px;\n");
	fprintf(out, "\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".box-content {\n");
	fprintf(out, "	margin: 0;\n");
	fprintf(out, "	padding-top: 8px;\n");
	fprintf(out, "	padding-bottom: 18px;\n");
	fprintf(out, "	padding-left: 8px;\n");
	fprintf(out, "	padding-right: 26px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".linkgroup {\n");
	fprintf(out, "	padding-left: 12px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".linkgrouptitle {\n");
	fprintf(out, "	font-weight: bold;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#footer {\n");
	fprintf(out, "	margin-top: 24px;\n");
	fprintf(out, "	padding-top: 8px;\n");
	fprintf(out, "	border-top: 1px solid #808080;\n");
	fprintf(out, "	font-size: 13px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#content {\n");
	fprintf(out, "	padding: 18px;\n");
	fprintf(out, "}\n");
	fprintf(out, ".grid {\n");
	fprintf(out, "	border-collapse: collapse;\n");
	fprintf(out, "	margin-top: 10px 0;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".grid, .grid th, .grid td {\n");
	fprintf(out, "	border: none;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".grid th, .grid td {\n");
	fprintf(out, "	border: 1px solid #808080;\n");
	fprintf(out, "	padding: 6px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".grid th {\n");
	fprintf(out, "	text-align: left;\n");
	fprintf(out, "	background-color: #dcdcdc;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "h1 {\n");
	fprintf(out, "	font-size: 30px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "h2 {\n");
	fprintf(out, "	font-size: 24px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "h3 {\n");
	fprintf(out, "	font-size: 18px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "h4 {\n");
	fprintf(out, "	font-size: 17px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "h5 {\n");
	fprintf(out, "	font-size: 16px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "h6 {\n");
	fprintf(out, "	font-size: 16px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".section {\n");
	fprintf(out, "	font-size: 24px;\n");
	fprintf(out, "	font-family: Arial, Helvetica, sans-serif;\n");
	fprintf(out, "	border-bottom: 1px solid #808080;\n");
	fprintf(out, "	padding: 4px 0;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".message-icon {\n");
	fprintf(out, "	padding-right: 5px;\n");
	;
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".message-title {\n");
	fprintf(out, "	font-family: Arial, Helvetica, sans-serif;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");

	for(i = 0; i < sizeof(messages) / sizeof(messages[0]); i++) {
		fprintf(out, ".%s-message {\n", messages[i]);
		fprintf(out, "	border: 1px solid #808080;\n");
		fprintf(out, "	margin: 0.67em 0;\n");
		fprintf(out, "	padding: 8px;\n");
		fprintf(out, "	background-color: #ffffe0;\n");
		fprintf(out, "}\n");
		fprintf(out, "\n");
	}
}

void simple_head(FILE* out, const char* top, xl_node_t* header) {
}

void simple_body(FILE* out, const char* top, const char* title, xl_node_t* body) {
	char	    year[4 + 1 + 4 + 1]; /* no one would use our software in year 10000... right? :) */
	char*	    holder	 = "Unknown people";
	char*	    project	 = "Unknown project";
	char*	    project_desc = "Unknown project description";
	xl_node_t** nodes;
	xl_node_t*  child;
	char*	    text;
	char*	    link;
	char	    size[256];

	size[0] = 0;

	strcpy(year, "Some year");

	if((nodes = xl_get_path(skinconf->root, "copyright.holder")) != NULL) {
		holder = nodes[0]->text;

		free(nodes);
	}

	if((nodes = xl_get_path(skinconf->root, "project.name")) != NULL) {
		project = nodes[0]->text;

		free(nodes);
	}

	if((nodes = xl_get_path(skinconf->root, "project.description")) != NULL) {
		project_desc = nodes[0]->text;

		free(nodes);
	}

	/* should this be default behavior? */
	if(strcmp(top, "") != 0 && title != NULL) project_desc = (char*)title;

	if((nodes = xl_get_path(skinconf->root, "copyright.year")) != NULL) {
		time_t	   t	 = time(NULL);
		struct tm* tm	 = localtime(&t);
		int	   cyear = tm->tm_year + 1900;
		int	   xyear = atoi(nodes[0]->text);

		if(cyear == xyear) {
			sprintf(year, "%d", cyear);
		} else {
			int low	 = cyear < xyear ? cyear : xyear;
			int high = cyear > xyear ? cyear : xyear;

			sprintf(year, "%d-%d", low, high);
		}

		free(nodes);
	}

	fprintf(out, "		<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\" id=\"page\">\n");
	fprintf(out, "			<tr>\n");
	fprintf(out, "				<td colspan=\"2\" id=\"banner\">\n");
	fprintf(out, "					<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\">\n");
	fprintf(out, "						<tr>\n");
	fprintf(out, "							<td>\n");
	fprintf(out, "								<h1>%s</h1>\n", project);
	fprintf(out, "								<p>%s</p>\n", project_desc);
	fprintf(out, "							</td>\n");
	fprintf(out, "							<td align=\"right\">\n");

	link = NULL;
	if((nodes = xl_get_path(skinconf->root, "project.link")) != NULL) {
		link = xl_get_attribute(nodes[0], "href");
	}
	if(link == NULL) link = "https://invalid.link";
	link = u_path(top, link);

	text = NULL;
	if((nodes = xl_get_path(skinconf->root, "project.image")) != NULL) {
		text = xl_get_attribute(nodes[0], "src");
		if(text != NULL) text = u_path(top, text);
	}

	if(text != NULL) {
		int ws, hs;

		if(u_image_size(top, text, u_http_path, &ws, &hs)) {
			sprintf(size, " width=\"%d\" height=\"%d\"", ws, hs);
		}

		fprintf(out, "								<a href=\"%s\"><img src=\"%s\" alt=\"Project logo\" border=\"0\"%s></a>\n", link, text, size);
		free(text);
	}

	free(link);

	fprintf(out, "							</td>\n");
	fprintf(out, "						</tr>\n");
	fprintf(out, "					</table>\n");
	fprintf(out, "				</td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "			<tr>\n");
	fprintf(out, "				<td id=\"nav\" valign=\"top\">\n");
	fprintf(out, "					<div class=\"box\">\n");
	fprintf(out, "						<h2>LINKS</h2>\n");
	fprintf(out, "						<div class=\"box-content\">\n");
	if((nodes = xl_get_path(skinconf->root, "nav")) != NULL) {
		int i;

		child = nodes[0]->first_child;
		while(child != NULL) {
			default_nav(out, top, child, 8);

			child = child->next;
		}

		free(nodes);
	}
	fprintf(out, "						</div>\n");
	fprintf(out, "					</div>\n");
	fprintf(out, "				</td>\n");
	fprintf(out, "				<td id=\"content\" valign=\"top\">\n");

	child = body->first_child;
	while(child != NULL) {
		default_body(out, top, child, 0, 5);

		child = child->next;
	}

	fprintf(out, "					<div id=\"footer\">\n");

	if((nodes = xl_get_path(skinconf->root, "footer")) != NULL) {
		child = nodes[0]->first_child;
		while(child != NULL) {
			default_body(out, top, child, 1, 6);

			child = child->next;
		}

		free(nodes);
	}

	fprintf(out, "						<a href=\"https://validator.w3.org/check/referer\"><img src=\"%simage/valid-html401.png\" alt=\"Valid HTML 4.01\" border=\"0\" width=\"88\" height=\"31\"></a>\n", top);
	fprintf(out, "						<a href=\"https://jigsaw.w3.org/css-validator/\"><img src=\"%simage/valid-css.png\" alt=\"Valid CSS\" border=\"0\" width=\"88\" height=\"31\"></a>\n", top);
	fprintf(out, "						<p id=\"copyright\">\n");
	fprintf(out, "							Copyright &copy; %s %s%s All rights reserved.\n", year, holder, (strlen(holder) > 0 && holder[strlen(holder) - 1] == '.') ? "" : ".");
	fprintf(out, "						</p>\n");
	fprintf(out, "					</div>\n");
	fprintf(out, "				</td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "		</table>\n");
}
