/**
 * togglebutton.c
 * a demo abut how to use toggle buttons.
 * Create two toggle buttons, click one of them will deactive another one.
 */
#include <gtk/gtk.h>

static void button_toggled( GtkToggleButton *toggleButton, GtkWidget *button );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Toggle Buttons" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *tbnt1 = gtk_toggle_button_new_with_mnemonic( "_Click me will fuck another one" );
  GtkWidget *tbnt2 = gtk_toggle_button_new_with_mnemonic( "_Fuck another one" );

  g_signal_connect( G_OBJECT( tbnt1 ), "toggled", G_CALLBACK( button_toggled ),
		    (gpointer) tbnt2 );
  g_signal_connect( G_OBJECT( tbnt2 ), "toggled", G_CALLBACK( button_toggled ), 
		    (gpointer) tbnt1 ); 
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  GtkWidget *vbox = gtk_vbox_new( TRUE, 10 );
  gtk_box_pack_start_defaults( GTK_BOX( vbox ), tbnt1 );
  gtk_box_pack_start_defaults( GTK_BOX( vbox ), tbnt2 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void button_toggled( GtkToggleButton *toggleButton, GtkWidget *button ) {
  /* there are two ways to set active for a toggle button */
  /* but gtk_toggle_button_set_active does not work */
  if ( gtk_toggle_button_get_active( toggleButton ) ) {
    gtk_widget_set_sensitive( button, FALSE );
    /* gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( button ), FALSE );  */
  } else {
    gtk_widget_set_sensitive( button, TRUE ); 
     /*gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( button ), TRUE );*/
  }
}
