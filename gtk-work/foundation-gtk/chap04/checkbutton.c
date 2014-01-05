/**
 * checkbutton.c
 * show you how to use GtkCheckButton.
 */
#include <gtk/gtk.h>

static void check_toggled( GtkToggleButton *button, GtkWidget *widget );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Check Button" );
  gtk_widget_set_size_request( window, 320, 240 );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );

  GtkWidget *pro = gtk_check_button_new_with_label( "Hi pro" );
  GtkWidget *con = gtk_check_button_new_with_mnemonic( "you are the pro iam the con" );
  gtk_widget_set_sensitive( con, FALSE );

  g_signal_connect( G_OBJECT( pro ), "toggled", G_CALLBACK( check_toggled ), (gpointer) con );
  g_signal_connect( G_OBJECT( con ), "toggled", G_CALLBACK( check_toggled ), (gpointer) pro );

  GtkWidget *close = gtk_button_new_from_stock( GTK_STOCK_CLOSE );
  g_signal_connect( G_OBJECT( close ), "clicked", G_CALLBACK( gtk_main_quit ), NULL );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), pro, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), con, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), close, FALSE, FALSE, 10 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all ( window );
  gtk_main();
  return 0;
}

static void check_toggled( GtkToggleButton *button, GtkWidget *widget ) {
  if ( gtk_toggle_button_get_active( button ) ) {
    gtk_widget_set_sensitive( widget, FALSE );
  } else {
    gtk_widget_set_sensitive( widget, TRUE );
  }
}
