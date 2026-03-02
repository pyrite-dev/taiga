#include <taiga.h>

#include "image/fill.h"
#include "image/valid-html401.h"
#include "image/valid-css.h"
#include "image/fixme.h"
#include "image/warning.h"
#include "image/note.h"

void classic_stylesheet(FILE* out, const char* top) {
	FILE*	    f;
	char	    path[128];
	char*	    breadcrumb_bgcolor = NULL;
	xl_node_t** nodes;
	char*	    messages[] = {
		  "fixme", "#cc6600",	/**/
		  "warning", "#990000", /**/
		  "note", "#006699"	/**/
	      };
	int i;

	sprintf(path, "%sfill.gif", top);
	f = fopen(path, "wb");
	fwrite(image_fill, 1, image_fill_len, f);
	fclose(f);

	sprintf(path, "%svalid-html401.png", top);
	f = fopen(path, "wb");
	fwrite(image_valid_html401, 1, image_valid_html401_len, f);
	fclose(f);

	sprintf(path, "%svalid-css.png", top);
	f = fopen(path, "wb");
	fwrite(image_valid_css, 1, image_valid_css_len, f);
	fclose(f);

	sprintf(path, "%sfixme.png", top);
	f = fopen(path, "wb");
	fwrite(image_fixme, 1, image_fixme_len, f);
	fclose(f);

	sprintf(path, "%swarning.png", top);
	f = fopen(path, "wb");
	fwrite(image_warning, 1, image_warning_len, f);
	fclose(f);

	sprintf(path, "%snote.png", top);
	f = fopen(path, "wb");
	fwrite(image_note, 1, image_note_len, f);
	fclose(f);

	if((nodes = xl_get_path(skinconf->root, "breadcrumb")) != NULL) {
		breadcrumb_bgcolor = xl_get_attribute(nodes[0], "color");

		free(nodes);
	}
	if(breadcrumb_bgcolor == NULL) breadcrumb_bgcolor = "#003366";

	fprintf(out, "body {\n");
	fprintf(out, "	padding: 0;\n");
	fprintf(out, "	margin: 0;\n");
	fprintf(out, "	font-family: Arial, sans-serif;\n");
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
	fprintf(out, "#content {\n");
	fprintf(out, "	padding: 8px;\n");
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
	fprintf(out, "	padding-left: 16px;\n");
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
	fprintf(out, "tr.even {\n");
	fprintf(out, "	background-color: #eeeeee;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "tr.odd {\n");
	fprintf(out, "	background-color: #dddddd;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	for(i = 0; i < sizeof(messages) / sizeof(messages[0]); i += 2) {
		fprintf(out, ".%s-message {\n", messages[i]);
		fprintf(out, "	border-top: solid 5px %s;\n", messages[i + 1]);
		fprintf(out, "	border-left: solid 1px %s;\n", messages[i + 1]);
		fprintf(out, "	padding: 0.33em 0 0.67em 5px;\n");
		fprintf(out, "	margin: 0.67em 0;\n");
		fprintf(out, "}\n");
	}
}

void classic_head(FILE* out, const char* top, xl_node_t* header) {
	fprintf(out, "		<link rel=\"stylesheet\" href=\"%sstyle.css\">\n", top);
}

static void print(FILE* out, const char* txt, int indent) {
	int i;

	for(i = 0;; i++) {
		if(i == 0 || txt[i] == '\n' || txt[i] == 0) {
			int j;
			if(i > 0) fprintf(out, "\n");
			if(txt[i] == 0) break;
			for(j = 0; j < indent; j++) fprintf(out, "\t");
		}

		if(txt[i] != '\n') fprintf(out, "%c", txt[i]);
	}
}

static void recursive(FILE* out, const char* top, xl_node_t* element, int indent) {
	xl_node_t* child;
	char	   tag[2048]; /* enough for most cases... :) */
	char	   end[128];
	int	   add = 0;

	tag[0] = end[0] = 0;

	if(element->name == NULL) return;

	if(strcmp(element->name, "section") == 0) {
		char* title = xl_get_attribute(element, "title");

		sprintf(tag, "<div class=\"section\">%s</div>", title);
	} else if(strcmp(element->name, "fixme") == 0 ||   /**/
		  strcmp(element->name, "warning") == 0 || /**/
		  strcmp(element->name, "note") == 0) {
		char* text = "";

		if(strcmp(element->name, "fixme") == 0) {
			text = "Fixme";
		} else if(strcmp(element->name, "warning") == 0) {
			text = "Warning";
		} else if(strcmp(element->name, "note") == 0) {
			text = "Note";
		}

		sprintf(tag + strlen(tag), "<div class=\"%s-message\">\n", element->name);
		sprintf(tag + strlen(tag), "	<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\">\n");
		sprintf(tag + strlen(tag), "		<tr>\n");
		sprintf(tag + strlen(tag), "			<td rowspan=\"2\">\n");
		sprintf(tag + strlen(tag), "				<img src=\"%s%s.png\">\n", top, element->name);
		sprintf(tag + strlen(tag), "			</td>\n");
		sprintf(tag + strlen(tag), "			<td>\n");
		sprintf(tag + strlen(tag), "				<b>%s</b>\n", text);
		sprintf(tag + strlen(tag), "			</td>\n");
		sprintf(tag + strlen(tag), "		</tr>\n");
		sprintf(tag + strlen(tag), "		<tr>\n");
		sprintf(tag + strlen(tag), "			<td width=\"100%%\">");

		sprintf(end + strlen(end), "			</td>\n");
		sprintf(end + strlen(end), "		</tr>\n");
		sprintf(end + strlen(end), "	</table>\n");
		sprintf(end + strlen(end), "</div>", element->name);

		add = 3;
	} else if(strcmp(element->name, "p") == 0 ||	      /**/
		  strcmp(element->name, "code") == 0 ||	      /**/
		  strcmp(element->name, "blockquote") == 0 || /**/
		  strcmp(element->name, "ul") == 0 ||	      /**/
		  strcmp(element->name, "ol") == 0 ||	      /**/
		  strcmp(element->name, "li") == 0) {
		sprintf(tag, "<%s>", element->name);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "a") == 0) {
		char		text[2048];
		xl_attribute_t* attr = element->first_attribute;

		text[0] = 0;
		while(attr != NULL) {
			if(attr->value == NULL) {
				sprintf(text + strlen(text), " %s", attr->key);
			} else {
				sprintf(text + strlen(text), " %s=\"%s\"", attr->key, attr->value);
			}

			attr = attr->next;
		}

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "hr") == 0) {
		sprintf(tag, "<%s>", element->name);
	}

	if(tag[0] != 0) print(out, tag, indent + 6);

	child = element->first_child;
	while(child != NULL) {
		if(child->type == XL_NODE_NODE && child->name != NULL) {
			recursive(out, top, child, indent + 1 + add);
		} else if(child->type == XL_NODE_TEXT && child->text != NULL) {
			print(out, child->text, indent + 7 + add);
		}

		child = child->next;
	}

	if(end[0] != 0) print(out, end, indent + 6);
}

