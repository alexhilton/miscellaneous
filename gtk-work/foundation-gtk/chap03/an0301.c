#include <gtk/gtk.h>

static void next_pressed( GtkButton *button, GtkNotebook *notebook );
static void prev_pressed( GtkButton *button, GtkNotebook *notebook );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Using Multiple Containers" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 640, 480 );

  GtkWidget *prev = gtk_button_new_with_mnemonic( "_Prev" );
  GtkWidget *exit = gtk_button_new_with_mnemonic( "_Exit" );
  const char *name[] = { "One", "Two", "Three", "Four" };

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  g_signal_connect( G_OBJECT( exit ), "clicked", G_CALLBACK( gtk_main_quit ), NULL );

  GtkWidget *notebook = gtk_notebook_new();
  int i = 0;
  for ( i = 0; i < 4; i++ ) {
    GtkWidget *next = gtk_button_new_with_mnemonic( "_Next" );
    g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );
    gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), next, gtk_label_new( name[ i ] ) );
    gtk_container_set_border_width( GTK_CONTAINER( next ), 10 );
  }
  gtk_notebook_set_tab_pos( GTK_NOTEBOOK( notebook ), GTK_POS_TOP );

  g_signal_connect( G_OBJECT( prev ), "clicked", G_CALLBACK( prev_pressed ), (gpointer) notebook );

  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  GtkWidget *hbox = gtk_hbox_new( TRUE, 5 );
  gtk_box_pack_end( GTK_BOX( hbox ), exit, FALSE, FALSE, 5 );
  gtk_box_pack_end( GTK_BOX( hbox ), prev, FALSE, FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), notebook, TRUE, TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), hbox, TRUE, FALSE, 5 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void next_pressed( GtkButton *button, GtkNotebook *notebook ) {
  gint page = gtk_notebook_get_current_page( notebook );
  if ( page == 3 ) {
    gtk_notebook_set_current_page( notebook, 0 );
  } else {
    gtk_notebook_next_page( notebook );
  }
}

static void prev_pressed( GtkButton *button, GtkNotebook *notebook ) {
  gint page = gtk_notebook_get_current_page( notebook );
  if ( page == 0 ) {
    gtk_notebook_set_current_page( notebook, 3 );
  } else {
    gtk_notebook_prev_page( notebook );
  }
}
