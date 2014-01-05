/**
 * buttonevent.c
 * button and its event handling.
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );
static gboolean button_clicked( GtkWidget *widget, GdkEventKey *event, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Button Event" );
  gtk_widget_set_size_request( window, 320, 240 );
  gtk_window_set_resizable( GTK_WINDOW( window ), FALSE );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 20 );
  GtkWidget *button = gtk_button_new_with_label( "Click" );
  gtk_widget_set_size_request( button, 50, 15 );
  gtk_button_set_relief( GTK_BUTTON( button ), GTK_RELIEF_NORMAL );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( button_clicked ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), button );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}

static gboolean button_clicked( GtkWidget *widget, GdkEventKey *event, gpointer pointer ) {
  g_print( "Ha, you clicked button just now\n" );
  return FALSE;
} 
