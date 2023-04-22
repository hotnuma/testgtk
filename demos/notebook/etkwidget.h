#ifndef ETKWIDGET_H
#define ETKWIDGET_H

#include <gtk/gtk.h>
#include <stdbool.h>

void etk_notebook_append(GtkWidget *notebook,
                         const char *title, GtkWidget *page, bool select,
                         GCallback callback, GtkWidget *widget);

#endif // ETKWIDGET_H


