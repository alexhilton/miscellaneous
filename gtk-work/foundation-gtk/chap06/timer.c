/**
 * timer.c
 * how to use GTimer
 */
#include <gtk/gtk.h>

static void button_clicked( GtkButton *button, GTimer *timer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Timer" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  /* Initializ the time */
  GTimer *timer = g_timer_new();
  GtkWidget *button = gtk_button_new_with_label( "Start Timer" );
  g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( button_clicked ), (gpointer) timer );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  gtk_container_add( GTK_CONTAINER( window ), button );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void button_clicked( GtkButton *button, GTimer *timer ) { 
  /* count the amount of elapsed time between two button clicks */
  static gdouble start_time = 0.0f;
  static gdouble end_time = 0.f;
  static gboolean running = FALSE;

  if ( running ) {
    end_time = g_timer_elapsed( timer, NULL );
    gtk_button_set_label( button, "Start Timer" );
    g_print( "Elapsed time: %.2f\n", end_time - start_time );
  } else {
    start_time = g_timer_elapsed( timer, NULL );
    gtk_button_set_label( button, "Stop Timer" );
  }
  running = !running;
}
