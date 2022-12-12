#include "MainWindow.h"
#include <CString.h>

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
    g_signal_connect(_wnd, "destroy", CB(_onDestroy), this);

    _grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(_wnd), _grid);

    _createMenu();
    _createToolbar();

    _notebook = gtk_notebook_new();
    gtk_widget_set_hexpand(_notebook, true);
    gtk_widget_set_vexpand(_notebook, true);
    gtk_grid_attach(GTK_GRID(_grid), _notebook, 0, _gridrow, 1, 1);
    ++_gridrow;

    _actionNew();



    _statusbar = gtk_statusbar_new();
    gtk_grid_attach(GTK_GRID(_grid), _statusbar, 0, _gridrow, 1, 1);
    ++_gridrow;



}

void MainWindow::_createMenu()
{
    // Menu bar
    GtkWidget *menubar = gtk_menu_bar_new();

    GtkWidget *menu = menuCreateSub(menubar, "File");

    menuAppendItem(menu, "Open...", CB(_actionOpen), this);
    menuAppendItem(menu, "Quit", CB(_actionQuit), this);

    gtk_grid_attach(GTK_GRID(_grid), menubar, 0, _gridrow, 1, 1);
    ++_gridrow;
}

void MainWindow::_createToolbar()
{
    _toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(_toolbar), GTK_TOOLBAR_ICONS);

    toolbarAppendItem(_toolbar, "gtk-new", CB(_actionOpen), this);
    toolbarAppendItem(_toolbar, "gtk-open", CB(_actionOpen), this);
    toolbarAppendItem(_toolbar, "gtk-save", CB(_actionOpen), this);
    toolbarAppendSeparator(_toolbar);
    toolbarAppendItem(_toolbar, "gtk-quit", CB(_actionOpen), this);

    gtk_grid_attach(GTK_GRID(_grid), _toolbar, 0, _gridrow, 1, 1);
    ++_gridrow;
}

void MainWindow::_onDestroy(GtkWidget*)
{
    //print("destroy");

    bool last = isLastWindow(this);

    setWindowObject(_wnd, nullptr);
    delete this;

    if (last)
        gtk_main_quit();
}


