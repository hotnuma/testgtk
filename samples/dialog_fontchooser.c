#include <gtk/gtk.h>

static void font_dialog_ok_callback(GtkFontChooserDialog *chooser_dialog,
                                    gpointer user_data)
{
    (void) user_data;

    gchar *font_name;
    font_name = gtk_font_chooser_get_font(GTK_FONT_CHOOSER(chooser_dialog));
    g_message("The font you chose is: %s", font_name);
    g_free(font_name);
}

int main (int argc, char *argv[])
{
    GtkWidget *window;
    GtkFontChooserDialog *font_chooser_dialog;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Font Dialog");

    font_chooser_dialog = gtk_font_chooser_dialog_new("Choose a font", GTK_WINDOW(window));
    gtk_window_set_modal(GTK_WINDOW(font_chooser_dialog), TRUE);
    g_signal_connect(GTK_DIALOG(font_chooser_dialog), "response", G_CALLBACK(font_dialog_ok_callback), NULL);
    gtk_widget_show_all(GTK_WIDGET(font_chooser_dialog));

    gtk_main();

    return 0;
}

