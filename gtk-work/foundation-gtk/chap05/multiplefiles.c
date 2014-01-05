/**
 * filechooserdialog.c
 * show you have to use filechooserdialog
 */
#include <gtk/gtk.h>

static void button_clicked( GtkButton *button, GtkWindow *window );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "File Chooser Dialog" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *button = gtk_button_new_with_mnemonic( "_Open Files" );

  g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( button_clicked ), (gpointer) window );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  gtk_container_add( GTK_CONTAINER( window ), button );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/*
 * allow the user to enter a new file name and location for the file and
 * set the button to the text of the location
 */
static void button_clicked( GtkButton *button, GtkWindow *window ) {
  GtkWidget *dialog = gtk_file_chooser_dialog_new( "Open Files", window,
						   GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL,
						   GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE,
						   GTK_RESPONSE_ACCEPT, NULL );
  /* set select multiple files flag as true */
  gtk_file_chooser_set_select_multiple( GTK_FILE_CHOOSER( dialog ), TRUE );
  gint result = gtk_dialog_run( GTK_DIALOG( dialog ) );
  if ( result == GTK_RESPONSE_ACCEPT ) {
    GSList *filename = gtk_file_chooser_get_filenames( GTK_FILE_CHOOSER( dialog ) );
    while ( filename != NULL ) {
      gchar *file = (gchar *) filename->data;
      g_print( "%s was selected\n", file );
      filename = filename->next;
    }
    
  }
  gtk_widget_destroy( dialog );
}
