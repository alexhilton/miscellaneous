/**
 * ex0601.c
 * solution to ex0601.c
 * This program writes the text input from a entry by user into a file selected 
 * by a filechooser. This is controled by a button.Before the program quits, we 
 * print all the ocntents of the file to the screen just for checking.
 */
#include <gtk/gtk.h>

typedef struct {
  const gchar *text;
  const gchar *filename;
  GtkWidget *entry;
  GtkWidget *button;
} Data;

static void text_entered( GtkEntry *entry, Data *data );
static void button_clicked( GtkButton *button, Data *data );
static void file_selected( GtkFileChooser *chooser, Data *data );
static void destroy( GtkWidget *widget, Data *data );
static void handle_error( GError *error );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Ex0601" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 20 );
  gtk_widget_set_size_request( window, 480, 320 );

  GtkWidget *entry = gtk_entry_new();
  gtk_entry_set_visibility( GTK_ENTRY( entry ), TRUE );
  GtkWidget *button = gtk_button_new_with_mnemonic( "_Write to File" );
  gtk_widget_set_sensitive( button, FALSE );
  gtk_widget_set_sensitive( entry, FALSE );

  Data data;
  data.text = '\0';
  data.filename = '\0';
  data.entry = entry;
  data.button = button;

  GtkWidget *chooser = gtk_file_chooser_button_new( "Chooser a folder", 
						    GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER );
  /* gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER( chooser ), g_get_home_dir() ); */

  g_signal_connect( G_OBJECT( chooser ), "selection_changed", G_CALLBACK( file_selected ), 
		    (gpointer) &data );
  g_signal_connect( G_OBJECT( entry ), "changed", G_CALLBACK( text_entered ), (gpointer) &data );
  g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( button_clicked ), (gpointer) &data );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), (gpointer) &data );
  /* arragne all widgets together in a container */
  GtkWidget *vbox = gtk_vbox_new( FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), chooser, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), entry, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), button, FALSE, FALSE, 10 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void file_selected( GtkFileChooser *chooser, Data *data ) {
  gtk_widget_set_sensitive( data->entry, TRUE );
  gtk_widget_set_sensitive( data->button, TRUE );
  data->filename = gtk_file_chooser_get_filename( chooser );
  gtk_widget_set_sensitive( GTK_WIDGET( chooser ), FALSE );
}

static void text_entered( GtkEntry *entry, Data *data ) {
  data->text = gtk_entry_get_text( entry );
}

static void button_clicked( GtkButton *button, Data *data ) {
  GError *error = NULL;
  gchar *filename = g_build_filename( data->filename, "tmp.tmp", NULL );
  g_file_set_contents( filename, data->text, -1, &error );
  handle_error( error );

  if ( !g_file_test( filename, G_FILE_TEST_EXISTS ) ) {
    g_error( "failed write to file" );
  }
  g_free( filename );
  gtk_entry_set_text( GTK_ENTRY( data->entry ), "" );
}

static void destroy( GtkWidget *widget, Data *data ) {
  gchar *contents;
  gsize bytes;
  GError *error = NULL;
  gchar *filename = g_build_filename( data->filename, "tmp.tmp", NULL );
  if ( !g_file_test( filename, G_FILE_TEST_EXISTS ) ) {
    g_free( filename );
    gtk_main_quit();
    return;
  }
  g_file_get_contents( filename, &contents, &bytes, &error );
  handle_error( error );
  g_print( "%s\n", contents );
  g_free( filename );
  g_free( contents );
  gtk_main_quit();
}

static void handle_error( GError *error ) {
  if ( error != NULL ) {
    g_print( error->message );
    g_clear_error( &error );
  }
}
