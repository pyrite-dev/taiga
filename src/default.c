#include <taiga.h>

static void print(FILE* out, const char* txt, int pre, int indent) {
	int i;

	for(i = 0;; i++) {
		if(i == 0 || txt[i] == '\n' || txt[i] == 0) {
			int j;
			if(pre ? (txt[i] == '\n') : (i > 0)) fprintf(out, "\n");
			if(txt[i] == 0) break;
			if(!pre)
				for(j = 0; j < indent; j++) fprintf(out, "\t");
		}

		if(txt[i] != '\n') fprintf(out, "%c", txt[i]);
	}
}

static void accept_attr(const char* top, char* text, int spec, xl_node_t* element, ...) {
	xl_attribute_t* attr = element->first_attribute;

	text[0] = 0;
	while(attr != NULL) {
		va_list	    va;
		const char* s;

		va_start(va, element);
		while((s = va_arg(va, const char*)) != NULL) {
			if(strcmp(attr->key, s) != 0)
				continue;
			if(attr->value == NULL) {
				sprintf(text + strlen(text), " %s", attr->key);
			} else {
				char* t;

				if(spec && (strcmp(attr->key, "href") == 0 || strcmp(attr->key, "src") == 0)) {
					t = u_path(top, attr->value);
				} else {
					t = u_strdup(attr->value);
				}

				sprintf(text + strlen(text), " %s=\"%s\"", attr->key, t);

				free(t);
			}
		}
		va_end(va);

		attr = attr->next;
	}
}

void default_head(FILE* out, const char* top, xl_node_t* element, int indent) {
	xl_node_t* child;
	char	   tag[2048];
	char	   end[128];
	int	   add = 0;

	tag[0] = end[0] = 0;

	if(element->name == NULL) return;

	if(strcmp(element->name, "link") == 0) {
		char text[2048];

		accept_attr(top, text, 0, element, "rel", "href", NULL);

		sprintf(tag, "<%s%s>", element->name, text);
	}

	if(tag[0] != 0) print(out, tag, 0, indent);

	child = element->first_child;
	while(child != NULL) {
		if(child->type == XL_NODE_NODE && child->name != NULL) {
			default_head(out, top, child, indent + 1 + add);
		} else if(child->type == XL_NODE_TEXT && child->text != NULL) {
			/* most likely junk */
#if 0
			print(out, child->text, indent + 1 + add);
#endif
		}

		child = child->next;
	}

	if(end[0] != 0) print(out, end, 0, indent);
}

