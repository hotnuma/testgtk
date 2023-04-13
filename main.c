#include <gtk/gtk.h>
//#include <glib-object.h>

static void button_clicked(GtkWidget *widget, gpointer data)
{
    (void) widget;
    (void) data;

    g_print("Button clicked\n");
}

static void check_button_toggled(GtkWidget *checkbutton, gpointer data)
{
    (void) data;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton)))
    {
        g_print("%s toggled on\n", gtk_button_get_label(GTK_BUTTON(checkbutton)));
    }
    else
    {
        g_print("%s toggled off\n", gtk_button_get_label(GTK_BUTTON(checkbutton)));
    }
}

static void color_set(GtkWidget *widget, gpointer user_data)
{
    (void) user_data;

    g_print("%s\n", G_OBJECT_TYPE_NAME(widget));

    GdkRGBA rgba;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widget), &rgba);
}

static void combobox_changed(GtkWidget *widget, gpointer data)
{
    (void) data;

    const char *text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));

    printf("%s\n", text);
}

static void entry_activated(GtkWidget *widget, gpointer data)
{
    (void) data;

    g_print("Entry text: '%s'\n", gtk_entry_get_text(GTK_ENTRY(widget)));
}

static void file_selected(GtkWidget *widget, gpointer data)
{
    (void) data;

    g_print("Selected file: %s",
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget)));
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Grid Widget");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 6);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0;
    int col = 0;

    GtkWidget *widget = NULL;
    int w = 80;
    int h = 30;

    widget = gtk_app_chooser_button_new("text/plain");
    gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
    ++col;

    widget = gtk_button_new_with_label("Button");
    gtk_widget_set_size_request(widget, w, h);
    gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
    g_signal_connect(GTK_BUTTON(widget), "clicked",
                     G_CALLBACK(button_clicked), NULL);
    ++col;

    widget = gtk_check_button_new_with_label("Check");
    gtk_widget_set_size_request(widget, w, h);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
    gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
    g_signal_connect(widget, "toggled",
                     G_CALLBACK(check_button_toggled), NULL);
    ++col;

    widget = gtk_color_button_new();
    gtk_widget_set_size_request(widget, w, h);
    gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
    g_signal_connect(widget, "color-set",
                     G_CALLBACK(color_set), NULL);
    col = 0;
    ++row;

    GtkListStore *liststore = gtk_list_store_new(1, G_TYPE_STRING);
    GtkTreeIter iter;

    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, "Ubuntu", -1);

    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, "Debian", -1);

    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, "Raspian", -1);

    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, "Sabayon", -1);

    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, "CentOS", -1);

    widget = gtk_combo_box_new_with_model(GTK_TREE_MODEL(liststore));
    gtk_widget_set_size_request(widget, w, h);
    gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);

    GtkCellRenderer *cellrenderertext = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(widget), cellrenderertext, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(widget), cellrenderertext, "text", 0, NULL);

    gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
    col = 0;
    ++col;

    widget = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "Oak");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "Birch");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "Sycamore");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), "Willow");
    gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
    gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
    g_signal_connect(widget, "changed",
                     G_CALLBACK(combobox_changed), NULL);
    ++col;

    widget = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(widget), "A Text Entry Widget");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widget), "Placeholder Text");
    gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
    g_signal_connect(GTK_ENTRY(widget), "activate",
                     G_CALLBACK(entry_activated), NULL);
    ++col;

    widget = gtk_file_chooser_button_new("FileChooserButton",
                                         GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
    g_signal_connect(widget, "file-set",
                     G_CALLBACK(file_selected), NULL);
    ++col;

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


