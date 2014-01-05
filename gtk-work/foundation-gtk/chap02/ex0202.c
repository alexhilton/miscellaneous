/**
 * ex0202.c
 * solution to ex0202
 */
#include <gtk/gtk.h>
#include <stdio.h>

static GtkWidget *label;
static gchararray firstname = "Alex";
static gchararray lastname = "Hilton";

static void destroy( GtkWidget *widget, gpointer pointer );
static gboolean key_pressed( GtkWidget *widget, gpointer pointer );
static void property_changed( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  g_object_set( window, "title", firstname, NULL );
  g_object_set( window, "default_height", 240, NULL );
  g_object_set( window, "default_width", 320, NULL );
  label = gtk_label_new( lastname );
  g_object_set( label, "selectable", TRUE, NULL );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );

  g_signal_connect( G_OBJECT( window ), "key_press_event", G_CALLBACK( key_pressed ),
		    NULL );
  g_signal_connect( G_OBJECT( window ), "notify::title", 
		    G_CALLBACK( property_changed ), NULL );
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
  printf( "the title is '%s'\n", title );
  gchararray labeltext;
  g_object_get( label, "label", &labeltext, NULL );
  if ( g_ascii_strcasecmp( firstname, title ) == 0 ) {
    g_object_set( widget, "title", lastname, NULL );
  } else {
    g_object_set( widget, "title", firstname, NULL );
  }
  if ( g_ascii_strcasecmp( firstname, labeltext ) == 0 ) {
    g_object_set( label, "label", lastname, NULL );
  } else {
    g_object_set( label, "label", firstname, NULL );
  }
  return FALSE;
}

static void property_changed( GtkWidget *widget, gpointer poitner ) {
  gchararray title;
  g_object_get( widget, "title", &title, NULL ); 
  g_message( "Hmm, your window title is changed into: '%s'\n", title );
}
