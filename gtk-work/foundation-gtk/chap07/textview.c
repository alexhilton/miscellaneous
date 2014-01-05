/**
 * textview.c
 * This example illustrates one of the simplest text view examples you could create.
 * A new GtkTextView widget is created. Its buffer is retrieved, and text is inserted 
 * into the buffer. A scrolled window is then used to contain the text view.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Text View" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 480, 320 );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  /* most important part of the program */
  /* create the text view, retrieve its buffer and set text into the buffer */
  GtkWidget *textview = gtk_text_view_new();
  GtkTextBuffer *buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( textview ) );
  gtk_text_buffer_set_text( buffer, "With great power comes great responsibility.\n"
			    "the tree of liberty must be refreshed from time to time with bloods"
			    "of patroits and tyrants.", -1 );

  /* use a scrolled window to hold text view */
  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scrolled_window ), 
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );

  gtk_container_add( GTK_CONTAINER( scrolled_window ), textview );
  gtk_container_add( GTK_CONTAINER( window ), scrolled_window );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
