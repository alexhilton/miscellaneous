/**
 * ex0201.c
 * solution to ex0201
 */
#include <gtk/gtk.h>

static GtkWidget *label;
static gchararray firstname = "Alex";
static gchararray lastname = "Hilton";

static void destroy( GtkWidget *widget, gpointer pointer );
static gboolean key_pressed( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_widget_set_size_request( window, 320, 240 );
  gtk_window_set_title( GTK_WINDOW( window ), firstname );
  label = gtk_label_new( lastname );
  gtk_label_set_selectable( GTK_LABEL( label ), TRUE );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );

  g_signal_connect( G_OBJECT( window ), "key_press_event", G_CALLBACK( key_pressed ),
		    NULL );
  gtk_container_add( GTK_CONTAINER( window ), label );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}

static gboolean key_pressed( GtkWidget *widget, gpointer pointer ) {
  gchararray title;
  g_object_get( widget, "title", &title, NULL );
  gchararray labeltext;
  g_object_get( label, "label", &labeltext, NULL );
  if ( g_ascii_strcasecmp( firstname, title ) == 0 ) {
    gtk_window_set_title( GTK_WINDOW( widget ), lastname );
  } else {
    gtk_window_set_title( GTK_WINDOW( widget ), firstname );
  }
  if ( g_ascii_strcasecmp( firstname, labeltext ) == 0 ) {
    gtk_label_set_text( GTK_LABEL( label ), lastname );
  } else {
    gtk_label_set_text( GTK_LABEL( label ), firstname );
  }
  return FALSE;
}
