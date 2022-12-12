#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CWindow.h"

class MainWindow : public CWindow
{
public:

    MainWindow();
    virtual ~MainWindow();

private:

    void _createWindow();
    void _createMenu();
    void _createToolbar();

    void _actionNew();

    CMAP1(MainWindow*, void, _onClicked, GtkWidget*)
    CMAP1(MainWindow*, void, _onDestroy, GtkWidget*)
    CMAP1(MainWindow*, void, _actionOpen, GtkWidget*)
    CMAP1(MainWindow*, void, _actionQuit, GtkWidget*)

    GtkWidget *_notebook = nullptr;
};

#endif // MAINWINDOW_H


