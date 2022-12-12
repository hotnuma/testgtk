#include "MainWindow.h"
#include <CString.h>

#include <libsocket.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <print.h>

MainWindow::MainWindow()
{
    _createWindow();
}

MainWindow::~MainWindow()
{
    print("delete");
}

void MainWindow::_createWindow()
{
    _wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(_wnd), "App Title");
    gtk_window_set_default_size(GTK_WINDOW(_wnd), 400, 300);
    gtk_window_set_position(GTK_WINDOW(_wnd), GTK_WIN_POS_CENTER);
    setWindowObject(_wnd, this);

    _grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(_wnd), _grid);

    _createMenu();

    GtkWidget *scrolled_w = gtk_scrolled_window_new(nullptr, nullptr);
    gtk_widget_set_hexpand(scrolled_w, true);
    gtk_widget_set_vexpand(scrolled_w, true);
    gtk_grid_attach(GTK_GRID(_grid), scrolled_w, 0, _gridrow, 1, 1);
    ++_gridrow;

    GtkWidget *view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled_w), view);

    //GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    //GtkTextIter iter;
    //gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    //gtk_text_buffer_insert(buffer, &iter, "sample text\n", -1);

    _statusbar = gtk_statusbar_new();
    gtk_grid_attach(GTK_GRID(_grid), _statusbar, 0, _gridrow, 1, 1);
    ++_gridrow;

    g_signal_connect(_wnd, "destroy", G_CALLBACK(_onDestroyCB), this);
}

void MainWindow::_createMenu()
{
    // Menu bar
    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_grid_attach(GTK_GRID(_grid), menubar, 0, _gridrow, 1, 1);
    ++_gridrow;

    // File menu
    GtkWidget *menu = gtk_menu_new();
    GtkWidget *submenu = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(submenu), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), submenu);

    // Quit item
    GtkWidget *item = gtk_menu_item_new_with_label("Quit");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(_onQuitCB), this);
}

void MainWindow::_onDestroy(GtkWidget*)
{
    print("destroy");

    bool quit = true;

    GList *list = gtk_window_list_toplevels();

    for (GList* i = list; i; i = i->next)
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


