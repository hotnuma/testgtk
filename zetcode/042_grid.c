#include <gtk/gtk.h>
#include <stdbool.h>

bool _visible = true;

void button_clicked(GtkWidget *grid, gpointer data)
{
    (void) data;

    GList *children = gtk_container_get_children(GTK_CONTAINER(grid));

    _visible = !_visible;

    while (children != NULL)
    {
        GtkWidget *widget = children->data;

        GValue value = G_VALUE_INIT;
        g_value_init(&value, G_TYPE_INT);
        gtk_container_child_get_property(GTK_CONTAINER(grid), widget,
                                         "top-attach", &value);
        int pos = g_value_get_int(&value);
        g_value_unset(&value);

        g_print("name : %s\n", gtk_widget_get_name(widget));
        g_print("label : %s\n", gtk_button_get_label(GTK_BUTTON(widget)));
        g_print("pos : %d\n", pos);

        if (pos == 0)
        {
            if (_visible)
                gtk_widget_show(widget);
            else
                gtk_widget_hide(widget);
        }

        children = children->next;
    }

    g_list_free (children);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Grid Widget");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0;

    GtkWidget *btn = NULL;

    btn = gtk_button_new_with_label("Button 1");
    gtk_widget_set_size_request(btn, 50, 30);
    gtk_grid_attach(GTK_GRID(grid), btn, 0, row, 1, 1);
    ++row;

    btn = gtk_button_new_with_label("Button 2");
    gtk_widget_set_hexpand(btn, TRUE);
    gtk_widget_set_vexpand(btn, TRUE);
    gtk_grid_attach(GTK_GRID(grid), btn, 0, row, 2, 1);
    ++row;
    g_signal_connect_swapped(G_OBJECT(btn), "clicked",
                             G_CALLBACK(button_clicked), G_OBJECT(grid));

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


