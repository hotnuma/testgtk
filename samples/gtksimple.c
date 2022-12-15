#include <gtk/gtk.h>

// gcc -g -O0 -o gtksimple gtksimple.c `pkg-config --libs --cflags gtk+-3.0`

/*

valgrind --leak-check=full --suppressions=./{glib,gtk,gtksimple}.supp ./gtksimple

valgrind --leak-check=full --error-limit=no --num-callers=20 \
--suppressions=/usr/share/glib-2.0/valgrind/glib.supp \
--suppressions=/usr/share/gtk-3.0/valgrind/gtk.supp \
--suppressions=./gtksimple.supp \
./gtksimple

*/

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show(window);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  

    gtk_main();

    return 0;
}


