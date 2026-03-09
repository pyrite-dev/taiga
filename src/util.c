#include <taiga.h>

char* u_strvacat(const char* str, ...) {
	va_list	    va;
	int	    len = 0;
	const char* s;
	char*	    r;

	len += strlen(str);
	va_start(va, str);
	while((s = va_arg(va, const char*)) != NULL) len += strlen(s);
	va_end(va);

	r = malloc(len + 1);

	strcpy(r, str);
	va_start(va, str);
	while((s = va_arg(va, const char*)) != NULL) strcat(r, s);
	va_end(va);

	return r;
}

char* u_strdup(const char* str) {
	char* s = malloc(strlen(str) + 1);

	strcpy(s, str);

	return s;
}

char* u_path(const char* top, const char* path) {
	if(strlen(path) > 3 && strstr(path, "://") != NULL) return u_strdup(path); /* link - return as is */
	if(strlen(path) > 2 && memcmp(path, "./", 2) == 0) return u_strdup(path);  /* current directory - probably intended */
	if(strlen(path) > 3 && memcmp(path, "../", 2) == 0) return u_strdup(path); /* parent directory - also probably intended */

	return u_strvacat(top, path, NULL); /* otherwise, concat */
}

char* u_http_path(const char* top, const char* path) {
	if(strlen(path) > 3 && strstr(path, "://") != NULL) return u_strdup(path); /* link - return as is */

	return u_strvacat(top, "build/", path, NULL); /* otherwise, concat */
}

/* reason why this exists, is because IE6 has bugs with PNG transparency
 * and script i wrote, needs image size or it (sometimes) breaaks how it's shown.
 */
int u_image_size(const char* top, const char* path, char* (*path_func)(const char* top, const char* path), int* w, int* h) {
	char* p;
	int   ch;
	FILE* f;
	int   st = 0;

	p = path_func(top, path);

	if(strlen(p) > 3 && strstr(p, "://") != NULL) {
		free(p);
		return 0;
	}

	if((f = fopen(p, "rb")) != NULL) {
		unsigned char buffer[512];
		unsigned char png_sig[16] = {
		    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a,
		    0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52};
		unsigned char gif_sig[6] = {
		    0x47, 0x49, 0x46, 0x38, 0x39, 0x61}; /* GIF89a */

		fseek(f, 0, SEEK_SET);
		if(fread(buffer, 1, 16, f) == 16 && memcmp(buffer, png_sig, 16) == 0 && fread(buffer, 1, 13, f) == 13) {
			int i;

			*w = 0;
			*h = 0;

			for(i = 0; i < 4; i++) {
				*w = (*w) << 8;
				*w |= buffer[i + 0];

				*h = (*h) << 8;
				*h |= buffer[i + 4];
			}

			st = 1;
		}

		fseek(f, 0, SEEK_SET);
		if(fread(buffer, 1, 6, f) == 6 && memcmp(buffer, gif_sig, 6) == 0 && fread(buffer, 1, 4, f) == 4) {
			int i;

			*w = 0;
			*h = 0;

			for(i = 0; i < 2; i++) {
				*w = (*w) << 8;
				*w |= buffer[1 - i + 0];

				*h = (*h) << 8;
				*h |= buffer[1 - i + 2];
			}

			st = 1;
		}

		fclose(f);
	}

	free(p);

	return st;
}

char* u_section_id(xl_node_t* node) {
	char* name;
	char* id;

	if((name = xl_get_attribute(node, "title")) == NULL) return NULL;

	if((id = xl_get_attribute(node, "id")) != NULL) id = u_strdup(id);
	if(id == NULL) {
		int	   unique = 0;
		xl_node_t* child  = node->parent->first_child;

		while(child != NULL) {
			if(child == node) break;

			if(child->type == XL_NODE_NODE && child->name != NULL && strcmp(child->name, "section") == 0) unique++;
			child = child->next;
		}

		id = malloc(64);

		sprintf(id, "section%d-%d", unique, crc32(name, strlen(name)));
	}

	return id;
}
