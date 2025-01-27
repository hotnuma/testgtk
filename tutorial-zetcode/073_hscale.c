#include <gtk/gtk.h>

void value_changed(GtkRange *range, gpointer win)
{
    gdouble val = gtk_range_get_value(range);

    gchar *str = g_strdup_printf("%.f", val);
    gtk_label_set_text(GTK_LABEL(win), str);

    g_free(str);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 250);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_title(GTK_WINDOW(window), "GtkHScale");

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0;

    GtkAdjustment *hadjustment = gtk_adjustment_new(50, 0, 100, 1, 10, 0);
    GtkWidget *hscale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, GTK_ADJUSTMENT(hadjustment));
    gtk_scale_set_draw_value(GTK_SCALE(hscale), FALSE);
    gtk_widget_set_size_request(hscale, 150, -1);
    gtk_grid_attach(GTK_GRID(grid), hscale, 0, row, 1, 1);

    GtkWidget *label = gtk_label_new("...");
    gtk_grid_attach(GTK_GRID(grid), label, 1, row, 1, 1);

    g_signal_connect(hscale, "value-changed",
                     G_CALLBACK(value_changed), label);

    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


