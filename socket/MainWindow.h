#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CWindow.h"

class MainWindow : public CWindow
{
public:

    MainWindow();
    virtual ~MainWindow();

    CMAP2(MainWindow*, int, onSocketInput, GIOChannel*, GIOCondition)

private:

    CMAP1(MainWindow*, void, _onQuit, GtkWidget*)
    CMAP1(MainWindow*, void, _onDestroy, GtkWidget*)

    void _createWindow();
    void _createMenu();

};

#endif // MAINWINDOW_H


