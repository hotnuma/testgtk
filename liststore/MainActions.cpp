#include "MainWindow.h"

#include <print.h>

void MainWindow::_onChanged(GtkWidget *selection)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(selection), &model, &iter))
    {
        char *value;
        gtk_tree_model_get(model, &iter, LIST_ITEM, &value, -1);

        print(value);

        //gtk_label_set_text(GTK_LABEL(label), value);

        g_free(value);
    }
}


