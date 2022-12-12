#include "MainWindow.h"

#include <print.h>

void MainWindow::_onClicked(GtkWidget*)
{
    print("clicked");

    gtk_notebook_remove_page(
        GTK_NOTEBOOK(_notebook),
        gtk_notebook_get_current_page(GTK_NOTEBOOK(_notebook)));

}

void MainWindow::_actionNew()
{
    //GtkWidget *page = gtk_label_new("page1");

    GtkWidget *scrolled = gtk_scrolled_window_new(nullptr, nullptr);
    gtk_widget_set_hexpand(scrolled, true);
    gtk_widget_set_vexpand(scrolled, true);

    GtkWidget *textview = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled), textview);

    notebookAppend(_notebook, "title1", scrolled, CB(_onClicked), this);
}

void MainWindow::_actionOpen(GtkWidget*)
{
    print("clicked");

    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new(
        "Open File",
        GTK_WINDOW(_wnd),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "gtk-cancel",
        GTK_RESPONSE_CANCEL,
        "gtk-open",
        GTK_RESPONSE_ACCEPT,
        nullptr);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        char *filename;

        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        print(filename);

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void MainWindow::_actionQuit(GtkWidget*)
{
    gtk_window_close(GTK_WINDOW(_wnd));
}


