/**
 * colorbutton.c
 * show you how to use a colorbutton.c
 */
#include <gtk/gtk.h>

static void color_changed( GtkColorButton *button, GtkWidget *widget );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Color Button" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GdkColor color, bgcolor; 

  /* parse a 6 digit hex form color value into a color structure */
  gdk_color_parse( "#003366", &color );
  gdk_color_parse( "#112233", &bgcolor );
  /* we create a color button with a default color */ 
  GtkWidget *colorButton = gtk_color_button_new_with_color( &color );
  gtk_color_button_set_title( GTK_COLOR_BUTTON( colorButton ), "Select a Color" );

  GtkWidget *label = gtk_label_new( "Look at my color" );
  /* set color and state of label with a default value */
  gtk_widget_modify_fg( label, GTK_STATE_NORMAL, &color );
  gtk_widget_modify_bg( label, GTK_STATE_NORMAL, &bgcolor );

  g_signal_connect( G_OBJECT( colorButton ), "color_set", G_CALLBACK( color_changed ), (gpointer) label );

  GtkWidget *hbox = gtk_hbox_new( FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( hbox ), colorButton, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( hbox ), label, FALSE, FALSE, 10 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  gtk_container_add( GTK_CONTAINER( window ), hbox );
  gtk_widget_show_all( window );

  gtk_main();
  return 0;
}

static void color_changed( GtkColorButton *button, GtkWidget *widget ) {
  GdkColor color;
  gtk_color_button_get_color( button, &color );
  gtk_widget_modify_fg( widget, GTK_STATE_NORMAL, &color );
}
