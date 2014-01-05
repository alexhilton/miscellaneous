/**
 * timeout.c
 * show you how to use timeout utility of GLIB
 */
#include <gtk/gtk.h>

static gboolean pulse_progress( GtkProgressBar *progress );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Timeouts" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *progress = gtk_progress_bar_new();
  /*
   * pulse_step is 0.1, pulse every tenth of one second.
   * take one second from one side to another 
   */
  gtk_progress_bar_set_pulse_step( GTK_PROGRESS_BAR( progress ), 0.1 );
  /* 
   * Timeout function pulse_progress will be called every 100 ms (0.1s) 
   * pulse_progress is the timeout function, it takes a pointer and return a
   * gboolean, returning false means timeout function won't be called anymore.
   * last arg is the argument for timeout function pulse_progress.
   */
  g_timeout_add( 100, (GSourceFunc) pulse_progress, (gpointer) progress );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  gtk_widget_set_size_request( progress, 200, 25 );

  gtk_container_add( GTK_CONTAINER( window ), progress );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/* pulse the progress bar and return true so the timeout is called again */
static gboolean pulse_progress( GtkProgressBar *progress ) {
  static gint count = 0;
  gtk_progress_bar_pulse( progress );
  count++;

  return ( count < 25 );
}
