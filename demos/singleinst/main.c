#include "appwindow.h"

#include "libargs.h"

#include <csingleinstance.h>
#include <libapp.h>
#include <netinet/in.h>
#include <sys/types.h>

#include <print.h>

int on_socket_input(GIOChannel *source, GIOCondition condition, gpointer data)
{
    (void) condition;
    (void) data;

    struct sockaddr_in caddr;
    socklen_t caddr_len = sizeof(caddr);

    int fd = g_io_channel_unix_get_fd(source);
    int sock = accept(fd, (struct sockaddr*) &caddr, &caddr_len);

    CString *buffer = cstr_new_size(2048);
    int total = 0;

    while (1)
    {
        int remain;
        char *ptr = cstr_reserve_ptr(buffer, &remain);

        int num = socket_fd_gets(sock, ptr, remain + 1);

        if (num < 0)
            break;

        total += num;
    }

    socket_fd_close(sock);

    cstr_terminate(buffer, total);

    if (cstr_last(buffer) == '\n')
        cstr_chop(buffer, 1);

    print("Received : %s", c_str(buffer));

    CListAuto *list = str_to_args(c_str(buffer));

    int argc = clist_size(list);
    char **argv = (char**) clist_data(list);

    for (int i = 0; i < argc; ++i)
    {
        print("arg = \"%s\"", argv[i]);
    }

    return true;
}

int main(int argc, char **argv)

{
    gtk_init(&argc, &argv);

    c_autofree char *sockpath = socket_path_new("singleinst");

    CSingleInstanceAuto *inst = csingleinst_new();
    csingleinst_open(inst, sockpath,
                     (GIOFunc) on_socket_input, NULL);

    if (!csingleinst_isfirst(inst))
    {
        c_autofree char *cmdargs = args_to_str(argc, argv);

        socket_fd_write_all(csingleinst_sock(inst),
                            cmdargs, -1);

        socket_fd_close(csingleinst_sock(inst));

        return 0;
    }

    GtkWidget *window = g_object_new(TYPE_APPWINDOW, NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


