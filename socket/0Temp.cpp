#if 0

G_GNUC_UNUSED gushort socket_port

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_LENGTH 4096

gboolean socket_lock_input_cb(GIOChannel *source,
                              GIOCondition,
                              gpointer)
{
    //GtkWidget *window = (GtkWidget*) data;

    struct sockaddr_in caddr;
    socklen_t caddr_len = sizeof(caddr);

    int fd = g_io_channel_unix_get_fd(source);
    int sock = accept(fd, (struct sockaddr*) &caddr, &caddr_len);

    char buf[BUFFER_LENGTH];
    char *command = nullptr;

    // first get the command.
    while (socket_fd_gets(sock, buf, sizeof(buf)) != -1)
    {
        command = g_strdup(buf);
        print("Received IPC command from remote instance: %s", g_strstrip(command));
        g_free(command);

    }

    socket_fd_close(sock);

    return true;
}

gboolean socket_lock_input_cb(GIOChannel *source, GIOCondition condition, gpointer data)
{
    int fd, sock;
    char buf[BUFFER_LENGTH];
    char *command = NULL;
    struct sockaddr_in caddr;
    socklen_t caddr_len = sizeof(caddr);
    GtkWidget *window = (GtkWidget*) data;
    gboolean popup = FALSE;

    fd = g_io_channel_unix_get_fd(source);
    sock = accept(fd, (struct sockaddr *)&caddr, &caddr_len);

    /* first get the command */
    while (_socket_fd_gets(sock, buf, sizeof(buf)) != -1)
    {
        command = g_strdup(buf);
        print("Received IPC command from remote instance: %s", g_strstrip(command));
        g_free(command);

    }

    if (popup)
    {
        #if 0
        //#ifdef GDK_WINDOWING_X11
        GdkWindow *x11_window = gtk_widget_get_window(window);

        /* Set the proper interaction time on the window. This seems necessary to make
         * gtk_window_present() really bring the main window into the foreground on some
         * window managers like Gnome's metacity.
         * Code taken from Gedit. */
        if (GDK_IS_X11_WINDOW(x11_window))
        {
            gdk_x11_window_set_user_time(x11_window, gdk_x11_get_server_time(x11_window));
        }
        #endif

        gtk_window_present(GTK_WINDOW(window));
    }

    socket_fd_close(sock);

    return TRUE;
}

void path_init()
{
    char *display_name = NULL;
    const char *hostname = g_get_host_name();
    GdkDisplay *display = gdk_display_get_default();
    char *p;

    if (display_name == NULL)
        display_name = g_strdup("NODISPLAY");

    /* these lines are taken from dcopc.c in kdelibs */
    if ((p = strrchr(display_name, '.')) > strrchr(display_name, ':') && p != NULL)
        *p = '\0';

    /* remove characters that may not be acceptable in a filename */
    for (p = display_name; *p; p++)
    {
        if (*p == ':' || *p == '/')
            *p = '_';
    }

    //if (socket_info.file_name == NULL)
    //    socket_info.file_name = g_strdup_printf("/tmp/geany_socket_%s_%s",
    //        hostname, display_name);

    g_free(display_name);

}

static void handle_input_filename(const char *buf)
{
    char *utf8_filename, *locale_filename;

    /* we never know how the input is encoded, so do the best auto detection we can */
    if (! g_utf8_validate(buf, -1, NULL))
        utf8_filename = encodings_convert_to_utf8(buf, -1, NULL);
    else
        utf8_filename = g_strdup(buf);

    locale_filename = utils_get_locale_from_utf8(utf8_filename);
    if (locale_filename)
    {
        if (g_str_has_suffix(locale_filename, ".geany"))
        {
            if (project_ask_close())
                main_load_project_from_command_line(locale_filename, TRUE);
        }
        else
            main_handle_filename(locale_filename);
    }

    g_free(utf8_filename);
    g_free(locale_filename);
}

static char *build_document_list(void)
{
    GString *doc_list = g_string_new(NULL);
    guint i;
    const char *filename;

    foreach_document(i)
    {
        filename = DOC_FILENAME(documents[i]);
        g_string_append(doc_list, filename);
        g_string_append_c(doc_list, '\n');
    }
    return g_string_free(doc_list, FALSE);
}

#endif


