#ifndef __TAIGA_H__
#define __TAIGA_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include <xemil.h>
#include <md4c.h>
#include <stb_ds.h>

#ifdef _WIN32
#define io_mkdir(x, y) _mkdir(x)
#define io_chdir(x) _chdir(x)
#define io_stat _stat

#define IO_DIR void
struct io_dirent {
	int  d_namlen;
	char d_name[512]; /* seems good enough for windows */
};
IO_DIR*		  io_opendir(const char* path);
struct io_dirent* io_readdir(IO_DIR* dir);
void		  io_closedir(IO_DIR* dir);

#define IO_S_ISDIR(m) ((m) & _S_IFDIR)
#else
#define io_mkdir mkdir
#define io_chdir chdir
#define io_stat stat

#define IO_S_ISDIR(m) ((m) & S_IFDIR)

#define IO_DIR DIR
#define io_dirent dirent
#define io_opendir opendir
#define io_readdir readdir
#define io_closedir closedir
#endif

/* action/site.c */
extern xemil_t* skinconf;
extern void (*site_stylesheet)(FILE* out, const char* top); /* also create files here if you need one */
extern void (*site_head)(FILE* out, const char* top, xl_node_t* header, const char* input);
extern void (*site_body)(FILE* out, const char* top, const char* title, xl_node_t* body, const char* input);

int action_site(int argc, char** argv);

/* action/help.c */
int action_help(int argc, char** argv);

/* action/seed.c */
int action_seed(int argc, char** argv);

/* action/markdown.c */
int action_markdown(int argc, char** argv);

/* action/markdown_dir.c */
int action_markdown_dir(int argc, char** argv);

/* util.c */
char* u_strvacat(const char* str, ...);
char* u_strdup(const char* str);
char* u_path(const char* top, const char* path);
char* u_http_path(const char* top, const char* path);
int   u_image_size(const char* top, const char* path, char* (*path_func)(const char* top, const char* path), int* w, int* h);
char* u_section_id(xl_node_t* node);
char* u_path_combine(const char* a, const char* b);
char* u_path_sanitize(const char* a);

/* crc.c */
unsigned int crc32(void* input, unsigned int len);

/* process.c */
int process(const char* top, const char* out, const char* full);

/* default.c */
void default_head(FILE* out, const char* top, xl_node_t* element, const char* input, int indent);
void default_body(FILE* out, const char* top, xl_node_t* element, const char* input, int spec, int pre, int indent); /* pass non-zero to spec if you want links to be relative from top */
void default_nav(FILE* out, const char* top, xl_node_t* element, const char* input, int indent);

/*** skins ***/

/* they should share compatible class/id names for elements but
 * they're not documented... oh well
 */

/* skin/classic.c */
void classic_stylesheet(FILE* out, const char* top);
void classic_head(FILE* out, const char* top, xl_node_t* header, const char* input);
void classic_body(FILE* out, const char* top, const char* title, xl_node_t* body, const char* input);

/* skin/simple.c */
void simple_stylesheet(FILE* out, const char* top);
void simple_head(FILE* out, const char* top, xl_node_t* header, const char* input);
void simple_body(FILE* out, const char* top, const char* title, xl_node_t* body, const char* input);

#endif
