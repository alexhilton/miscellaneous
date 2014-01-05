/**
 * file.c
 * show you how to use File uility api
 */
#include <glib.h>

static void handle_error( GError *error );

int main( int argc, char **argv ) {
  /* build a file in user's home directory */
  gchar *filename = g_build_filename( g_get_home_dir(), "temp", NULL );
  gchar *content;
  gsize bytes;
  GError *error = NULL;

  /* set the contents of the given file and report any errors */
  g_file_set_contents( filename, "Hello, world", -1, &error );
  handle_error( error );

  if ( !g_file_test( filename, G_FILE_TEST_EXISTS ) ) {
    g_error( "error: file does not exist" );
  }

  /* get the contents of the given file and report any error */
  g_file_get_contents( filename, &content, &bytes, &error );
  handle_error( error );
  g_print( "%s\n", content );

  g_free( content );
  g_free( filename );
  return 0;
}

static void handle_error( GError *error ) {
  if ( error != NULL ) {
    g_print( "%s\n", error->message );
    g_clear_error( &error );
  }
}
