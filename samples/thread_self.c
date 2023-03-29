#include <glib.h>
#include <stdio.h>
#include <unistd.h>

gboolean timeout_callback(gpointer data)
{
    static int i;

    g_print("timeout_callback called %d times\n", ++i);
    printf("thread : %p\n", g_thread_self());

    sleep(1);

    if (10 == i)
    {
        g_main_loop_quit((GMainLoop*) data);
        return FALSE;
    }

    return TRUE;
}

int main()
{
    printf("thread : %p\n", g_thread_self());

    GMainLoop *loop = g_main_loop_new(NULL ,FALSE);

    // add source to default context
    g_idle_add(timeout_callback , loop);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);

    return 0;
}


