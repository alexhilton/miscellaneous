/**
 * mmprofile.c
 * show you how to use memory profiling.
 */
#include <glib.h>

int main( int argc, char **argv ) {
  GSList *list = NULL; /* single list */

  /* 
   * To use memory profile, you have to set the GMemVTable.
   * Set the GMemVTable to the default table. This needs to be called before
   * any other call to a GLib function
   */
  g_mem_set_vtable( glib_mem_profiler_table );

  /* call g_mem_profile() when the apllication exits */
  g_atexit( g_mem_profile );

  /* do some memory related operations */
  list = (GSList *) g_malloc( sizeof( *list ) );
  list->next = (GSList *) g_malloc( sizeof( GSList ) );

  /* Only free one of the GSList objects  to see the memory profiler output. */
  g_free( list->next );

  return 0;
}
