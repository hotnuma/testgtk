#include "libargs.h"

#include <cstring.h>
#include <string.h>
#include <print.h>

#include <unistd.h>
#include <glib.h>

char* socket_path_new(const char *appname)
{
    int uid = getuid();

    char *filepath = g_strdup_printf(
                            "/tmp/%s_socket_%d",
                            appname,
                            uid);

    return filepath;
}

void clist_split(CList *cslist, const char *str, const char *sep,
                 bool keepEmptyParts, bool sensitive)
{
    clist_clear(cslist);

    int slen = strlen(sep);

    const char *c = str;
    int len = 0;

    while (1)
    {
        if (*c == '\0')
        {
            len = c - str;

            if (len || keepEmptyParts)
                clist_append(cslist, strndup(str, len));

            break;
        }

        if (sensitive)
        {
            if (strncmp(c, sep, slen) == 0)
            {
                len = c - str;

                if (len > 0 || keepEmptyParts)
                    clist_append(cslist, strndup(str, len));

                c += slen;
                str = c;

                continue;
            }
        }
        else
        {
            if (strncasecmp(c, sep, slen) == 0)
            {
                len = c - str;

                if (len > 0 || keepEmptyParts)
                    clist_append(cslist, strndup(str, len));

                c += slen;
                str = c;

                continue;
            }
        }

        ++c;
    }
}

char* args_to_str(int argc, char **argv)
{
    if (argc < 1)
        return NULL;

    int len = 0;
    for (int i = 0; i < argc; ++i)
    {
        if (i > 0)
            ++len;

        len += strlen(argv[i]);
    }

    char *result = (char*) malloc((len + 2) * sizeof(char));
    char *p = result;

    for (int i = 0; i < argc; ++i)
    {
        if (i > 0)
        {
            *p = '|';
            ++p;
        }

        strcpy(p, argv[i]);
        p += strlen(argv[i]);
    }

    result[len] = '\n';
    ++len;
    result[len] = '\0';

    return result;
}

CList* str_to_args(const char *str)
{
    if (!str || !*str)
        return NULL;

    CList *list = clist_new(10, (CDeleteFunc) free);
    clist_split(list, str, "|", true, true);

    return list;
}


