#include <gtk/gtk.h>

// gcc -g -O0 -o gtk_simple gtk_simple.c `pkg-config --libs --cflags gtk+-3.0`
// valgrind --leak-check=full --suppressions=./{glib,gtk,gtk_simple}.supp ./gtk_simple

/*
valgrind --leak-check=full --error-limit=no --num-callers=20 \
--suppressions=/usr/share/glib-2.0/valgrind/glib.supp \
--suppressions=/usr/share/gtk-3.0/valgrind/gtk.supp \
--suppressions=./gtk_simple.supp \
./gtk_simple
*/

//~ int main(int argc, char **argv)
//~ {
    //~ gtk_init(&argc, &argv);

    //~ GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //~ gtk_widget_show(window);

    //~ g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  

    //~ gtk_main();

    //~ return 0;
//~ }

#include <stdlib.h>

  void f(void)
  {
     int* x = malloc(10 * sizeof(int));
     x[10] = 0;        // problem 1: heap block overrun
  }                    // problem 2: memory leak -- x not freed

  int main(void)
  {
     f();
     return 0;
  }
