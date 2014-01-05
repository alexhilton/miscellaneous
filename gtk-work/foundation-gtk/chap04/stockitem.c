/**
 * stockitem.c
 * Show you how to use stock item.
 * This example will create a button from stock items.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Stock Item" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *close = gtk_button_new_from_stock( GTK_STOCK_CLOSE );
  g_signal_connect_swapped( G_OBJECT( close ), "clicked", G_CALLBACK( gtk_widget_destroy ),
			    (gpointer) window );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  gtk_container_add( GTK_CONTAINER( window ), close );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
