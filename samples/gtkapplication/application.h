#ifndef APPLICATION_H
#define APPLICATION_H

#include "config.h"
#include <gtk/gtk.h>
#include <etype.h>

#define TYPE_APPLICATION (application_get_type())
E_DECLARE_FINAL_TYPE(Application, application, APPLICATION, GtkApplication)

Application* application_get();

#endif // APPLICATION_H


