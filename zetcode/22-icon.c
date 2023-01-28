#include <gtk/gtk.h>

GdkPixbuf* create_pixbuf(const gchar *filename)
{
    GError *error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, &error);

    if (!pixbuf)
    {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }

    return pixbuf;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Icon");
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GdkPixbuf *pix = create_pixbuf("/usr/share/icons/hicolor/16x16/apps/geany.png");
    if (pix)
    {
        gtk_window_set_icon(GTK_WINDOW(window), pix);
        g_object_unref(pix);
    }

    gtk_widget_show(window);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}


