#include "MainWindow.h"
#include <Scintilla.h>
#include <SciLexer.h>
#include <ScintillaWidget.h>

#define SendMessage(m, w, l) scintilla_send_message(sci, m, w, l)

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
    GtkWidget *editor = scintilla_new();
    ScintillaObject *sci = SCINTILLA(editor);

    scintilla_set_id(sci, 0);

    SendMessage(SCI_STYLECLEARALL, 0, 0);
    SendMessage(SCI_SETLEXER, SCLEX_CPP, 0);
    SendMessage(SCI_SETKEYWORDS, 0, (sptr_t)"int char");
    SendMessage(SCI_STYLESETFORE, SCE_C_COMMENT, 0x008000);
    SendMessage(SCI_STYLESETFORE, SCE_C_COMMENTLINE, 0x008000);
    SendMessage(SCI_STYLESETFORE, SCE_C_NUMBER, 0x808000);
    SendMessage(SCI_STYLESETFORE, SCE_C_WORD, 0x800000);
    SendMessage(SCI_STYLESETFORE, SCE_C_STRING, 0x800080);
    SendMessage(SCI_STYLESETBOLD, SCE_C_OPERATOR, 1);
    SendMessage(SCI_INSERTTEXT, 0, (sptr_t)
    "int main(int argc, char **argv) {\n"
    "    // Start up the gnome\n"
    "    gnome_init(\"stest\", \"1.0\", argc, argv);\n}"
    );

    notebookAppend(_notebook, "title1", editor, CB(_onClicked), this);
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


