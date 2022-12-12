#include "MainWindow.h"

#include <libsocket.h>
#include <netinet/in.h>

#include <print.h>

#define BUFFER_LENGTH 4096

int MainWindow::onSocketInput(GIOChannel *source, GIOCondition)
{
    struct sockaddr_in caddr;
    socklen_t caddr_len = sizeof(caddr);

    int fd = g_io_channel_unix_get_fd(source);
    int sock = accept(fd, (struct sockaddr*) &caddr, &caddr_len);

    char buf[BUFFER_LENGTH];
    char *command = nullptr;

    // first get the command.
    while (socket_fd_gets(sock, buf, sizeof(buf)) != -1)
    {
        command = strdup(buf);
        print("Received : %s", g_strstrip(command));
        free(command);
    }

    socket_fd_close(sock);

    return true;
}

void MainWindow::_onQuit(GtkWidget*)
{
    gtk_window_close(GTK_WINDOW(_wnd));
}


