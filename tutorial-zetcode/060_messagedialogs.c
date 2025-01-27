#include <gtk/gtk.h>

void show_info(GtkWidget *widget, gpointer window)
{
    (void) widget;

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Download Completed");

    gtk_window_set_title(GTK_WINDOW(dialog), "Information");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void show_error(GtkWidget *widget, gpointer window)
{
    (void) widget;

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "Error loading file");

    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void show_question(GtkWidget *widget, gpointer window)
{
    (void) widget;

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_YES_NO,
                                    "Are you sure to quit?");

    gtk_window_set_title(GTK_WINDOW(dialog), "Question");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void show_warning(GtkWidget *widget, gpointer window)
{
    (void) widget;

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_WARNING,
                                    GTK_BUTTONS_OK,
                                    "Unallowed operation");

    gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Message dialogs");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 4);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 4);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 4);
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0;

    GtkWidget *item = NULL;

    item = gtk_button_new_with_label("Info");
    gtk_grid_attach(GTK_GRID(grid), item, 0, row, 1, 1);
    g_signal_connect(G_OBJECT(item), "clicked",
                     G_CALLBACK(show_info), (gpointer) window);

    item = gtk_button_new_with_label("Warning");
    gtk_grid_attach(GTK_GRID(grid), item, 1, row, 1, 1);
    g_signal_connect(G_OBJECT(item), "clicked",
                     G_CALLBACK(show_warning), (gpointer) window);
    ++row;

    item = gtk_button_new_with_label("Question");
    gtk_grid_attach(GTK_GRID(grid), item, 0, row, 1, 1);
    g_signal_connect(G_OBJECT(item), "clicked",
                     G_CALLBACK(show_question), (gpointer) window);

    item = gtk_button_new_with_label("Error");
    gtk_grid_attach(GTK_GRID(grid), item, 1, row, 1, 1);
    g_signal_connect(G_OBJECT(item), "clicked",
                     G_CALLBACK(show_error), (gpointer) window);
    ++row;

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


