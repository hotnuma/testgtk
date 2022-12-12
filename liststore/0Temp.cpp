#if 0

g_signal_connect(_wnd, "delete-event", G_CALLBACK(_onDeleteEventCB), this);

bool MainWindow::_onDeleteEvent(GtkWidget*, GdkEvent*)
{
    print("delete-event");

    return false;
}

void MainWindow::_onButtonClicked(GtkWidget *widget)
{
    gtk_button_set_label(GTK_BUTTON(widget), "Hello World");

    CString str = "Status : Ok";

    gtk_statusbar_push(
        GTK_STATUSBAR(_statusbar),
        gtk_statusbar_get_context_id(GTK_STATUSBAR(_statusbar), str),
        str);
}

#endif


