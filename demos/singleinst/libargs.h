#ifndef LIBARGS_H
#define LIBARGS_H

#include <clist.h>
#include <stdbool.h>

void clist_split(CList *cslist, const char *str, const char *sep,
                 bool keepEmptyParts, bool sensitive);

char* args_to_str(int argc, char **argv);
CList* str_to_args(const char *str);

#endif // LIBARGS_H


