/**
 * firstdialog.c
 * show you how to create a simple dialog
 */
#include <gtk/gtk.h>

static void button_clicked( GtkButton *button, GtkWindow *window );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "First Dialog" );
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
  GtkWidget *dialog = gtk_dialog_new_with_buttons( "Information which you need to know", window,
						   GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK,
						   NULL );
  //gtk_dialog_set_has_separator( GTK_DIALOG( dialog ), FALSE );
  gtk_dialog_set_has_separator( GTK_DIALOG( dialog ), TRUE );
  GtkWidget *label = gtk_label_new( "The button has been clicked!" );
  GtkWidget *image = gtk_image_new_from_stock( GTK_STOCK_DIALOG_INFO, GTK_ICON_SIZE_DIALOG );

  GtkWidget *hbox = gtk_hbox_new( FALSE, 5 );
  gtk_container_set_border_width( GTK_CONTAINER( hbox ), 10 );
  gtk_box_pack_start( GTK_BOX( hbox ), image, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( hbox ), label, FALSE, FALSE, 10 );

  /* pack the dialog content into the dialog's GtkVBox */
  gtk_box_pack_start_defaults( GTK_BOX( GTK_DIALOG(dialog)->vbox ), hbox );
  gtk_widget_show_all( dialog );

  /* create the dialog as modal and destroy it when a button is clicked */
  gtk_dialog_run( GTK_DIALOG( dialog ) );
  gtk_widget_destroy( dialog );
}
