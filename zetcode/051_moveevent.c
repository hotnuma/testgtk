#include <gtk/gtk.h>

void configure_callback(GtkWindow *window, GdkEvent *event, gpointer data)
{
    (void) data;

    int x = event->configure.x;
    int y = event->configure.y;

    GString *buf = g_string_new(NULL);
    g_string_printf(buf, "%d, %d", x, y);

    gtk_window_set_title(window, buf->str);

    g_string_free(buf, TRUE);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    gtk_widget_add_events(GTK_WIDGET(window), GDK_CONFIGURE);
    g_signal_connect(G_OBJECT(window), "configure-event",
                     G_CALLBACK(configure_callback), NULL);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


