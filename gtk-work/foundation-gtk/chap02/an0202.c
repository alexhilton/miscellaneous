/**
 * ex0202.c
 * solution to ex0202
 */
#include <gtk/gtk.h>
#include <stdio.h>

static gchar *firstname = "Alex";
static gchar *lastname = "Hilton";

static void destroy( GtkWidget *widget, gpointer pointer );
static gboolean key_pressed( GtkWidget *widget, GdkEventKey *event, GtkLabel *label );
static void property_changed( GObject *object, GParamSpec *pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  g_object_set( window, "title", firstname, "width_request", 320, "height_request", 240,
	    "resizable", FALSE, NULL );
  GtkLabel *label = gtk_label_new( lastname );
  g_object_set( label, "selectable", TRUE, NULL );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );

  g_signal_connect( G_OBJECT( window ), "key_press_event", G_CALLBACK( key_pressed ),
		    (gpointer) label );
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

static gboolean key_pressed( GtkWidget *widget, GdkEventKey *event, GtkLabel *label ) {
  gchar *labeltext;
  g_object_get( label, "label", &labeltext, NULL );
  if ( g_ascii_strcasecmp( firstname, labeltext ) == 0 ) {
    g_object_set( label, "label", lastname, NULL );
    g_object_set( widget, "title", firstname, NULL );
  } else {
    g_object_set( label, "label", firstname, NULL );
    g_object_set( widget, "title", lastname, NULL );
  }
  return FALSE;
}

static void property_changed( GObject *widget, GParamSpec *poitner ) {
  gchar *title;
  g_object_get( widget, "title", &title, NULL ); 
  g_message( "Hmm, your window title is changed into: '%s'\n", title );
}
