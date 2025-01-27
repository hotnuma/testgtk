#include <gtk/gtk.h>

void combo_selected(GtkWidget *widget, gpointer user_data)
{
    gchar *text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));
    gtk_label_set_text(GTK_LABEL(user_data), text);
    g_free(text);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkComboBox");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Ubuntu");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Arch");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Fedora");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Mint");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Gentoo");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Debian");
    gtk_box_pack_start(GTK_BOX(vbox), combo, FALSE, FALSE, 0);

    GtkWidget *label = gtk_label_new("...");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(combo), "changed",
                     G_CALLBACK(combo_selected), (gpointer) label);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


