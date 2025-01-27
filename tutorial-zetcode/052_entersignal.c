#include <gtk/gtk.h>

void enter_button(GtkWidget *widget, gpointer data)
{
    (void) data;

    //GdkColor col = {0, 27000, 30000, 35000};
    GdkColor col = {0, 65535, 0, 0};
    gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &col);

//    GdkRGBA color = {1.0, .0, .0, 1.0};
//    gtk_widget_override_background_color(widget, GTK_STATE_NORMAL, &color);

#if 0
    // You need an object to store css information: the CSS Provider
    GtkCssProvider * css = gtk_css_provider_new();
    // Load CSS into the object ("-1" says, that the css string is \0-terminated)
    gtk_css_provider_load_from_data(css, "* { background-image:none; background-color:red;}",-1,NULL);

    // The "Style context" manages CSS providers (as there can be more of them)
    GtkStyleContext * context = gtk_widget_get_style_context(widget);
    // So we want to add our CSS provider (that contains the CSS) to that "style manager".
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);


    // I'm not sure, if you need this. I took it from mame89's code
    g_object_unref (css);
#endif

}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Enter signal");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *btn = gtk_button_new_with_label("Button");
    gtk_widget_set_size_request(btn, 70, 30);

    gtk_grid_attach(GTK_GRID(grid), btn, 0, 0, 1, 1);

    g_signal_connect(G_OBJECT(btn), "enter",
                     G_CALLBACK(enter_button), NULL);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


