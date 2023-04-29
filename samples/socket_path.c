#include <gtk/gtk.h>

#if 0
char* socket_geany_pathinit(const char *dir, const char *appname)
{
    //GdkDisplay *display = gdk_display_get_default();

    char *display_name = NULL;

    if (display_name == NULL)
        display_name = g_strdup("NODISPLAY");

    /* these lines are taken from dcopc.c in kdelibs */
    char *p;
    if ((p = strrchr(display_name, '.')) > strrchr(display_name, ':')
        && p != NULL)
        *p = '\0';

    /* remove characters that may not be acceptable in a filename */
    for (p = display_name; *p; ++p)
    {
        if (*p == ':' || *p == '/')
            *p = '_';
    }

    const char *hostname = g_get_host_name();

    char *filepath = g_strdup_printf(
                            "%s/%s_socket_%s_%s",
                            dir,
                            appname,
                            hostname,
                            display_name);

    g_free(display_name);

    return filepath;
}
#endif

char* socket_path_new(const char *appname)
{
    int uid = getuid();

    char *filepath = g_strdup_printf(
                            "/tmp/%s_socket_%d",
                            appname,
                            uid);

    return filepath;
}

int main()
{
    printf("path = %s\n", socket_path_new("app"));

    return 0;
}


