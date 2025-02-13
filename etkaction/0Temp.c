#if 0

_window_create_toolbar_item_from_action(window,
                                        APP_WINDOW_ACTION_FILE_OPEN,
                                        _window_actions,
                                        -1);

static GtkWidget* _window_create_toolbar_item_from_action(
                                                    AppWindow            *window,
                                                    int                  id,
                                                    const EtkActionEntry *action_entries,
                                                    guint                item_order);

static GtkWidget* _window_create_toolbar_item_from_action(
                                                    AppWindow            *window,
                                                    int                  id,
                                                    const EtkActionEntry *action_entries,
                                                    guint                item_order)
{
    GtkWidget *toolbar_item;

    toolbar_item = etk_tool_button_new_from_action(GTK_TOOLBAR(window->toolbar),
                                                   id,
                                                   action_entries,
                                                   G_OBJECT(window));

    const EtkActionEntry *action_entry = etk_actions_get_entry(action_entries, id);

    g_object_set_data_full(G_OBJECT(toolbar_item),
                           "label",
                           g_strdup(action_entry->label_text),
                           g_free);
    g_object_set_data_full(G_OBJECT(toolbar_item),
                           "icon",
                           g_strdup(action_entry->icon_name),
                           g_free);

    g_signal_connect_after(G_OBJECT(toolbar_item), "button-press-event",
                           G_CALLBACK(_window_toolbar_button_clicked), G_OBJECT(window));

    thunar_g_object_set_guint_data(G_OBJECT(toolbar_item), "default-order", item_order);

    return toolbar_item;
}

static GtkWidget*
thunar_window_create_toolbar_toggle_item_from_action (ThunarWindow       *window,
                                                      ThunarWindowAction action,
                                                      gboolean           active,
                                                      guint              item_order)
{
  GtkWidget *toolbar_item;

  toolbar_item = xfce_gtk_toggle_tool_button_new_from_action_entry (get_action_entry (action), G_OBJECT (window), active, GTK_TOOLBAR (window->location_toolbar));
  g_object_set_data_full (G_OBJECT (toolbar_item), "label", g_strdup (get_action_entry (action)->menu_item_label_text), g_free);
  g_object_set_data_full (G_OBJECT (toolbar_item), "icon", g_strdup (get_action_entry (action)->menu_item_icon_name), g_free);
  g_signal_connect_after (G_OBJECT (toolbar_item), "button-press-event", G_CALLBACK (thunar_window_toolbar_button_clicked), G_OBJECT (window));

  thunar_g_object_set_guint_data (G_OBJECT (toolbar_item), "default-order", item_order);

  return toolbar_item;
}

#endif


