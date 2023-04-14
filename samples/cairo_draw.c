#include <gtk/gtk.h>
#include <stdbool.h>
#include <cairo.h>

gboolean on_draw(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    (void) event;
    (void) data;

    GdkWindow *window = gtk_widget_get_window(widget);
    cairo_region_t *cairoRegion = cairo_region_create();

    GdkDrawingContext *drawingContext;
    drawingContext = gdk_window_begin_draw_frame(window, cairoRegion);

    cairo_t *cr = gdk_drawing_context_get_cairo_context(drawingContext);

    // draw something
    cairo_move_to(cr, 30, 30);
    cairo_set_font_size(cr, 15);
    cairo_show_text(cr, "hello world");

    gdk_window_end_draw_frame(window,drawingContext);

    cairo_region_destroy(cairoRegion);

    return false;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWindow *window = (GtkWindow*) gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(window, "Drawing");
    gtk_window_set_position(window, GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(window, 300, 200);

    GtkDrawingArea *drawingArea = (GtkDrawingArea*) gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), (GtkWidget*) drawingArea);

    g_signal_connect((GtkWidget*) drawingArea, "draw",
                     G_CALLBACK(on_draw), NULL);

    g_signal_connect(window, "destroy", gtk_main_quit, NULL);

    gtk_widget_show_all((GtkWidget*) window);
    gtk_main();

    return 0;
}


