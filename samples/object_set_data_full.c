#include <gtk/gtk.h>

static void on_button_clicked(GtkWidget *widget, gpointer data)
{
    (void) widget;
    (void) data;

    const char *val = g_object_get_data(G_OBJECT(widget), "custom-data");

    if (!val)
        return;

    g_print("clicked : %s\n", val);
}

void my_free(void *ptr)
{
    if (!ptr)
        return;

    g_print("free : %s\n", (const char*) ptr);

    free(ptr);
}

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

    GtkWidget *button = gtk_button_new_with_label("Read data");
    g_object_set_data_full(G_OBJECT(button), "custom-data",
                           g_strdup("bla"), my_free);
    g_signal_connect(GTK_BUTTON(button), "clicked",
                     G_CALLBACK(on_button_clicked), NULL);

    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}


