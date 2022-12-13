#include <application.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    g_set_application_name("TestGtk");

    Application *app = application_get();

    gtk_window_set_default_icon_name("Application");

    g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(G_OBJECT(app));

    return EXIT_SUCCESS;
}


