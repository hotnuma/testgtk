#include <application.h>

int main(int argc, char **argv)
{
    g_set_application_name(APP_DISPLAY_NAME);

    Application *app = application_get();
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(G_OBJECT(app));

    return status;
}


