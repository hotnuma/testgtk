#include <gtk/gtk.h>

void button_pressed(GtkWidget *widget, gpointer window)
{
    gchar *str = g_strdup_printf("%s button clicked",
                                 gtk_button_get_label(GTK_BUTTON(widget)));

    gtk_statusbar_push(
        GTK_STATUSBAR(window),
        gtk_statusbar_get_context_id(GTK_STATUSBAR(window), str), str);

    g_free(str);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_title(GTK_WINDOW(window), "GtkStatusbar");

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);

    GtkWidget *button1;
    button1 = gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(button1, 70, 30 );
    gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 5);

    GtkWidget *button2;
    button2 = gtk_button_new_with_label("Apply");
    gtk_widget_set_size_request(button2, 70, 30 );
    gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 0);

    GtkWidget *statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(button1), "clicked",
                     G_CALLBACK(button_pressed), G_OBJECT(statusbar));
    g_signal_connect(G_OBJECT(button2), "clicked",
                     G_CALLBACK(button_pressed), G_OBJECT(statusbar));

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


