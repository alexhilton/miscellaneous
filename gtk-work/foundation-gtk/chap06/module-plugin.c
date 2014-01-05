/**
 * module-plugin.c
 * show you how to use modules and plugin 
 */
#include <glib.h>
#include <stdio.h>
#include <gmodule.h>

G_MODULE_EXPORT gboolean print_the_message( gpointer data ) {
  printf( "%s\n", (gchar *) data );
  return TRUE;
}

G_MODULE_EXPORT gboolean print_another_one( gpointer data ) {
  printf( "%s\n", (gchar *) data );
  return TRUE;
}
