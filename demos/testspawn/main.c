#include <gtk/gtk.h>
#include "spawn.h"

static GtkTextIter iter;
static GtkTextBuffer *buffer;

static void output_append(const gchar *str)
{
    gtk_text_buffer_insert(buffer, &iter, str, -1);
}

static void build_iofunc(GString *string, GIOCondition condition, gpointer data)
{
    (void) data;

    if (condition & (G_IO_IN | G_IO_PRI))
    {
        //process_build_output_line(string->str,
        //    (GPOINTER_TO_INT(data)) ? COLOR_DARK_RED : COLOR_BLACK);

        output_append(string->str);
    }
}

static void build_exit_cb(GPid child_pid, gint status, gpointer user_data)
{
    (void) child_pid;
    (void) status;
    (void) user_data;

//	show_build_result_message(!SPAWN_WIFEXITED(status) || SPAWN_WEXITSTATUS(status) != EXIT_SUCCESS);
//	utils_beep();

//	build_info.pid = 0;
//	/* enable build items again */
//	build_menu_update(NULL);
//	ui_progress_bar_stop();
}

void exec_cmd()
{
    GError *error = NULL;

    if (!spawn_with_callbacks(NULL,
                              "/usr/local/bin/testout",
                              NULL,
                              NULL,
                              0,
                              NULL,
                              NULL,
                              build_iofunc,
                              GINT_TO_POINTER(0),
                              0,
                              build_iofunc,
                              GINT_TO_POINTER(1),
                              0,
                              build_exit_cb,
                              NULL,
                              NULL,
                              &error))
    {
        g_error_free(error);
    }
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_title(GTK_WINDOW(window), "GtkTextView");

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scroll);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scroll),
                                        GTK_SHADOW_IN);

    GtkWidget *view = gtk_text_view_new();

    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    exec_cmd();

    gtk_main();

    return 0;
}


