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

/* site.c */
extern xemil_t* skinconf;
extern void (*site_stylesheet)(FILE* out, const char* top); /* also create files here if you need one */
extern void (*site_head)(FILE* out, const char* top, xl_node_t* header);
extern void (*site_body)(FILE* out, const char* top, const char* title, xl_node_t* body);

int action_site(int argc, char** argv);

/* help.c */
int action_help(int argc, char** argv);

/* seed.c */
int action_seed(int argc, char** argv);

/* util.c */
char* u_strvacat(const char* str, ...);
char* u_strdup(const char* str);
char* u_path(const char* top, const char* path);
char* u_http_path(const char* top, const char* path);
int   u_image_size(const char* top, const char* path, char* (*path_func)(const char* top, const char* path), int* w, int* h);

/* process.c */
int process(const char* top, const char* out, const char* full);

/* default.c */
void default_head(FILE* out, const char* top, xl_node_t* element, int indent);
void default_body(FILE* out, const char* top, xl_node_t* element, int spec, int indent); /* pass non-zero to spec if you want links to be relative from top */
void default_nav(FILE* out, const char* top, xl_node_t* element, int indent);

/*** skins ***/

/* they should share compatible class/id names for elements but
 * they're not documented... oh well
 */

/* classic.c */
void classic_stylesheet(FILE* out, const char* top);
void classic_head(FILE* out, const char* top, xl_node_t* header);
void classic_body(FILE* out, const char* top, const char* title, xl_node_t* body);

/* simple.c */
void simple_stylesheet(FILE* out, const char* top);
void simple_head(FILE* out, const char* top, xl_node_t* header);
void simple_body(FILE* out, const char* top, const char* title, xl_node_t* body);

#endif
