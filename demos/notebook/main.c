#include "appwindow.h"
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = g_object_new(TYPE_APPWINDOW, NULL);

    //GObject *obj = G_OBJECT(window);
    //g_print("ref %d\n",  obj->ref_count);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


