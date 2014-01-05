/**
 * moretextview.c
 * Show many of the properties that can be used to customize the whole content of
 * a GtkTextBuffer. 
 * Note: that many of these properties could be overridden in inidividual
 * sections of a document with text tags.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Text View properties" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 640, 480 );

  PangoFontDescription *font = pango_font_description_from_string( "Monospace Bold 10" );
  GtkWidget *textview = gtk_text_view_new();
  gtk_widget_modify_font( textview, font );

  /* set more properties */
  gtk_text_view_set_wrap_mode( GTK_TEXT_VIEW( textview ), GTK_WRAP_WORD );
  /*
   * Justification is alignment, left alignment, right alignment or central
   * alignment.
   */
  gtk_text_view_set_justification( GTK_TEXT_VIEW( textview ), GTK_JUSTIFY_LEFT );
  gtk_text_view_set_editable( GTK_TEXT_VIEW( textview ), TRUE );
  gtk_text_view_set_cursor_visible( GTK_TEXT_VIEW( textview ), TRUE );
  gtk_text_view_set_pixels_above_lines( GTK_TEXT_VIEW( textview ), 5 );
  gtk_text_view_set_pixels_below_lines( GTK_TEXT_VIEW( textview ), 5 );
  gtk_text_view_set_pixels_inside_wrap( GTK_TEXT_VIEW( textview ), 5 );

  gtk_text_view_set_left_margin( GTK_TEXT_VIEW( textview ), 10 );
  gtk_text_view_set_right_margin( GTK_TEXT_VIEW( textview ), 10 );
  GtkTextBuffer *buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( textview ) );
  gtk_text_buffer_set_text( buffer, "With great power comes great responsibility\n"
			    "the tree of liberty must be refreshed\n"
			    "from time to time with blood of patroits and tyrants!", -1 );
  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scrolled_window ),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  gtk_container_add( GTK_CONTAINER( scrolled_window ), textview );
  gtk_container_add( GTK_CONTAINER( window ), scrolled_window );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
