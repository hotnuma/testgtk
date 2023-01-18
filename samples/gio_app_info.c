#include <gio/gio.h>
#include <locale.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>

static gint _sort_app_infos(gconstpointer a, gconstpointer b)
{
    return strcasecmp(g_app_info_get_id(G_APP_INFO(a)),
                          g_app_info_get_id(G_APP_INFO(b)));
}

void _print_csv(const char *str, bool with_tab)
{
    if (with_tab)
        printf("\t");

    if (str)
        printf("%s", str);
}

int main()
{
    bool format_csv = true;

    GList *all = g_app_info_get_all();
    all = g_list_sort(all, _sort_app_infos);

    for (GList *lp = all; lp; lp = lp->next)
    {
        GAppInfo *info = (GAppInfo*) lp->data;

        if (format_csv)
        {
            _print_csv(g_app_info_get_id(info), false);
            _print_csv(g_app_info_get_name(info), true);
            _print_csv(g_app_info_get_description(info), true);
            _print_csv(g_app_info_get_executable(info), true);
            printf("\n");

            continue;
        }

        printf("------------------------------------------------------------\n");

        const gchar *str = NULL;

        str = g_app_info_get_id(info);
        if (str)
            printf("Id : %s\n", str);

        str = g_app_info_get_name(info);
        if (str)
            printf("Name : %s\n", str);

        str = g_app_info_get_description(info);
        if (str)
            printf("Desc : %s\n", str);

        str = g_app_info_get_executable(info);
        if (str)
            printf("Exec : %s\n", str);

    }

    g_list_free_full(all, g_object_unref);

    return 0;
}


