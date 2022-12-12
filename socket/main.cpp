#include "MainWindow.h"

#include <CSingleInstance.h>
#include <libapp.h>

#include <print.h>

int main(int argc, char **argv)

{
    setbuf(stdout, 0);

    gtk_init(&argc, &argv);

    CSingleInstance inst;
    inst.open("/tmp/my_socket",
              (GIOFunc) MainWindow::onSocketInputCB);

    if (!inst.isFirst())
    {
        socket_fd_write_all(inst.sock(), "bla ble blie\n");

        //socket_fd_close(inst.sock());

        return 0;
    }

    MainWindow *wnd1 = new MainWindow();
    wnd1->showAll();

    gtk_main();

    return 0;
}


