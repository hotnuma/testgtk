#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <cairo.h>

gchar _buf[256];

gboolean on_draw(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    (void) event;
    (void) data;

    // "convert" the G*t*kWidget to G*d*kWindow (no, it's not a GtkWindow!)
    GdkWindow *window = gtk_widget_get_window(widget);

    cairo_region_t *cairoRegion = cairo_region_create();

    GdkDrawingContext *drawingContext;
    drawingContext = gdk_window_begin_draw_frame(window, cairoRegion);

    {
        // say: "I want to start drawing"
        cairo_t *cr = gdk_drawing_context_get_cairo_context(drawingContext);

        // do your drawing
        cairo_move_to(cr, 30, 30);
        cairo_set_font_size(cr, 15);
        cairo_show_text(cr, _buf);

        // say: "I'm finished drawing
        gdk_window_end_draw_frame(window,drawingContext);
    }

    // cleanup
    cairo_region_destroy(cairoRegion);

    return FALSE;
}

gboolean time_handler(GtkWidget *widget)
{
    if (gtk_widget_get_window(widget) == NULL)
        return FALSE;

    GDateTime *now = g_date_time_new_now_local();
    gchar *my_time = g_date_time_format(now, "%H:%M:%S");

    g_sprintf(_buf, "%s", my_time);

    g_free(my_time);
    g_date_time_unref(now);

    gtk_widget_queue_draw(widget);

    return TRUE;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_title(GTK_WINDOW(window), "Timer");

    GtkWidget *darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);

    g_signal_connect(darea, "draw",
                     G_CALLBACK(on_draw), NULL);

    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_timeout_add(1000, (GSourceFunc) time_handler, (gpointer) window);

    gtk_widget_show_all(window);
    time_handler(window);

    gtk_main();

    return 0;
}


