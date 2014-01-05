#include <gtk/gtk.h>

/*
 * This is a callback function. the data arguments are ignored in this example.
 * More on callback below.
 */
void hello( GtkWidget *widget, gpointer data ) {
  g_print( "Hello world\n" );
}

gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data ) {
  /*
   * If you return false in the "delete_event" signal handler, GTK will emit the "destory"
   * signal. Returning TRue means you don't want the window to be destoryed. 
   * This is useful for popping up 'are you sure you want quit?' type dialogs.
   */
  g_print( "delete event occured\n" );
  return TRUE;
}

/*
 * another callback
 */
void destory( GtkWidget *widget, gpointer data ) {
  gtk_main_quit();
}

int main( int argc, char *argv[] ) {
  /*
   * GtkWidget is the storage type for widgets 
   */
  GtkWidget *window;
  GtkWidget *button;
  /*
   * This is called in all GTK applications. Arguments are passed from the command line and are
   * returned to the application 
   */
  gtk_init( &argc, &argv );

  /* create a new window */
  window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  /*
   * When the window is given the "delete_event" signal (this is given by the window manager, usually by
   * the close option, or on the titlebar), we ask it to call the delete_event() function as defined
   * above. The data passed to the callback function is NULL and is ignored in the callback function.
   */
  g_signal_connect( G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL );

  /*
   * Here we connect the "destory" event to a signal handler.
   * This event occurs when we call gtk_widget_destory() on the window, or if we return FALSE in the
   * "delete_event" callback.
   */
  g_signal_connect( G_OBJECT(window), "destory", G_CALLBACK(destory), NULL );

  /* Sets the border width of the window */
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );

  /* creates a new button with the label "Hello, world". */
  button = gtk_button_new_with_label( "Hello, world" );

  /*
   * When the button receives the "clicked" signal, it will call the function hello() passing
   * is NULL as its argument. The hello() function is defined above.
   */
  g_signal_connect( G_OBJECT(button), "clicked", G_CALLBACK(hello), NULL );

  /*
   * This will cause the window to be destoryed by calling gtk_widget_destory(window) when
   * "clicked". Again, the destory signal could come from here, or the window manager.
   */
  g_signal_connect_swapped( G_OBJECT(button), "clicked", G_CALLBACK(destory), 
			    G_OBJECT(window) );

  /*
   * This packs the button into the window (a GTK container).
   */
  gtk_container_add( GTK_CONTAINER(window), button );

  /*
   * The final step is to display this newly created widget.
   */
  gtk_widget_show( button );

  /* and the window */
  gtk_widget_show( window );

  /*
   * all GTK applications must have a gtk_main(). Control ends here and waits for an event to occur
   * like a key press or a mouse event.
   */
  gtk_main();
  return 0;
}
