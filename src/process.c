#include <taiga.h>

static FILE* f;

static int parse_file(const char* top, const char* full) {
	xemil_t* handle = xl_open_file(full);
	int	 st	= 1;

	handle->new_text = 1;

	if(handle != NULL && xl_parse(handle)) {
		if(handle->root == NULL || strcmp(handle->root->name, "document") != 0) {
			fprintf(stderr, "Root element has to be document\n");
			st = 0;
		}

		if(st) {
			char*	    title  = NULL;
			xl_node_t*  node   = NULL;
			xl_node_t*  header = NULL;
			xl_node_t*  body   = NULL;
			xl_node_t** nodes;
			xl_node_t** nodes2;
			int	    has_own_icon = 0;

			if(handle->root != NULL) node = handle->root->first_child;
			while(node != NULL) {
				if(node->type == XL_NODE_NODE && strcmp(node->name, "header") == 0) {
					xl_node_t* n = node->first_child;

					while(n != NULL) {
						if(n->type == XL_NODE_NODE && strcmp(n->name, "title") == 0) {
							if(title != NULL) free(title);
							title = u_strdup(n->text);
						}
						n = n->next;
					}

					header = node;
				} else if(node->type == XL_NODE_NODE && strcmp(node->name, "body") == 0) {
					body = node;
				}

				node = node->next;
			}

			if(title == NULL) title = u_strdup("Untitled");

			fprintf(f, "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
			fprintf(f, "<html>\n");
			fprintf(f, "	<head>\n");
			fprintf(f, "		<meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\">\n");
			fprintf(f, "		<title>%s</title>\n", title);

			if((nodes = xl_get_path(header, "link")) != NULL) {
				int i;

				for(i = 0; nodes[i] != NULL; i++) {
					char* rel = xl_get_attribute(nodes[i], "rel");

					if(strcmp(rel, "icon") == 0) {
						has_own_icon = 1;
						break;
					}
				}

				free(nodes);
			}

			classic_head(f, top, header);

			if(!has_own_icon && (nodes = xl_get_path(skinconf->root, "favicon")) != NULL) {
				if(nodes[0]->text != NULL) {
					char* p = u_path(top, nodes[0]->text);
					fprintf(f, "		<link rel=\"icon\" href=\"%s\">\n", p);
					free(p);
				}

				free(nodes);
			}

			fprintf(f, "	</head>\n");
			fprintf(f, "	<body>\n");
			classic_body(f, top, title, body);
			fprintf(f, "	</body>\n");
			fprintf(f, "</html>\n");

			free(title);
		}
	} else {
		fprintf(stderr, "Parse failed!\n", full);
		st = 0;
	}

	if(handle != NULL) xl_close(handle);

	return st;
}

int process(const char* top, const char* out, const char* full) {
	char* fn = strrchr(full, '/');

	if(fn != NULL) fn = fn + 1;

	if(fn != NULL) {
		char* n;
		char* p;

		fn = u_strdup(fn);
		if((n = strrchr(fn, '.')) != NULL) n[0] = 0;

		p = u_strvacat(out, fn, ".html", NULL);
		if((f = fopen(p, "w")) != NULL) {
			if(!parse_file(top, full)) {
				fclose(f);
				free(p);
				free(fn);
				return 0;
			}
			fclose(f);
		}
		free(p);

		free(fn);
	}

	return 1;
}
