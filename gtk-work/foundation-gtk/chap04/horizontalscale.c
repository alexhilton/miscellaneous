/**
 * horizontalscale.c
 * show yuou how to use a horizontal scales.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Horizontal Scale" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  /* 
   * create two horizontal scales, one for integer and one for float.
   * the arguments for gtk_hscale_new_with_range
   * gdouble min
   * gdouble max
   * gdouble step
   */
  GtkWidget *integerScale = gtk_hscale_new_with_range( 1.0f, 10.0f, 1.0f );
  GtkWidget *floatScale = gtk_hscale_new_with_range( .0f, 1.f, .1f );

  /*
   * set number of digits showed to user.
   */
  gtk_scale_set_digits( GTK_SCALE( integerScale ), 0 );
  gtk_scale_set_digits( GTK_SCALE( floatScale ), 1 );

  /*
   * set the position in which you want show the number.
   */
  gtk_scale_set_value_pos( GTK_SCALE( integerScale ), GTK_POS_LEFT );
  gtk_scale_set_value_pos( GTK_SCALE( floatScale ), GTK_POS_LEFT );

  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), integerScale, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), floatScale, FALSE, FALSE, 10 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
