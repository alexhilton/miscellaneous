/**
 * module-main.c
 * show you how to call another library in the code dynamically. Rather than
 * in the compile time.
 */
#include <gmodule.h>
#include <glib.h>

typedef gboolean (* PrintMessageFunc) (gpointer data);
typedef gboolean (* PrintAnotherFunc) (gpointer data);

int main( int argc, char **argv ) {
  GModule *module;
  PrintMessageFunc print_the_message;
  PrintAnotherFunc print_another_one;

  gchar *text = "With great power comes great responsibility";

  /* Make sure module loading is supported on the user's machine */
  g_assert( g_module_supported() );

  /*
   * Open the library and resolve symbols only when necessary.
   * LIbraries on windows will have a .dll appendix 
   */
  module = g_module_open( "/home/alex/work/gtk-work/foundation-gtk/chap06/module-plugin.so", G_MODULE_BIND_LAZY );

  if ( !module ) {
    g_error( "Error: %s\n", (gchar *) g_module_error() );
    return 0;
  }

  /* load the print_the_message() function */
  if ( !g_module_symbol( module, "print_the_message", (gpointer *) &print_the_message ) ) {
    g_error( "Errro: %s\n", (gchar *) g_module_error() );
    return -1;
  }

  /* load the print_another_one() function */
  if ( !g_module_symbol( module, "print_another_one", (gpointer *) &print_another_one ) ) {
    g_error( "Error: %s\n", (gchar *) g_module_error() );
    return 0;
  }

  /*
   * Run both loaded functions since there were no errors reported loading
   * neither the module nor the symbols
   */
  print_the_message( (gpointer) text );
  print_another_one( "Another message" );

  /* close the module and free allocated resources */
  if ( !g_module_close( module ) ) {
    g_error( "Error: %s\n", (gchar *) g_module_error() );
  }

  return 0;
}
