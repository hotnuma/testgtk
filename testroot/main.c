#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);
    gtk_window_set_title(GTK_WINDOW(window), "Test Root");

    GtkWidget *label = gtk_label_new(NULL);

    char *str = NULL;

    int uid = getuid();

    if (uid == 0)
    {
        str = g_strdup_printf ("<span font=\"14\" color=\"red\">"
                               "<b>User is root</b>"
                               "</span>");
    }
    else
    {
        str = g_strdup_printf ("<span font=\"14\" color=\"black\">"
                               "<b>User ID : %d</b>"
                               "</span>",
                               uid);
    }

    gtk_label_set_markup(GTK_LABEL(label), str);
    g_free(str);

    gtk_container_add(GTK_CONTAINER(window), label);
    gtk_widget_show(label);

    g_signal_connect(window, "destroy",
    G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show(window);

    gtk_main();

    return 0;
}


