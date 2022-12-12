#include <gtk/gtk.h>
#include <application.h>

int main(int argc, char **argv)
{
    g_set_application_name("Application");

    Application *app = application_get();

    gtk_window_set_default_icon_name("Application");

    g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(G_OBJECT(app));

    return EXIT_SUCCESS;
}

//#include <gtk/gtk.h>

//int main(int argc, char *argv[]) {

//  GtkWidget *window;

//  gtk_init(&argc, &argv);

//  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//  gtk_widget_show(window);

//  g_signal_connect(window, "destroy",
//      G_CALLBACK(gtk_main_quit), NULL);

//  gtk_main();

//  return 0;
//}
