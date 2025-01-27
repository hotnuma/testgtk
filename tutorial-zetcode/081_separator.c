#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkHSeparator");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *label1;
    label1 = gtk_label_new("Zinc is a moderately reactive, blue gray metal.");
    gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, TRUE, 0);

    GtkWidget *hseparator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox), hseparator, FALSE, TRUE, 10);

    GtkWidget *label2;
    label2 = gtk_label_new("Copper is an essential trace nutrient to all high"
                           " plants and animals.");
    gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, TRUE, 0);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                             G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


