#if 0

#define c_autounref _CCLEANUP(_auto_unref_func)

static inline void _auto_unref_func(void *p)
{
    void **pp = (void**) p;

    if (*pp)
        g_object_unref(*pp);
}

#endif