void default_body(FILE* out, const char* top, xl_node_t* element, int spec, int pre, int indent) {
	xl_node_t* child;
	char	   tag[2048]; /* enough for most cases... :) */
	char	   end[128];
	char	   text[2048];
	int	   add = 0;

	tag[0] = end[0] = 0;

	if(element->name == NULL) return;

	if(strcmp(element->name, "section") == 0) {
		char* title = xl_get_attribute(element, "title");
		char* id    = u_section_id(element);

		if(id != NULL) sprintf(tag, "<div class=\"section\" id=\"%s\">%s</div>", id, title);
	} else if(strcmp(element->name, "fixme") == 0 ||   /**/
		  strcmp(element->name, "warning") == 0 || /**/
		  strcmp(element->name, "note") == 0) {
		char* say = "";
		char  author[2048];
		char* attr;

		author[0] = 0;

		accept_attr(top, text, 0, element, "id", "class", NULL);

		if(strcmp(element->name, "fixme") == 0) {
			say = "Fixme";

			strcpy(author, " ()");
			if((attr = xl_get_attribute(element, "author")) != NULL) sprintf(author, " (%s)", attr);
		} else if(strcmp(element->name, "warning") == 0) {
			say = "Warning";
		} else if(strcmp(element->name, "note") == 0) {
			say = "Note";
		}

		sprintf(tag + strlen(tag), "<div class=\"%s-message\"%s>\n", element->name, text);
		sprintf(tag + strlen(tag), "	<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\">\n");
		sprintf(tag + strlen(tag), "		<tr>\n");
		sprintf(tag + strlen(tag), "			<td rowspan=\"2\" class=\"message-icon\">\n");
		sprintf(tag + strlen(tag), "				<img src=\"%simage/%s.png\" alt=\"%s\" width=\"32\" height=\"32\">\n", top, element->name, say);
		sprintf(tag + strlen(tag), "			</td>\n");
		sprintf(tag + strlen(tag), "			<td class=\"message-title\">\n");
		sprintf(tag + strlen(tag), "				<b>%s%s</b>\n", say, author);
		sprintf(tag + strlen(tag), "			</td>\n");
		sprintf(tag + strlen(tag), "		</tr>\n");
		sprintf(tag + strlen(tag), "		<tr>\n");
		sprintf(tag + strlen(tag), "			<td width=\"100%%\" class=\"message-content\">");

		sprintf(end + strlen(end), "			</td>\n");
		sprintf(end + strlen(end), "		</tr>\n");
		sprintf(end + strlen(end), "	</table>\n");
		sprintf(end + strlen(end), "</div>", element->name);

		add = 3;
	} else if(strcmp(element->name, "p") == 0 ||	      /**/
		  strcmp(element->name, "code") == 0 ||	      /**/
		  strcmp(element->name, "pre") == 0 ||	      /**/
		  strcmp(element->name, "blockquote") == 0 || /**/
		  strcmp(element->name, "li") == 0 ||	      /**/
		  strcmp(element->name, "dt") == 0 ||	      /**/
		  strcmp(element->name, "dd") == 0 ||	      /**/
		  strcmp(element->name, "strong") == 0 ||     /**/
		  strcmp(element->name, "del") == 0 ||	      /**/
		  strcmp(element->name, "u") == 0 ||	      /**/
		  strcmp(element->name, "sub") == 0 ||	      /**/
		  strcmp(element->name, "sup") == 0 ||	      /**/
		  strcmp(element->name, "tr") == 0 ||	      /**/
		  strcmp(element->name, "em") == 0 ||	      /**/
		  strcmp(element->name, "h1") == 0 ||	      /**/
		  strcmp(element->name, "h2") == 0 ||	      /**/
		  strcmp(element->name, "h3") == 0 ||	      /**/
		  strcmp(element->name, "h4") == 0 ||	      /**/
		  strcmp(element->name, "h5") == 0 ||	      /**/
		  strcmp(element->name, "h6") == 0) {
		accept_attr(top, text, 0, element, "id", "class", NULL);

		if(strcmp(element->name, "pre") == 0) pre = 1;

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "ul") == 0 || /**/
		  strcmp(element->name, "ol") == 0) {
		accept_attr(top, text, 0, element, "id", "class", "spacing", NULL);

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "a") == 0) {
		accept_attr(top, text, 0, element, "id", "class", "href", "title", "rel", NULL);

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "td") == 0 || /**/
		  strcmp(element->name, "th") == 0) {
		accept_attr(top, text, 0, element, "id", "class", "rowspan", "colspan", NULL);

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "img") == 0) {
		char* r;
		char* w;
		char* h;
		int   ws, hs;

		accept_attr(top, text, 0, element, "src", "alt", "title", "height", "width", "id", "class", NULL);

		w = xl_get_attribute(element, "width");
		h = xl_get_attribute(element, "height");
		if((w == NULL || h == NULL) && (r = xl_get_attribute(element, "src")) != NULL) {
			if(u_image_size(top, r, u_http_path, &ws, &hs)) {
				if(w == NULL && h == NULL) {
					sprintf(text + strlen(text), "width=\"%d\" height=\"%d\"", ws, hs);
				} else if(w != NULL) {
					sprintf(text + strlen(text), "width=\"%d\" height=\"%d\"", atoi(w), hs * atoi(w) / ws);
				} else if(h != NULL) {
					sprintf(text + strlen(text), "width=\"%d\" height=\"%d\"", ws * atoi(h) / hs, atoi(h));
				}
			}
		}

		sprintf(tag, "<%s%s border=\"0\">", element->name, text);
	} else if(strcmp(element->name, "script") == 0) {
		accept_attr(top, text, 0, element, "src", "type", NULL);

		sprintf(tag, "<%s%s>", element->name, text);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "table") == 0) {
		char* t = xl_get_attribute(element, "class");

		accept_attr(top, text, 0, element, "id", NULL);

		sprintf(tag, "<%s%s class=\"grid%s%s\" width=\"100%%\" cellpadding=\"3\" cellspacing=\"2\" border=\"1\">", element->name, text, t == NULL ? "" : " ", t == NULL ? "" : t);

		sprintf(end, "</%s>", element->name);
	} else if(strcmp(element->name, "hr") == 0 || /**/
		  strcmp(element->name, "br") == 0) {
		accept_attr(top, text, 0, element, "id", "class", NULL);

		sprintf(tag, "<%s%s>", element->name, text);
	}

	if(tag[0] != 0) print(out, tag, pre, indent);

	child = element->first_child;
	while(child != NULL) {
		if(child->type == XL_NODE_NODE && child->name != NULL) {
			default_body(out, top, child, spec, pre, indent + 1 + add);
		} else if(child->type == XL_NODE_TEXT && (pre ? (child->text_raw != NULL) : (child->text != NULL))) {
			print(out, pre ? child->text_raw : child->text, pre, pre ? 0 : (indent + 1 + add));
		}

		child = child->next;
	}

	if(end[0] != 0) print(out, end, pre, indent);
	if(strcmp(end, "</pre>") == 0) fprintf(out, "\n");
}

