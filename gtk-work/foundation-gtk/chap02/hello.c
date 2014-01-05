/**
 * hello.c
 * More complex demo program using some typical features of
 * GTK+
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );
static gboolean delete_event( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "More complex Hello" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );
  GtkWidget *label = gtk_label_new( "Hello, world of Gtk+" );
  //gtk_label_set_selectable( GTK_LABEL( label ), TRUE );
  gtk_label_set_selectable( GTK_LABEL( label ), FALSE );
  gtk_container_add( GTK_CONTAINER( window ), label );

  /* connect signals and callback function */
  g_signal_connect( G_OBJECT( window ), "destroy",
		    G_CALLBACK( destroy ), NULL );
  g_signal_connect( G_OBJECT( window ), "delete_event",
		    G_CALLBACK( delete_event ), NULL );

  gtk_widget_show_all( window );

  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}

static gboolean delete_event( GtkWidget *widget, gpointer pointer ) {
  return FALSE;
}
