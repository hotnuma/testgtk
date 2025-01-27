#include "appwindow.h"
#include "etkwidget.h"
#include <cfile.h>

GtkWidget* window_get_current_page(AppWindow *window);

void _window_action_new(AppWindow *window)
{
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, true);
    gtk_widget_set_vexpand(scroll, true);

    GtkWidget *textview = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scroll), textview);

    gtk_widget_show_all(scroll);

    etk_notebook_append(window->notebook,
                        "title1", scroll, true,
                        G_CALLBACK(_window_action_close_tab), GTK_WIDGET(window));
}

void _window_action_open(AppWindow *window)
{
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new(
        "Open File",
        GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "gtk-cancel",
        GTK_RESPONSE_CANCEL,
        "gtk-open",
        GTK_RESPONSE_ACCEPT,
        NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        char *filename;

        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        CStringAuto *buffer = cstr_new_size(1024);

        if (!file_read(buffer, filename))
        {
            g_print("read error : %s\n", filename);
        }
        else
        {
            GtkWidget *textview = window_get_current_page(window);
            GtkTextBuffer *textbuffer = gtk_text_view_get_buffer(
                                                    GTK_TEXT_VIEW(textview));
            gtk_text_buffer_set_text(textbuffer, c_str(buffer), -1);
        }

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

GtkWidget* window_get_current_page(AppWindow *window)
{
    GtkWidget *notebook = GTK_WIDGET(window->notebook);

    int num = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));
    GtkWidget *page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), num);

    if (!page)
        return NULL;

    return gtk_bin_get_child(GTK_BIN(page));
}

void _window_action_close_tab(AppWindow *window)
{
    GtkWidget *notebook = window->notebook;

    int count = gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook));

    // exit program
    if (count == 1)
    {
        gtk_window_close(GTK_WINDOW((window)));

        //gtk_widget_destroy(GTK_WIDGET(window));

        return;
    }

    // close page
    int curr = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));
    gtk_notebook_remove_page(GTK_NOTEBOOK(notebook), curr);
}


