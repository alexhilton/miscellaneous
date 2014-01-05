/**
 * filechooserdialog.c
 * show you have to use filechooserdialog
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  /*
   * allow the user to enter a new file name and location for the file and
   * set the button to the text of the location
   */

  GtkWidget *dialog = gtk_file_chooser_dialog_new( "Save File as ...", NULL,
						   GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER,
						   GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, 
						   GTK_STOCK_OK, GTK_RESPONSE_OK, NULL );

  gint result = gtk_dialog_run( GTK_DIALOG( dialog ) );
  if ( result == GTK_RESPONSE_OK ) {
    gchar *filename = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( dialog ) );
    g_print( "Creating dicretory: %s\n", filename );
  }
  gtk_widget_destroy( dialog );
  return 0;
}  
