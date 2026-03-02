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
