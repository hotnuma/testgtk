#include "appwindow.h"

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    g_object_new(TYPE_APPWINDOW, NULL);

    gtk_main();

    return 0;
}


