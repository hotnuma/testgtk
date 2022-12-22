#ifndef APPLICATION_H
#define APPLICATION_H

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _ApplicationClass ApplicationClass;
typedef struct _Application      Application;

#define TYPE_APPLICATION (application_get_type())
#define APPLICATION(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_APPLICATION, Application))
#define APPLICATION_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), TYPE_APPLICATION, ApplicationClass))
#define IS_APPLICATION(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_APPLICATION))
#define IS_APPLICATION_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_APPLICATION))
#define APPLICATION_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), TYPE_APPLICATION, ApplicationClass))

GType application_get_type() G_GNUC_CONST;

Application* application_get();

G_END_DECLS

#endif // APPLICATION_H


