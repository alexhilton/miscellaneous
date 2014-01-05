/*
 * an0201.c
 * answer to ex0201.c
 */
#include <gtk/gtk.h>

static gchar *firstname = "Alex";
static gchar *lastname = "Hilton";

static void destroy( GtkWidget *widget, gpointer pointer );
static gboolean key_pressed( GtkWidget *widget, GdkEventKey *event, GtkLabel *label );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), firstname );
  gtk_widget_set_size_request( window, 320, 240 );
  gtk_window_set_resizable( GTK_WINDOW( window ), FALSE );
  GtkWidget *label = gtk_label_new( lastname );
  gtk_label_set_selectable( GTK_LABEL( label ), TRUE );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  g_signal_connect( G_OBJECT( window ), "key_press_event", 
		    G_CALLBACK( key_pressed ), (gpointer) label );
  gtk_container_add( GTK_CONTAINER( window ), label );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
} 

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}

static gboolean key_pressed( GtkWidget *widget, GdkEventKey *event, GtkLabel *label ) {
  gchar *text = gtk_label_get_text( label );
  if ( g_ascii_strcasecmp( firstname, text ) == 0 ) {
    gtk_window_set_title( GTK_WINDOW( widget ), firstname );
    gtk_label_set_text( label, lastname );
  } else {
    gtk_window_set_title( GTK_WINDOW( widget ), lastname );
    gtk_label_set_text( label, firstname );
  }
  return FALSE;
}
