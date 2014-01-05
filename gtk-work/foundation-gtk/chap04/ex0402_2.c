/**
 * ex0402.c
 * a different solution to ex0402
 * the way of creating spin and scale are different
 */
#include <gtk/gtk.h>

static int synchronized = 0;
static void check_toggled( GtkCheckButton *button, gpointer pointer );
static void scaled( GtkScale *scale, GtkSpinButton *spin );
static void spined( GtkSpinButton *spin, GtkScale *scale );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL ); 
  gtk_window_set_title( GTK_WINDOW( window ), "Ex0402" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *sync = gtk_check_button_new_with_mnemonic( "_Synchronize" );

  g_signal_connect( G_OBJECT( sync ), "toggled", G_CALLBACK( check_toggled ), NULL );

  /* create spin button and scale button based on adjustment */
  GtkWidget *spin = gtk_spin_button_new_with_range( 1.0f, 10.f, 1.f );
  GtkWidget *scale = gtk_hscale_new_with_range( 1.f, 10.f, 1.f );
  gtk_scale_set_value_pos( GTK_SCALE( scale ), GTK_POS_RIGHT );
  gtk_scale_set_digits( GTK_SCALE( scale ), 0 );

  g_signal_connect( G_OBJECT( spin ), "value_changed", G_CALLBACK( spined ), (gpointer) scale );
  g_signal_connect( G_OBJECT( scale ), "value_changed", G_CALLBACK( scaled ), (gpointer) spin );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  /* use a vbox to organize all widgets */
  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), sync, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), spin, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), scale, FALSE, FALSE, 10 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void check_toggled( GtkCheckButton *button, gpointer pointer ) {
  synchronized = 1 - synchronized;
  printf( "synchronized is '%s'\n", synchronized ? "True" : "False" );
}

static void spined( GtkSpinButton *button, GtkScale *scale ) {
  if ( synchronized ) {
    gdouble value = gtk_spin_button_get_value( button );
    printf( "spin is %g and set it to scale\n", value );
    gtk_range_set_value( GTK_RANGE( scale ), value );
  }
}

static void scaled( GtkScale *scale, GtkSpinButton *button ) {
  if ( synchronized ) {
    gdouble value = gtk_range_get_value( GTK_RANGE( scale ) );
    printf( "scale is %g and set it to spin\n", value );
    gtk_spin_button_set_value( button, value );
  }
}
