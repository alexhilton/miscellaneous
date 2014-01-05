/**
 * verticalbox.c
 */
#include <gtk/gtk.h>

#define NUMBER 4

static void destroy( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Vertical Boxes" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );

  /* add four buttons to vbox */
  const gchar *names[] = { "Andrew", "Joe", "Samantha", "Jonathan" };

  int i;
  for ( i = 0; i < NUMBER; i++ ) {
    GtkWidget *button = gtk_button_new_with_label( names[ i ] );
    gtk_box_pack_start( GTK_BOX( vbox ), button, TRUE, TRUE, 5 );
    g_signal_connect_swapped( G_OBJECT( button ), "clicked", 
			      G_CALLBACK( gtk_widget_destroy ), (gpointer) window );
  }
  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}
