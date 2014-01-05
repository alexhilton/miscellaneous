/**
 * horizontalpane.c
 * demonstrate how to use horizontal pane.
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Vertical pane" );
  gtk_widget_set_size_request( window, 100, 200 );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  GtkWidget *vpane = gtk_vpaned_new();
  GtkWidget *button1 = gtk_button_new_with_label( "Click" );
  GtkWidget *button2 = gtk_button_new_with_label( "Me" );
  g_signal_connect_swapped( G_OBJECT( button1 ), "clicked",
			    G_CALLBACK( gtk_widget_destroy ), (gpointer) window );
  g_signal_connect_swapped( G_OBJECT( button2 ), "clicked", G_CALLBACK( gtk_widget_destroy ),
			    (gpointer) window );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  gtk_paned_pack1( GTK_PANED( vpane ), button1, FALSE, FALSE );
  gtk_paned_pack2( GTK_PANED( vpane ), button2, FALSE, FALSE );

  gtk_container_add( GTK_CONTAINER( window ), vpane );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}
 
