#ifndef __TAIGA_H__
#define __TAIGA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#include <dirent.h>
#endif

#ifdef _WIN32
#define io_mkdir(x,y) _mkdir(x)
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
int action_site(int argc, char** argv);

/* help.c */
int action_help(int argc, char** argv);

/* seed.c */
int action_seed(int argc, char** argv);

/* util.c */
char* u_strvacat(const char* str, ...);

#endif
