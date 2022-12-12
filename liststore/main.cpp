#include "MainWindow.h"

int main(int argc, char **argv)

{
    gtk_init(&argc, &argv);

    MainWindow *wnd = new MainWindow();
    wnd->showAll();

    gtk_main();

    return 0;
}


