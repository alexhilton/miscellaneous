/**
 * expander.c
 * how to use GtkExpander, another container
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Expander" );
  gtk_widget_set_size_request( window, 320, 240 );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );

  GtkWidget *expander = gtk_expander_new_with_mnemonic( "_Expaner" );
  GtkWidget *label = gtk_label_new( "HIde me or show me\n, is your choice" );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );

  gtk_container_add( GTK_CONTAINER( expander ), label );
  gtk_expander_set_expanded( GTK_EXPANDER( expander ), TRUE );
  gtk_container_add( GTK_CONTAINER( window ), expander );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}
