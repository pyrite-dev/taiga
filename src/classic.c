#include <taiga.h>

void classic_stylesheet(FILE* out, const char* top) {
	FILE*	    f;
	char	    path[128];
	char*	    breadcrumb_bgcolor = NULL;
	xl_node_t** nodes;
	int	    i;
	char*	    messages[] = {
		  "fixme", "#cc6600",	/**/
		  "warning", "#990000", /**/
		  "note", "#006699"	/**/
	      };

	if((nodes = xl_get_path(skinconf->root, "breadcrumb")) != NULL) {
		breadcrumb_bgcolor = xl_get_attribute(nodes[0], "color");

		free(nodes);
	}
	if(breadcrumb_bgcolor == NULL) breadcrumb_bgcolor = "#003366";

	fprintf(out, "body {\n");
	fprintf(out, "	padding: 0;\n");
	fprintf(out, "	margin: 0;\n");
	fprintf(out, "	font-family: Verdana, Helvetica, Arial, sans-serif;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#breadcrumb {\n");
	fprintf(out, "	background-color: %s;\n", breadcrumb_bgcolor);
	fprintf(out, "	font-weight: bold;\n");
	fprintf(out, "	color: #fff;\n");
	fprintf(out, "	padding-left: 8px;\n");
	fprintf(out, "	padding-top: 2px;\n");
	fprintf(out, "	padding-bottom: 2px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "form {\n");
	fprintf(out, "	margin-top: 0;\n");
	fprintf(out, "	margin-bottom: 0;\n");
	fprintf(out, "}\n");
	fprintf(out, "#breadcrumb, #breadcrumb *, #copyright, #nav {\n");
	fprintf(out, "	font-size: x-small;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#nav {\n");
	fprintf(out, "	background-color: #eeeeee;\n");
	fprintf(out, "	border-right: solid 1px #aaaaaa;\n");
	fprintf(out, "	border-bottom: solid 1px #aaaaaa;\n");
	fprintf(out, "	padding: 8px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#content, #footer {\n");
	fprintf(out, "	padding: 8px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#footer {\n");
	fprintf(out, "	padding-top: 0;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".section {\n");
	fprintf(out, "	background-color: #eeeeee;\n");
	fprintf(out, "	padding-left: 8px;\n");
	fprintf(out, "	font-weight: bold;\n");
	fprintf(out, "	color: #000088;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a {\n");
	fprintf(out, "	text-decoration: none;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#breadcrumb a {\n");
	fprintf(out, "	color: #ffff44;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:link {\n");
	fprintf(out, "	color: #003366;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:visited {\n");
	fprintf(out, "	color: blue;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:hover, #breadcrumb a:hover {\n");
	fprintf(out, "	color: #ff3300;\n");
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
	fprintf(out, "#content p {\n");
	fprintf(out, "	padding-left: 8px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".grid, .grid th, .grid td {\n");
	fprintf(out, "	border: none;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".grid th, .grid td {\n");
	fprintf(out, "	text-align: left;\n");
	fprintf(out, "	vertical-align: top;\n");
	fprintf(out, "	padding: 2px 3px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".grid th {\n");
	fprintf(out, "	background-color: #cccccc;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".grid td {\n");
	fprintf(out, "	background-color: #ffffff;\n");
	fprintf(out, "	border-top: 1px solid #cccccc;\n");
	fprintf(out, "	border-left: 1px solid #cccccc;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".message-icon {\n");
	fprintf(out, "	padding-right: 5px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	for(i = 0; i < sizeof(messages) / sizeof(messages[0]); i += 2) {
		fprintf(out, ".%s-message {\n", messages[i]);
		fprintf(out, "	border-top: solid 5px %s;\n", messages[i + 1]);
		fprintf(out, "	border-left: solid 1px %s;\n", messages[i + 1]);
		fprintf(out, "	padding: 0.33em 0 0.67em 5px;\n");
		fprintf(out, "	margin: 0.67em 0;\n");
		fprintf(out, "}\n");
		fprintf(out, "\n");
	}
}

void classic_head(FILE* out, const char* top, xl_node_t* header) {
	xl_node_t* child;

	fprintf(out, "		<link rel=\"stylesheet\" href=\"%sstyle.css\">\n", top);

	child = header->first_child;
	while(child != NULL) {
		default_head(out, top, child, 2);

		child = child->next;
	}
}

void classic_body(FILE* out, const char* top, const char* title, xl_node_t* body) {
	char	    year[4 + 1 + 4 + 1]; /* no one would use our software in year 10000... right? :) */
	char*	    holder     = "Unknown people";
	char*	    sitesearch = NULL;
	xl_node_t** nodes;
	xl_node_t*  child;
	int	    i;
	char*	    images[] = {
		  "group", "Group",    /**/
		  "project", "Project" /**/
	      };

	strcpy(year, "Some year");

	if((nodes = xl_get_path(skinconf->root, "copyright.holder")) != NULL) {
		holder = nodes[0]->text;

		free(nodes);
	}

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

	if((nodes = xl_get_path(skinconf->root, "search")) != NULL) {
		sitesearch = xl_get_attribute(nodes[0], "domain");

		free(nodes);
	}
	if(sitesearch == NULL)
		sitesearch = "https://invalid.link";

	fprintf(out, "		<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\">\n");
	fprintf(out, "			<tr>\n");
	fprintf(out, "				<td>\n");
	for(i = 0; i < sizeof(images) / sizeof(images[0]); i++) {
		char  path[64];
		char* name;
		char* link;

		sprintf(path, "%s.name", images[i]);
		if((nodes = xl_get_path(skinconf->root, path)) != NULL) {
			name = nodes[0]->text;
			free(nodes);
		}
		if(name == NULL) name = "Logo";

		sprintf(path, "%s.link", images[i]);
		if((nodes = xl_get_path(skinconf->root, path)) != NULL) {
			link = xl_get_attribute(nodes[0], "href");
			free(nodes);
		}
		if(link == NULL) link = "https://invalid.link";

		link = u_path(top, link);

		sprintf(path, "%s.image", images[i]);
		if((nodes = xl_get_path(skinconf->root, path)) != NULL) {
			char* text = xl_get_attribute(nodes[0], "src");

			if(text != NULL) {
				int  ws, hs;
				char size[256];

				size[0] = 0;

				ws = 0;
				if(u_image_size(top, text, u_http_path, &ws, &hs)) {
					sprintf(size, " width=\"%d\" height=\"%d\"", ws, hs);
				}

				text = u_path(top, text);

				fprintf(out, "					<a href=\"%s\"><img src=\"%s\" alt=\"%s\" border=\"0\"%s></a>\n", link, text, name, size);
				fprintf(out, "					<img src=\"%simage/fill.gif\" width=\"96\">\n", top);
				free(text);
			}

			free(nodes);
		}

		free(link);
	}
	fprintf(out, "				</td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "		</table>\n");
	fprintf(out, "		<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\" id=\"breadcrumb\">\n");
	fprintf(out, "			<tr>\n");
	fprintf(out, "				<td>\n");
	if((nodes = xl_get_path(skinconf->root, "breadcrumb.link")) != NULL) {
		int i;

		for(i = 0; nodes[i] != NULL; i++) {
			char* link = xl_get_attribute(nodes[i], "href");
			char* name = xl_get_attribute(nodes[i], "name");

			if(link == NULL) link = "https://invalid.link";

			link = u_path(top, link);

			if(title == NULL) title = link;

			if(i > 0) fprintf(out, "					|\n");
			fprintf(out, "					<a href=\"%s\">%s</a>\n", link, name);

			free(link);
		}

		free(nodes);
	}
	fprintf(out, "				</td>\n");
	fprintf(out, "				<td nowrap=\"nowrap\" align=\"right\">\n");
	fprintf(out, "					<form action=\"https://www.google.com/search\" method=\"GET\">\n");
	fprintf(out, "						Search\n");
	fprintf(out, "						<input type=\"hidden\" name=\"sitesearch\" value=\"%s\">\n", sitesearch);
	fprintf(out, "						<input name=\"q\" size=\"10\">\n");
	fprintf(out, "						<input type=\"submit\" value=\"Go\">\n");
	fprintf(out, "					</form>\n");
	fprintf(out, "				</td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "		</table>\n");
	fprintf(out, "		<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\">\n");
	fprintf(out, "			<tr>\n");
	fprintf(out, "				<td width=\"150\" valign=\"top\">\n");
	fprintf(out, "					<div id=\"nav\">\n");

	if((nodes = xl_get_path(body, "section")) != NULL) {
		int i;

		fprintf(out, "						<div class=\"linkgrouptitle\"> - Contents</div>\n");
		fprintf(out, "						<div class=\"linkgroup\">\n");

		for(i = 0; nodes[i] != NULL; i++) {
			char* name = NULL;
			char* id;

			if((name = xl_get_attribute(nodes[i], "title")) == NULL) continue;

			id = u_section_id(nodes[i]);

			fprintf(out, "							 - <a href=\"#%s\">%s</a><br>\n", id, name);
		}

		fprintf(out, "						</div>\n");
		fprintf(out, "						<br>\n");
	}

	if((nodes = xl_get_path(skinconf->root, "nav")) != NULL) {
		int i;

		child = nodes[0]->first_child;
		while(child != NULL) {
			default_nav(out, top, child, 6);

			child = child->next;
		}

		free(nodes);
	}

	fprintf(out, "					</div>\n");
	fprintf(out, "				</td>\n");
	fprintf(out, "				<td valign=\"top\">\n");
	fprintf(out, "					<div id=\"content\">\n");

	child = body->first_child;
	while(child != NULL) {
		default_body(out, top, child, 0, 6);

		child = child->next;
	}

	fprintf(out, "					</div>\n");
	fprintf(out, "					<div id=\"footer\">\n");

	if((nodes = xl_get_path(skinconf->root, "footer")) != NULL) {
		child = nodes[0]->first_child;
		while(child != NULL) {
			default_body(out, top, child, 1, 6);

			child = child->next;
		}

		free(nodes);
	}

	fprintf(out, "					</div>\n");
	fprintf(out, "				</td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "		</table>\n");
	fprintf(out, "		<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\">\n");
	fprintf(out, "			<tr>\n");
	fprintf(out, "				<td id=\"copyright\" align=\"center\">\n");
	fprintf(out, "					Copyright &copy; %s %s%s All rights reserved.\n", year, holder, (strlen(holder) > 0 && holder[strlen(holder) - 1] == '.') ? "" : ".");
	fprintf(out, "				<td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "			<tr>\n");
	fprintf(out, "				<td align=\"right\">\n");
	fprintf(out, "					<a href=\"https://validator.w3.org/check/referer\"><img src=\"%simage/valid-html401.png\" alt=\"Valid HTML 4.01\" border=\"0\" width=\"88\" height=\"31\"></a>\n", top);
	fprintf(out, "					<a href=\"https://jigsaw.w3.org/css-validator/\"><img src=\"%simage/valid-css.png\" alt=\"Valid CSS\" border=\"0\" width=\"88\" height=\"31\"></a>\n", top);
	fprintf(out, "				<td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "		</table>\n");
}
