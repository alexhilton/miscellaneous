/**
 * promptquit.c
 * prompt the user when the program is quitting
 */
#include <gtk/gtk.h>
#include <stdio.h>

static gboolean close_operation( GtkWidget *window, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Prompt Quit" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 480, 360 );

  GtkWidget *label = gtk_label_new( "With great power comes great responsibilities\n" );

  g_signal_connect( G_OBJECT( window ), "delete_event", G_CALLBACK( close_operation ), NULL );

  gtk_container_add( GTK_CONTAINER( window ), label );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static gboolean close_operation( GtkWidget *window, gpointer pointer ) {
  GtkWidget *dialog = gtk_dialog_new_with_buttons( "Message", GTK_WINDOW( window ),
						   GTK_DIALOG_MODAL, 
						   GTK_STOCK_OK, GTK_RESPONSE_OK,
						   GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL );
  gtk_dialog_set_default_response( GTK_DIALOG( dialog ), GTK_RESPONSE_OK );

  GtkWidget *label = gtk_label_new( "Do you really want to leave Program?" );
  GtkWidget *image = gtk_image_new_from_stock( GTK_STOCK_DIALOG_INFO, GTK_ICON_SIZE_DIALOG );

  GtkWidget *hbox = gtk_hbox_new( FALSE, 5 );
  gtk_container_set_border_width( GTK_CONTAINER( hbox ), 10 );
  gtk_box_pack_start( GTK_BOX( hbox ), image, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( hbox ), label, FALSE, FALSE, 10 );

  /* pack the dialog content into the dialog's GtkVBox */
  gtk_box_pack_start_defaults( GTK_BOX( GTK_DIALOG(dialog)->vbox ), hbox );
  gtk_widget_show_all( dialog );

  /* run the dialog and output the data if the user clicks the OK button */
  gint result = gtk_dialog_run( GTK_DIALOG( dialog ) );
  if ( result == GTK_RESPONSE_OK ) {
    printf( "quitting the program\n" );
    gtk_widget_destroy( dialog );
    gtk_main_quit();
    return FALSE;
  } else if ( result == GTK_RESPONSE_CANCEL ) {
    printf( "keep running\n" );
    gtk_widget_destroy( dialog );
  }
  return TRUE;
}
