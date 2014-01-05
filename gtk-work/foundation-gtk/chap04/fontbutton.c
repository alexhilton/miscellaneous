/**
 * fontbutton.c
 * how to use a fontbutton.c
 */
#include <gtk/gtk.h>

static void font_changed( GtkFontButton *button, GtkWidget *label );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Font Button" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );


  GtkWidget *label = gtk_label_new( "Look at the font!" );
  PangoFontDescription *initfont = pango_font_description_from_string( "Sans Bold 12" );
  gtk_widget_modify_font( label, initfont );

  /* Create a new font selection button with the given default font */
  GtkWidget *button = gtk_font_button_new_with_font( "Sans Bold 12" );
  gtk_font_button_set_title( GTK_FONT_BUTTON( button ), "Chooser a font" );
  /*
   * by setting the following two attributes, the font will be applied to
   * font button title
   */
  //gtk_font_button_set_use_font( GTK_FONT_BUTTON( button ),  TRUE );
  //gtk_font_button_set_use_size( GTK_FONT_BUTTON( button ), TRUE ); 

  /* Monitor for changes to the font chosen in the font button */
  g_signal_connect( G_OBJECT( button ), "font_set", G_CALLBACK( font_changed ), (gpointer) label );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  /* Arrange widgets and show it to user */
  GtkWidget *vbox = gtk_vbox_new( TRUE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), button, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), label, FALSE, FALSE, 10 );
  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void font_changed( GtkFontButton *button, GtkWidget *label ) {
  const gchar *font = gtk_font_button_get_font_name( button );
  PangoFontDescription *desc = pango_font_description_from_string( font );
  gchar buffer[ 512 ];
  g_snprintf( buffer, sizeof( buffer ), "Font: %s", font );
  gtk_label_set_text( GTK_LABEL( label ), buffer );
  gtk_widget_modify_font( label, desc );
}
