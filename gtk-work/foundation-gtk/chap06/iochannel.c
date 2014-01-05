/**
 * iochannel.c
 * show you how to use File uility api
 */
#include <glib.h>

static void handle_error( GError *error );

int main( int argc, char **argv ) {
  /* build a file in user's home directory */
  gchar *filename = g_build_filename( g_get_home_dir(), "temp", NULL );
  GIOChannel *write, *read;
  gchar *content;
  gsize bytes;
  GError *error = NULL;

  /* set the contents of the given file and report any errors */
  write = g_io_channel_new_file( filename, "w", &error );
  handle_error( error );
  g_io_channel_write_chars( write, "Hello, world!", -1, &bytes, NULL );
  g_io_channel_close( write );

  if ( !g_file_test( filename, G_FILE_TEST_EXISTS ) ) {
    g_error( "error: file does not exist" );
  }

  /* get the contents of the given file and report any error */
  read = g_io_channel_new_file( filename, "r", &error );
  handle_error( error );
  g_io_channel_read_to_end( read, &content, &bytes, NULL );
  g_print( "%s\n", content );
  g_io_channel_close( read );

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
