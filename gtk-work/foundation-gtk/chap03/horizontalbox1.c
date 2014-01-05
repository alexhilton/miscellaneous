/**
 * horizontalbox.c
 * using horizontal box to arrange buttons.
 */
#include <gtk/gtk.h>

#define NUM 4

static void destroy( GtkWidget *widget, gpointer pointer );
 
int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Horizontal Box" );
  gtk_widget_set_size_request( window, 480, 60 );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );

  GtkWidget *hbox = gtk_hbox_new( TRUE, 5 );
  gchar *names[] = { "Andrew", "Joe", "Samantha", "Jonathan" };
  GtkWidget *button;
  int i;
  for ( i = 0; i < NUM; i++ ) {
    button = gtk_button_new_with_label( names[ i ] );
    gtk_box_pack_start( GTK_BOX( hbox ), button, TRUE, FALSE, 5 );
    g_signal_connect_swapped( G_OBJECT( button ), "clicked", G_CALLBACK( gtk_widget_destroy ),
			      (gpointer) window );
  }
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), hbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
} 