void classic_body(FILE* out, const char* top, const char* title, xl_node_t* body) {
	char	    year[4 + 1 + 4 + 1]; /* no one would use our software in year 10000... right? :) */
	char*	    holder     = "Unknown people";
	char*	    sitesearch = NULL;
	xl_node_t** nodes;
	xl_node_t*  child;

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
	if(sitesearch == NULL) sitesearch = "https://invalid.link";

	fprintf(out, "		<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\" id=\"breadcrumb\">\n");
	fprintf(out, "			<tr width=\"100%%\">\n");
	fprintf(out, "				<td>\n");
	if((nodes = xl_get_path(skinconf->root, "breadcrumb.link")) != NULL) {
		int i;

		for(i = 0; nodes[i] != NULL; i++) {
			char* link = xl_get_attribute(nodes[i], "href");
			char* name = xl_get_attribute(nodes[i], "name");

			if(link == NULL) link = "https://invalid.link";
			if(title == NULL) title = link;

			if(i > 0) fprintf(out, "					|\n");
			fprintf(out, "					<a href=\"%s\">%s</a>\n", link, name);
		}

		free(nodes);
	}
	fprintf(out, "				</td>\n");
	fprintf(out, "				<td nowrap=\"1\" align=\"right\">\n");
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
	fprintf(out, "					</div>\n");
	fprintf(out, "				</td>\n");
	fprintf(out, "				<td valign=\"top\">\n");
	fprintf(out, "					<div id=\"content\">\n");

	child = body->first_child;
	while(child != NULL) {
		recursive(out, top, child, 0);

		child = child->next;
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
	fprintf(out, "					<a href=\"https://validator.w3.org/check/referer\"><img src=\"%svalid-html401.png\" alt=\"Valid HTML 4.01\" border=\"0\"></a>", top);
	fprintf(out, "					<a href=\"https://jigsaw.w3.org/css-validator/\"><img src=\"%svalid-css.png\" alt=\"Valid CSS\" border=\"0\"></a>", top);
	fprintf(out, "				<td>\n");
	fprintf(out, "			</tr>\n");
	fprintf(out, "		</table>\n");
	fprintf(out, "		<!--[if lte IE 6]>\n");
	fprintf(out, "		<script language=\"javascript\" type=\"text/javascript\">\n");
	fprintf(out, "			for(var i = 0; i < document.images.length; i++){\n");
	fprintf(out, "				var s = document.images[i].src;\n");
	fprintf(out, "				if(s.indexOf('.png') > 0){\n");
	fprintf(out, "					var oldw = document.images[i].clientWidth;\n");
	fprintf(out, "					var oldh = document.images[i].clientHeight;\n");
	fprintf(out, "					document.images[i].src = '%sfill.gif';\n", top);
	fprintf(out, "					document.images[i].style.filter = \"progid:DXImageTransform.Microsoft.AlphaImageLoader(src='\" + s + \"', sizingMethod='scale')\";\n");
	fprintf(out, "					document.images[i].style.width = oldw + \"px\";\n");
	fprintf(out, "					document.images[i].style.height = oldh + \"px\";\n");
	fprintf(out, "				}\n");
	fprintf(out, "			}\n");
	fprintf(out, "		</script>\n");
	fprintf(out, "		<![endif]-->\n");
}
