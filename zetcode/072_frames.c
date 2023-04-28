#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkFrame");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 250);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    G_GNUC_BEGIN_IGNORE_DEPRECATIONS;

    GtkWidget *table = gtk_table_new(2, 2, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    gtk_table_set_col_spacings(GTK_TABLE(table), 10);
    gtk_container_add(GTK_CONTAINER(window), table);

    GtkWidget *item = NULL;

    item = gtk_frame_new("Shadow In");
    gtk_frame_set_shadow_type(GTK_FRAME(item), GTK_SHADOW_IN);
    gtk_table_attach_defaults(GTK_TABLE(table), item, 0, 1, 0, 1);

    item = gtk_frame_new("Shadow Out");
    gtk_frame_set_shadow_type(GTK_FRAME(item), GTK_SHADOW_OUT);
    gtk_table_attach_defaults(GTK_TABLE(table), item, 0, 1, 1, 2);

    item = gtk_frame_new("Shadow Etched In");
    gtk_frame_set_shadow_type(GTK_FRAME(item), GTK_SHADOW_ETCHED_IN);
    gtk_table_attach_defaults(GTK_TABLE(table), item, 1, 2, 0, 1);

    item = gtk_frame_new("Shadow Etched Out");
    gtk_frame_set_shadow_type(GTK_FRAME(item), GTK_SHADOW_ETCHED_OUT);
    gtk_table_attach_defaults(GTK_TABLE(table), item, 1, 2, 1, 2);

    G_GNUC_END_IGNORE_DEPRECATIONS;

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


