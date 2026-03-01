#ifndef __TAIGA_H__
#define __TAIGA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

/* site.c */
int action_site(int argc, char** argv);

/* help.c */
int action_help(int argc, char** argv);

/* seed.c */
int action_seed(int argc, char** argv);

#endif
