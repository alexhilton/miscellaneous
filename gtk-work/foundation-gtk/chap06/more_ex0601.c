/**
 * more_ex0601.c
 * more than solution to ex0601.c
 * This program writes the text input from a entry by user into a file selected 
 * by a filechooser. This is controled by a button.Before the program quits, we 
 * print all the ocntents of the file to the screen just for checking.
 * When dealing with file chooser, you should use signal file_set.
 */
#include <gtk/gtk.h>

typedef struct {
  const gchar *text;
  const gchar *filename;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget *folder_chooser;
  GtkWidget *file_chooser;
} Data;

static void text_entered( GtkEntry *entry, Data *data );
static void button_clicked( GtkButton *button, Data *data );
static void folder_selected( GtkFileChooser *folder, Data *data );
static void file_selected( GtkFileChooser *chooser, Data *data );
static void destroy( GtkWidget *widget, Data *data );
/* static void handle_error( GError *error ); */
static void again_clicked( GtkButton *button, Data *data );

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

  GtkWidget *again = gtk_button_new_with_mnemonic( "_Again" );
  GtkWidget *file_chooser = gtk_file_chooser_button_new( "Chooser a file", 
						    GTK_FILE_CHOOSER_ACTION_OPEN );
  GtkWidget *folder_chooser = gtk_file_chooser_button_new( "Chooser a folder",
						    GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER );
  gtk_widget_set_sensitive( file_chooser, FALSE );

  Data data;
  data.text = '\0';
  data.filename = '\0';
  data.entry = entry;
  data.button = button;
  data.file_chooser = file_chooser;
  data.folder_chooser = folder_chooser;

  /* add file filter for file_chooser */
  GtkFileFilter *filter = gtk_file_filter_new();
  gtk_file_filter_set_name( filter, "Text Files" );
  gtk_file_filter_add_pattern( filter, "*.txt" );
  gtk_file_filter_add_pattern( filter, "*.c" );
  gtk_file_filter_add_pattern( filter, "*.c~" );
  gtk_file_filter_add_pattern( filter, "*.cc" );
  gtk_file_filter_add_pattern( filter, "*.java" );
  gtk_file_chooser_add_filter( GTK_FILE_CHOOSER( file_chooser ), filter );

  /* 
   * attention:
   *    gtk_file_chooser_set_current_folder will invoke event "selection_changed"
   * Note:
   *  When using file chooser, either button or dialog, you should use signal
   *  file_set rather than selection_changed. Only file_set is emitted when user
   *  do a change: select a file.
   */
  /* gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER( chooser ), g_get_home_dir() ); */
  g_signal_connect( G_OBJECT( folder_chooser ), "file_set", G_CALLBACK( folder_selected ),
		    (gpointer) &data );
  g_signal_connect( G_OBJECT( file_chooser ), "file_set", G_CALLBACK( file_selected ), 
		    (gpointer) &data );
  g_signal_connect( G_OBJECT( entry ), "changed", G_CALLBACK( text_entered ), (gpointer) &data );
  g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( button_clicked ), (gpointer) &data );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), (gpointer) &data );
  g_signal_connect( G_OBJECT( again ), "clicked", G_CALLBACK( again_clicked ), (gpointer) &data );

  /* arragne all widgets together in a container */
  GtkWidget *vbox = gtk_vbox_new( FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), folder_chooser, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), file_chooser, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), entry, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), button, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), again, FALSE, FALSE, 10 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void folder_selected( GtkFileChooser *folder_chooser, Data *data ) {
  gtk_widget_set_sensitive( GTK_WIDGET( data->file_chooser ), TRUE );
  gchar *folder = gtk_file_chooser_get_filename( folder_chooser );
  gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER( data->file_chooser ), folder );
  gtk_widget_set_sensitive( GTK_WIDGET( folder_chooser ), FALSE );
}

static void file_selected( GtkFileChooser *chooser, Data *data ) {
  gtk_widget_set_sensitive( data->entry, TRUE );
  data->filename = gtk_file_chooser_get_filename( chooser );
}

static void text_entered( GtkEntry *entry, Data *data ) {
  data->text = gtk_entry_get_text( entry );
  gtk_widget_set_sensitive( data->button, TRUE );
}

static void button_clicked( GtkButton *button, Data *data ) {
  FILE *fp;
  if ( (fp = fopen( data->filename, "a" )) == NULL ) {
    fclose( fp );
    return;
  }
  fputs( data->text, fp );
  fputs( "\n", fp );
  fclose( fp );
  gtk_entry_set_text( GTK_ENTRY( data->entry ), "" );
  gtk_widget_set_sensitive( data->button, FALSE );
}

static void destroy( GtkWidget *widget, Data *data ) {
  FILE *fp;
  char buffer[ 256 ];
  if ( (fp = fopen( data->filename, "r" )) == NULL ) {
    gtk_main_quit();
    return;
  }
  while ( fgets( buffer, sizeof( buffer ), fp ) != NULL ) {
    fputs( buffer, stdout );
  }
  fclose( fp );
  gtk_main_quit();
}

/*
static void handle_error( GError *error ) {
  if ( error != NULL ) {
    g_print( error->message );
    g_clear_error( &error );
  }
}
*/

static void again_clicked( GtkButton *button, Data *data ) {
  gtk_widget_set_sensitive( data->folder_chooser, TRUE );
  gtk_widget_set_sensitive( data->file_chooser, FALSE );
  gtk_widget_set_sensitive( data->button, FALSE );
  gtk_widget_set_sensitive( data->entry, FALSE );
}
