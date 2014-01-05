/**
 * messagedialog.c
 * show you how to create a simple dialog
 * using the GtkMessageDialog
 */
#include <gtk/gtk.h>

static void button_clicked( GtkButton *button, GtkWindow *window );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Message Dialog" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *button  = gtk_button_new_with_mnemonic( "_Show me" );
  gtk_widget_set_size_request( button, 100, 30 );

  g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( button_clicked ), (gpointer) window );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), button );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/* after the button was clicked, we show user a dialog */
static void button_clicked( GtkButton *button, GtkWindow *window ) {
  /* create a new dialog with on OK button */
  GtkWidget *dialog = gtk_message_dialog_new( window, GTK_DIALOG_MODAL, 
      GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "the button was clicked" );
  gtk_window_set_title( GTK_WINDOW( dialog ), "Information" );

  /* create the dialog as modal and destroy it when a button is clicked */
  gtk_dialog_run( GTK_DIALOG( dialog ) );
  gtk_widget_destroy( dialog );
}
