/*
 * This program shows a GtkTextView widget that contains a child GtkButton widget.
 * This can be used to create this window. When the button is pressed, gtk_main_quit()
 * is called which terminates the application.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Child Widgets" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *textview = gtk_text_view_new();
  GtkTextBuffer *buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( textview ) );
  gtk_text_buffer_set_text( buffer, "\n Click  to exit!", -1 );

  /* create a new child widget anchor at the specified iterator */
  GtkTextIter iter;
  gtk_text_buffer_get_iter_at_offset( buffer, &iter, 8 );
  GtkTextChildAnchor *anchor;
  anchor = gtk_text_buffer_create_child_anchor( buffer, &iter );

  /* insert a GtkButton widget at the child anchor */
  GtkWidget *exit = gtk_button_new_with_label( "Exit" );
  gtk_text_view_add_child_at_anchor( GTK_TEXT_VIEW( textview ),
				     exit, anchor );
  g_signal_connect_swapped( G_OBJECT( exit ), "clicked", G_CALLBACK( gtk_widget_destroy ),
		    (gpointer) window );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ),
		    NULL );

  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  gtk_container_add( GTK_CONTAINER( scrolled_window ), textview );
  gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scrolled_window ),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS );
  gtk_container_add( GTK_CONTAINER( window ), scrolled_window );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