static int sort_xml(const void* a, const void* b) {
	const char* sa = *(const char**)a;
	const char* sb = *(const char**)b;
	int	    na = 0;
	int	    nb = 0;
	int	    i;

	for(i = 0; sa[i] != 0; i++) {
		if(sa[i] == '/') na++;
	}

	for(i = 0; sb[i] != 0; i++) {
		if(sb[i] == '/') nb++;
	}

	if(na == nb) return strcmp(sa, sb);
	return a > b ? 1 : -1;
}

static char** scan_xml(const char* path, const char* path2, xl_node_t** excludes, int layer) {
	IO_DIR* dir;
	char**	arr = NULL;

	if((dir = io_opendir(path)) != NULL) {
		struct io_dirent* d;

		while((d = io_readdir(dir)) != NULL) {
			char*	       p;
			struct io_stat s;

			if(strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".") == 0) continue;

			p = u_strvacat(path, d->d_name, NULL);

			if(io_stat(p, &s) == 0) {
				if(IO_S_ISDIR(s.st_mode)) {
					char*  p2;
					char** arr2;
					int    i;

					if(layer > 0 || layer == -0xffff) {
						char* p3 = u_strvacat(path2, d->d_name, "/", NULL);

						p2   = u_strvacat(p, "/", NULL);
						arr2 = scan_xml(p2, p3, excludes, layer - 1);

						free(p3);

						for(i = 0; i < arrlen(arr2); i++) {
							arrput(arr, arr2[i]);
						}

						arrfree(arr2);
						free(p2);
						free(p);
					}
				} else if(strcmp(d->d_name, "index.xml") == 0) {
					char* p3 = u_strvacat(path2, d->d_name, NULL);
					int   i;

					for(i = 0; excludes[i] != NULL; i++) {
						if(excludes[i]->text == NULL) continue;

						if(strcmp(excludes[i]->text, p3) == 0) break;
						if(strlen(excludes[i]->text) > 0 && excludes[i]->text[strlen(excludes[i]->text) - 1] == '/' && strstr(p3, excludes[i]->text) == p3) break;
						if(strlen(excludes[i]->text) > 0) {
							char* p4 = u_strvacat(excludes[i]->text, "/", NULL);

							if(strstr(p3, p4) == p3) {
								free(p4);
								break;
							}
							free(p4);
						}
					}

					free(p3);

					if(excludes[i] == NULL) arrput(arr, p);
				} else {
					free(p);
				}
			} else {
				free(p);
			}
		}

		io_closedir(dir);
	}

	qsort(arr, arrlen(arr), sizeof(char*), sort_xml);

	return arr;
}

void default_nav(FILE* out, const char* top, xl_node_t* element, int indent) {
	int i;

	if(element->name == NULL) return;

	if(strcmp(element->name, "link") == 0) {
		char* link;
		char* name;

		if((link = xl_get_attribute(element, "href")) == NULL) link = "https://invalid.link";
		if((name = xl_get_attribute(element, "name")) == NULL) name = "";

		link = u_path(top, link);

		for(i = 0; i < indent; i++) fprintf(out, "\t");
		fprintf(out, " - <a href=\"%s\">%s</a><br>\n", link, name);

		free(link);
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
	} else if(strcmp(element->name, "autogenerate") == 0) {
		char**	    xml;
		int	    i;
		char*	    layer;
		xl_node_t*  child;
		xl_node_t** excludes;

		if((layer = xl_get_attribute(element, "layer")) == NULL) layer = "*";

		excludes = xl_get_path(element, "exclude");

		xml = scan_xml("site/content/", "", excludes, strcmp(layer, "*") == 0 ? -0xffff : (atoi(layer) - 1));

		if(excludes != NULL) free(excludes);

		for(i = 0; i < arrlen(xml); i++) {
			xemil_t* handle;

			if((handle = xl_open_file(xml[i])) != NULL && (handle->param.new_text = handle->param.do_xinclude = 1) && xl_parse(handle)) {
				xl_node_t** nodes = xl_get_path(handle->root, "header.title");

				if(nodes != NULL && nodes[0]->text != NULL) {
					int j;

					xml[i][strlen(xml[i]) - strlen("index.xml")] = 0;

					for(j = 0; j < indent; j++) fprintf(out, "\t");
					fprintf(out, " - <a href=\"%s%s\">%s</a><br>\n", top, xml[i] + strlen("site/content/"), nodes[0]->text);

					free(nodes);
				}
			}

			if(handle != NULL) xl_close(handle);
		}

		for(i = 0; i < arrlen(xml); i++) free(xml[i]);
		arrfree(xml);
	}
}
