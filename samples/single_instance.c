#include <glib.h>
#include <glib-object.h>
#include <sys/file.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#define APPNAME "testgtk"
#define APPLOCK "/tmp/" APPNAME ".pid"

bool app_isfirst(const char *lockfile)
{
    int pid_file = open(lockfile, O_CREAT | O_RDWR, 0666);

    int rc = flock(pid_file, LOCK_EX | LOCK_NB);

    // another instance is running
    if (rc && EWOULDBLOCK == errno)
        return false;

    return true;
}

int main()
{
    if (!app_isfirst(APPLOCK))
    {
        g_print("not first instance\n");
        return 1;
    }

    g_print("is first instance\n");

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    g_object_unref(loop);

    return 0;
}


