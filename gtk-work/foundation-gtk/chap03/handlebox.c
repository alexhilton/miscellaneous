/**
 * handlebox.c
 * demo to use handlebox.c
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Handle Box" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *handlebox = gtk_handle_box_new();
  GtkWidget *label = gtk_label_new( "Detach me" );
  gtk_handle_box_set_shadow_type( GTK_HANDLE_BOX( handlebox ), GTK_SHADOW_IN );
  gtk_handle_box_set_handle_position( GTK_HANDLE_BOX( handlebox ), GTK_POS_LEFT );
  gtk_handle_box_set_snap_edge( GTK_HANDLE_BOX( handlebox ), GTK_POS_TOP );

  gtk_container_add( GTK_CONTAINER( handlebox ), label );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), handlebox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}
