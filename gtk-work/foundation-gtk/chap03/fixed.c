/**
 * fixed.c
 * how to use fixed container: GtkFixed, though it has many drawbacks
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_widget_set_size_request( window , 320, 240 );
  gtk_window_set_title( GTK_WINDOW( window ), "Gtk Fixed container" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );

  GtkWidget *fixed = gtk_fixed_new();
  GtkWidget *button1 = gtk_button_new_with_label( "Pixel by pixel..." );
  GtkWidget *button2 = gtk_button_new_with_label( "click me ..." );
  g_signal_connect_swapped( G_OBJECT( button1 ), "clicked", G_CALLBACK( gtk_widget_destroy ),
			    (gpointer) window );
  g_signal_connect_swapped( G_OBJECT( button2 ), "clicked", G_CALLBACK( gtk_widget_destroy ),
			    (gpointer) window );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );

  gtk_fixed_put( GTK_FIXED( fixed ), button1, 0, 0 );
  gtk_fixed_put( GTK_FIXED( fixed ), button2, 50, 50 );

  gtk_container_add( GTK_CONTAINER( window ), fixed );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}
