#include "appwindow.h"

#include "libargs.h"

#include <csingleinstance.h>
#include <libapp.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <print.h>

#define BUFFER_LENGTH 4096

int onSocketInput(GIOChannel *source, GIOCondition condition, gpointer data)
{
    (void) condition;
    (void) data;

    struct sockaddr_in caddr;
    socklen_t caddr_len = sizeof(caddr);

    int fd = g_io_channel_unix_get_fd(source);
    int sock = accept(fd, (struct sockaddr*) &caddr, &caddr_len);

    char buf[BUFFER_LENGTH];
    char *cmdargs = NULL;

    // first get the command.
    while (socket_fd_gets(sock, buf, sizeof(buf)) != -1)
    {
        cmdargs = strdup(buf);

        print("Received : %s", g_strstrip(cmdargs));

        free(cmdargs);
    }

    socket_fd_close(sock);

    return true;
}

int main(int argc, char **argv)

{
    gtk_init(&argc, &argv);

    CSingleInstanceAuto *inst = csingleinst_new();
    csingleinst_open(inst, "/tmp/my_socket",
                     (GIOFunc) onSocketInput, NULL);

    if (!csingleinst_isfirst(inst))
    {
        char *cmdargs = args_to_str(argc, argv);

        socket_fd_write_all(csingleinst_sock(inst),
                            cmdargs, -1);

        socket_fd_close(csingleinst_sock(inst));

        free(cmdargs);

        return 0;
    }

    GtkWidget *window = g_object_new(TYPE_APPWINDOW, NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


