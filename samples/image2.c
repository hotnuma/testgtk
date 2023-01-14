#include <gtk/gtk.h>

#define filepath "/usr/share/icons/hicolor/48x48/apps/geany.png"

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Image");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    GdkPixbuf *src = gdk_pixbuf_new_from_file(filepath, NULL);

    if (src)
    {
        gdk_pixbuf_saturate_and_pixelate(src, src, 0.5, FALSE);

        GtkWidget *image = gtk_image_new_from_pixbuf(src);
        gtk_container_add(GTK_CONTAINER(window), image);
        g_object_unref(src);
    }

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


