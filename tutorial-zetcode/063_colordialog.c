#include <gtk/gtk.h>

void select_font(GtkWidget *widget, gpointer label)
{
    (void) widget;

    G_GNUC_BEGIN_IGNORE_DEPRECATIONS;

    GtkWidget *dialog = gtk_color_selection_dialog_new("Font Color");
    GtkResponseType result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_OK)
    {
        GtkColorSelection *colorsel =
            GTK_COLOR_SELECTION(gtk_color_selection_dialog_get_color_selection(
                GTK_COLOR_SELECTION_DIALOG(dialog)));

        GdkColor color;
        gtk_color_selection_get_current_color(colorsel, &color);

        gtk_widget_modify_fg(GTK_WIDGET(label),
                             GTK_STATE_NORMAL,
                             &color);
    }

    gtk_widget_destroy(dialog);

    G_GNUC_END_IGNORE_DEPRECATIONS;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Color Selection Dialog");
    gtk_window_set_default_size(GTK_WINDOW(window), 280, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

    G_GNUC_BEGIN_IGNORE_DEPRECATIONS;
    GtkToolItem *font = gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), font, -1);
    G_GNUC_END_IGNORE_DEPRECATIONS;

    GtkWidget *label = gtk_label_new("ZetCode");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, FALSE, 5);

    g_signal_connect(G_OBJECT(font), "clicked",
                     G_CALLBACK(select_font), label);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


