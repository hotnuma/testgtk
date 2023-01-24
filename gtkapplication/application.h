#ifndef APPLICATION_H
#define APPLICATION_H

#include <etype.h>
#include <gtk/gtk.h>

#define TYPE_APPLICATION (application_get_type())
E_DECLARE_FINAL_TYPE(Application, application, APPLICATION, GtkApplication)

Application* application_get();

#endif // APPLICATION_H


