#include "MainWindow.h"
#include <CString.h>

void _listAppend(GtkWidget *list, const gchar *str)
{
    GtkListStore *store =
        GTK_LIST_STORE(gtk_tree_view_get_model(
                            GTK_TREE_VIEW(list)));

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}

MainWindow::MainWindow()
{
    _createWindow();
}

MainWindow::~MainWindow()
{
}

void MainWindow::_createWindow()
{
    _wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(_wnd), "App Title");
    gtk_window_set_default_size(GTK_WINDOW(_wnd), 400, 300);
    gtk_window_set_position(GTK_WINDOW(_wnd), GTK_WIN_POS_CENTER);
    setWindowObject(_wnd, this);

    GtkWidget *listView = _createListView();
    gtk_container_add(GTK_CONTAINER(_wnd), listView);

    g_signal_connect(_wnd, "destroy", G_CALLBACK(_onDestroyCB), this);
}

GtkWidget* MainWindow::_createListView()
{
    GtkWidget *listView = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(listView), false);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column =
        gtk_tree_view_column_new_with_attributes(
            "List Items",
            renderer,
            "text",
            LIST_ITEM,
            nullptr);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listView), column);

    GtkListStore *store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

    gtk_tree_view_set_model(
        GTK_TREE_VIEW(listView),
        GTK_TREE_MODEL(store));

    g_object_unref(store);

    _listAppend(listView, "Aliens");
    _listAppend(listView, "Leon");
    _listAppend(listView, "The Verdict");
    _listAppend(listView, "North Face");
    _listAppend(listView, "Der Untergang");

    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(listView));

    g_signal_connect(selection, "changed",
        G_CALLBACK(_onChangedCB), this);

    return listView;
}

void MainWindow::_onDestroy(GtkWidget*)
{
    bool quit = true;

    GList *list = gtk_window_list_toplevels();

    for (GList *i = list; i; i = i->next)
    {
        CWindow *window = (CWindow*) getWindowObject(GTK_WIDGET(i->data));

        if (window && window != this)
        {
            quit = false;
            break;
        }
    }

    setWindowObject(_wnd, nullptr);
    delete this;

    if (quit)
        gtk_main_quit();
}


