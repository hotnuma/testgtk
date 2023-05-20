
// Header ---------------------------------------------------------------------

#include <glib-object.h>

typedef struct _MyObjectClass MyObjectClass;
typedef struct _MyObject      MyObject;

#define TYPE_MYOBJECT (myobject_get_type())
#define MYOBJECT(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj),  TYPE_MYOBJECT, MyObject))
#define MYOBJECT_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass),   TYPE_MYOBJECT, MyObjectClass))
#define IS_MYOBJECT(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj),  TYPE_MYOBJECT))
#define IS_MYOBJECT_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass),   TYPE_MYOBJECT))
#define MYOBJECT_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj),   TYPE_MYOBJECT, MyObjectClass))

GType myobject_get_type() G_GNUC_CONST;

// MyObject ---------------------------------------------------------------

static void myobject_constructed(GObject *object);
static void myobject_dispose(GObject *object);
static void myobject_finalize(GObject *object);
static void myobject_get_property(GObject *object, guint prop_id,
                                   GValue *value, GParamSpec *pspec);
static void myobject_set_property(GObject *object, guint prop_uid,
                                   const GValue *value, GParamSpec *pspec);

// MyObject ---------------------------------------------------------------

#include <stdio.h>

struct _MyObjectClass
{
    GObjectClass __parent__;
};

struct _MyObject
{
    GObject __parent__;
};

G_DEFINE_TYPE(MyObject, myobject, G_TYPE_OBJECT)

static void myobject_class_init(MyObjectClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->constructed = myobject_constructed;
    gobject_class->dispose = myobject_dispose;
    gobject_class->finalize = myobject_finalize;
    gobject_class->get_property = myobject_get_property;
    gobject_class->set_property = myobject_set_property;

    printf("myobject_class_init\n");
}

static void myobject_init(MyObject *myobject)
{
    (void) myobject;

    printf("myobject_init\n");
}

// GObjectClass ---------------------------------------------------------------

static void myobject_constructed(GObject *object)
{
    //MyObject *myobject = MYOBJECT(object);

    printf("myobject_constructed\n");

    G_OBJECT_CLASS(myobject_parent_class)->constructed(object);
}

static void myobject_dispose(GObject *object)
{
    //MyObject *myobject = MYOBJECT(object);

    printf("myobject_dispose\n");

    G_OBJECT_CLASS(myobject_parent_class)->dispose(object);
}

static void myobject_finalize(GObject *object)
{
    //MyObject *myobject = MYOBJECT(object);

    printf("myobject_finalize\n");

    G_OBJECT_CLASS(myobject_parent_class)->finalize(object);
}

static void myobject_get_property(GObject *object, guint prop_id,
                                  GValue *value, GParamSpec *pspec)
{
    (void) value;

    //MyObject *myobject = MYOBJECT(object);

    switch (prop_id)
    {

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }

    printf("myobject_get_property\n");
}

static void myobject_set_property(GObject *object, guint prop_id,
                                   const GValue *value, GParamSpec *pspec)
{
    (void) value;

    //MyObject *myobject = MYOBJECT(object);

    switch (prop_id)
    {

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }

    printf("myobject_get_property\n");
}

int main()
{
    setbuf(stdout, NULL);

    MyObject *obj1 = g_object_new(TYPE_MYOBJECT, NULL);
    MyObject *obj2 = g_object_new(TYPE_MYOBJECT, NULL);

    g_object_unref(obj1);
    g_object_unref(obj2);

    return EXIT_SUCCESS;
}


