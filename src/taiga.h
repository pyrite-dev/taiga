#ifndef __TAIGA_H__
#define __TAIGA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#include <dirent.h>
#endif

#include <xemil.h>

#ifdef _WIN32
#define io_mkdir(x, y) _mkdir(x)
#define io_chdir(x) _chdir(x)
#define io_stat _stat

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

int action_site(int argc, char** argv);

/* help.c */
int action_help(int argc, char** argv);

/* seed.c */
int action_seed(int argc, char** argv);

/* util.c */
char* u_strvacat(const char* str, ...);
char* u_strdup(const char* str);

/* process.c */
int process(const char* top, const char* out, const char* full);

/* classic.c */
void classic_stylesheet(FILE* out, const char* top); /* also create files here if you need one */
void classic_head(FILE* out, const char* top, xl_node_t* header);
void classic_body(FILE* out, const char* top, const char* title, xl_node_t* body);

/* default.c */
void default_node(FILE* out, const char* top, xl_node_t* element, int indent);
void default_nav(FILE* out, const char* top, xl_node_t* element, int indent);

#endif
