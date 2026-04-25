#include <taiga.h>

void dark_stylesheet(FILE* out, const char* top) {
	fprintf(out, "body, td, th, div, p, .smalltext {\n");
	fprintf(out, "	color: #666666;\n");
	fprintf(out, "	font-family: \"Verdana\";\n");
	fprintf(out, "	font-size: 9pt;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".smalltext, .linkgroup, .linkgrouptitle {\n");
	fprintf(out, "	font-size: 8pt;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".section {\n");
	fprintf(out, "	color: #999999;\n");
	fprintf(out, "	font-family: \"Verdana\";\n");
	fprintf(out, "	font-size: 11pt;\n");
	fprintf(out, "	padding-top: 8px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "hr {\n");
	fprintf(out, "	border: none;\n");
	fprintf(out, "	border-bottom: solid 1px #666666;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".sectionsep {\n");
	fprintf(out, "	background: #666666;\n");
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
	fprintf(out, "a {\n");
	fprintf(out, "	text-decoration: none;\n");
	fprintf(out, "	color: #cccccc;\n");
	fprintf(out, "	font-family: \"Verdana\";\n");
	fprintf(out, "	font-weight: bold;\n");
	fprintf(out, "}\n");
}

void dark_htmlattr(FILE* out, const char* top) {
	fprintf(out, " style=\"height: 100%%;\"");
}

void dark_head(FILE* out, const char* top, xl_node_t* header, const char* input) {
	xl_node_t* child;

	child = header->first_child;
	while(child != NULL) {
		default_head(out, top, child, input, 2);

		child = child->next;
	}
}

void dark_bodyattr(FILE* out, const char* top) {
	fprintf(out, " marginwidth=\"0\"");
	fprintf(out, " marginheight=\"0\"");
	fprintf(out, " bgcolor=\"black\"");
	fprintf(out, " style=\"height: 100%%;\"");
}

void dark_body(FILE* out, const char* top, const char* title, xl_node_t* body, const char* input) {
	char*	    holder	 = "Unknown people";
	char*	    project_desc = "Unknown project description";
	char*	    link;
	char*	    image;
	char	    size[256];
	int	    ws, hs;
	xl_node_t*  child;
	xl_node_t** nodes;

	size[0] = 0;

	if((nodes = xl_get_path(skinconf->root, "copyright.holder")) != NULL) {
		holder = nodes[0]->text;

		free(nodes);
	}

	link = NULL;
	if((nodes = xl_get_path(skinconf->root, "project.link")) != NULL) {
		link = xl_get_attribute(nodes[0], "href");

		free(nodes);
	}
	if(link == NULL) link = "https://invalid.link";
	link = u_path(top, link);

	image = NULL;
	if((nodes = xl_get_path(skinconf->root, "project.image")) != NULL) {
		image = xl_get_attribute(nodes[0], "src");
		if(image != NULL) image = u_path(top, image);

		if(u_image_size(top, image, u_http_path, &ws, &hs)) {
			sprintf(size, " width=\"%d\" height=\"%d\"", ws, hs);
		}

		free(nodes);
	}

	if((nodes = xl_get_path(skinconf->root, "project.description")) != NULL) {
		project_desc = nodes[0]->text;

		free(nodes);
	}

	fprintf(out, "		<table width=\"100%%\" height=\"100%%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">\n");
	fprintf(out, "			<tr>\n");
	fprintf(out, "				<td valign=\"middle\" align=\"center\">\n");
	fprintf(out, "					<table width=\"600\" height=\"400\" border=\"0\" cellspacing=\"10\" cellpadding=\"0\">\n");
	fprintf(out, "						<tr>\n");
	fprintf(out, "							<td rowspan=\"2\">\n");
	fprintf(out, "								<table width=\"1\" border=\"0\" cellspacing=\"0\" cellpadding=\"4\">\n");
	fprintf(out, "									<tr>\n");
	fprintf(out, "										<td align=\"center\" valign=\"middle\">\n");
	if(image != NULL) {
		fprintf(out, "											<a href=\"%s\"><img src=\"%s\" alt=\"Project logo\" border=\"0\"%s></a>\n", link, image, size);
	}
	fprintf(out, "										</td>\n");
	fprintf(out, "									</tr>\n");
	fprintf(out, "									<tr>\n");
	fprintf(out, "										<td align=\"right\">\n");
	fprintf(out, "											%s<br>\n", project_desc);
	fprintf(out, "											<br>\n");
	fprintf(out, "											<div class=\"smalltext\">&copy; %s</div>\n", holder);
	fprintf(out, "										</td>\n");
	fprintf(out, "									</tr>\n");
	fprintf(out, "									<tr>\n");
	fprintf(out, "										<td>\n");
	fprintf(out, "											<table border=\"0\" width=\"100%%\" height=\"1\" cellspacing=\"0\" cellpadding=\"0\"><tr><td class=\"sectionsep\"></td></tr></table>");
	fprintf(out, "										</td>\n");
	fprintf(out, "									</tr>\n");
	fprintf(out, "									<tr>\n");
	fprintf(out, "										<td align=\"left\">\n");
	if((nodes = xl_get_path(skinconf->root, "nav")) != NULL) {
		int i;

		child = nodes[0]->first_child;
		while(child != NULL) {
			default_nav(out, top, child, input, 8);

			child = child->next;
		}

		free(nodes);
	}
	fprintf(out, "										</td>\n");
	fprintf(out, "									</tr>\n");
	fprintf(out, "								</table>\n");
	fprintf(out, "							</td>\n");
	fprintf(out, "							<td width=\"1\" bgcolor=\"#666666\" rowspan=\"2\"></td>\n");
	fprintf(out, "							<td width=\"450\" valign=\"top\" id=\"content\">\n");
	if(body != NULL) {
		child = body->first_child;
		while(child != NULL) {
			default_body(out, top, child, input, 0, 0, 8);

			child = child->next;
		}
	}
	fprintf(out, "							</td>\n");
	fprintf(out, "						</tr>\n");
	fprintf(out, "						<tr>\n");
	fprintf(out, "							<td id=\"footer\">\n");
	if((nodes = xl_get_path(skinconf->root, "footer")) != NULL) {
		child = nodes[0]->first_child;
		while(child != NULL) {
			default_body(out, top, child, input, 1, 0, 8);

			child = child->next;
		}

		free(nodes);
	}
	fprintf(out, "							</td>\n");
	fprintf(out, "						</tr>\n");
	fprintf(out, "					</table>\n");
	fprintf(out, "				</td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "		</table>\n");
}
