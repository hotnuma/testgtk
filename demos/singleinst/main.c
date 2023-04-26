#include "appwindow.h"

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

    print("input %d", gettid());

    struct sockaddr_in caddr;
    socklen_t caddr_len = sizeof(caddr);

    int fd = g_io_channel_unix_get_fd(source);
    int sock = accept(fd, (struct sockaddr*) &caddr, &caddr_len);

    char buf[BUFFER_LENGTH];
    char *command = NULL;

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

int main(int argc, char **argv)

{
    print("main %d", gettid());

    gtk_init(&argc, &argv);

    CSingleInstanceAuto *inst = csingleinst_new();
    csingleinst_open(inst, "/tmp/my_socket",
                     (GIOFunc) onSocketInput, NULL);

    if (!csingleinst_isfirst(inst))
    {
        socket_fd_write_all(csingleinst_sock(inst),
                            "bla ble blie\n", -1);

        //socket_fd_close(inst.sock());

        return 0;
    }

    GtkWidget *window = g_object_new(TYPE_APPWINDOW, NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


