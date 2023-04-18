#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 250);
    gtk_window_set_title(GTK_WINDOW(window), "GtkVBox");
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *settings = gtk_button_new_with_label("Settings");
    GtkWidget *accounts = gtk_button_new_with_label("Accounts");
    GtkWidget *loans = gtk_button_new_with_label("Loans");
    GtkWidget *cash = gtk_button_new_with_label("Cash");
    GtkWidget *debts = gtk_button_new_with_label("Debts");

    gtk_box_pack_start(GTK_BOX(vbox), settings, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), accounts, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), loans, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), cash, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), debts, TRUE, TRUE, 0);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


