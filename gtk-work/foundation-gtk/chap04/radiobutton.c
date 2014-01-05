/**
 * radiobutton.c
 * How to use GtkRadiouButtos
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Radio Button" );
  gtk_widget_set_size_request( window, 320, 240 );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 20 );

  /*
   * you have to group them into one radio button. otherwise they will work
   * individually.
   */
  GtkWidget *chief = gtk_radio_button_new_with_label( NULL, "I am the Chief" );
  GtkWidget *staff1 = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( chief ), "I am staff 1" );
  GtkWidget *staff2 = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( chief ), "I am staff 2" );
  GtkWidget *staff3 = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( chief ), "I am staff 3" );

  GtkWidget *close = gtk_button_new_from_stock( GTK_STOCK_CLOSE );
  g_signal_connect( G_OBJECT( close ), "clicked", G_CALLBACK( gtk_main_quit ), NULL );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  GtkWidget *vbox = gtk_vbox_new( TRUE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), chief, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), staff1, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), staff2, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), staff3, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), close, FALSE, FALSE, 10 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
