#include <taiga.h>

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

static void accept_attr(char* text, xl_node_t* element, ...) {
	xl_attribute_t* attr = element->first_attribute;

	text[0] = 0;
	while(attr != NULL) {
		va_list	    va;
		const char* s;

		va_start(va, element);
		while((s = va_arg(va, const char*)) != NULL) {
			if(strcmp(attr->key, s) != 0) continue;
			if(attr->value == NULL) {
				sprintf(text + strlen(text), " %s", attr->key);
			} else {
				sprintf(text + strlen(text), " %s=\"%s\"", attr->key, attr->value);
			}
		}
		va_end(va);

		attr = attr->next;
	}
}

void default_node(FILE* out, const char* top, xl_node_t* element, int indent) {
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
		  strcmp(element->name, "li") == 0 ||	      /**/
		  strcmp(element->name, "dt") == 0 ||	      /**/
		  strcmp(element->name, "dd") == 0 ||	      /**/
		  strcmp(element->name, "strong") == 0 ||     /**/
		  strcmp(element->name, "sub") == 0 ||	      /**/
		  strcmp(element->name, "sup") == 0 ||	      /**/
		  strcmp(element->name, "tr") == 0) {
		sprintf(tag, "<%s>", element->name);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "a") == 0) {
		char text[2048];

		accept_attr(text, element, "href", NULL);

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "td") == 0 || /**/
		  strcmp(element->name, "th") == 0) {
		char text[2048];

		accept_attr(text, element, "rowspan", "colspan", NULL);

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "img") == 0) {
		char text[2048];

		accept_attr(text, element, "src", NULL);

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "table") == 0) {
		sprintf(tag, "<%s>", element->name);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "hr") == 0) {
		sprintf(tag, "<%s>", element->name);
	}

	if(tag[0] != 0) print(out, tag, indent);

	child = element->first_child;
	while(child != NULL) {
		if(child->type == XL_NODE_NODE && child->name != NULL) {
			default_node(out, top, child, indent + 1 + add);
		} else if(child->type == XL_NODE_TEXT && child->text != NULL) {
			print(out, child->text, indent + 1 + add);
		}

		child = child->next;
	}

	if(end[0] != 0) print(out, end, indent);
}

void default_nav(FILE* out, const char* top, xl_node_t* element, int indent) {
	int i;

	if(element->name == NULL) return;

	if(strcmp(element->name, "link") == 0) {
		char* link;
		char* name;

		if((link = xl_get_attribute(element, "href")) == NULL) link = "https://invalid.link";
		if((name = xl_get_attribute(element, "name")) == NULL) name = "";

		for(i = 0; i < indent; i++) fprintf(out, "\t");
		fprintf(out, " - <a href=\"%s\">%s</a><br>", link, name);
	} else if(strcmp(element->name, "group") == 0) {
		char*	   title;
		xl_node_t* child;

		if((title = xl_get_attribute(element, "title")) == NULL) title = "";

		if(title != NULL) {
			for(i = 0; i < indent; i++) fprintf(out, "\t");
			fprintf(out, "<div class=\"linkgrouptitle\"> - %s</div>\n", title);
		}

		for(i = 0; i < indent; i++) fprintf(out, "\t");
		fprintf(out, "<div class=\"linkgroup\">\n");

		child = element->first_child;
		while(child != NULL) {
			default_nav(out, top, child, indent + 1);

			child = child->next;
		}

		for(i = 0; i < indent; i++) fprintf(out, "\t");
		fprintf(out, "</div>\n");
	}
}
