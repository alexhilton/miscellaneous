/**
 * spinbutton.c
 * how to use a spinbutton.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Spin Button" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  /*
   * to use a spin button, you have to create a GtkAdjustment which is
   * a some kind of arrage control widget for it.
   * the arguments for gtk_adjustment_new are:
   * gint init_value: the value stored by adjustment when it is initialized.
   * gint lower_range: the minimum value the adjustment will be allowed to hold.
   * gint upper_range: the maximum value the adjustment will be allowed to hold.
   * gint step_increment: the increment step.
   * gint page_increment: the inrement to make when Page UP or Page Down is pressed.
   * gint page_size: the size of a page.
   */
  GtkAdjustment *integerAdjust = GTK_ADJUSTMENT( gtk_adjustment_new(5.0f, 0.0f, 10.0f, 1.0f, 2.0f, .0f) );
  GtkAdjustment *floatAdjust = GTK_ADJUSTMENT( gtk_adjustment_new( 0.5f, 0.0f, 1.0f, 0.1f, 0.5f, 0.f ) );

  /*
   * create spin buttons for integer and float, with integerAdjust and
   * floatAjdust as its arguments.
   * the arguments for gtk_spin_button_new:
   * GtkAdjustment *: the adjustment set to it.
   * gdouble step: climb rate
   * gint: number of digits
   */
  GtkWidget *integerSpin = gtk_spin_button_new( integerAdjust, 1.0, 0 );
  GtkWidget *floatSpin = gtk_spin_button_new( floatAdjust, 0.1, 1 );

  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), integerSpin, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), floatSpin, FALSE, FALSE, 10 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
