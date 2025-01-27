#include <gtk/gtk.h>
#include <Scintilla.h>
#include <SciLexer.h>
#include <ScintillaWidget.h>
#include <stdbool.h>

#define SendMessage(m, w, l) scintilla_send_message(sci, m, w, l)

static void destroy(GtkWidget *widget, gpointer data)
{
    (void) widget;
    (void) data;

    gtk_main_quit();
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

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


    gtk_grid_attach(GTK_GRID(grid), editor, 0, 0, 1, 1);
    gtk_widget_set_hexpand(editor, true);
    gtk_widget_set_vexpand(editor, true);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}


