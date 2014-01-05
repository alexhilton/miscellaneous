/*
 * ex0302.c
 * solution to ex0302
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );
static void next_pressed( GtkButton *button, GtkNotebook *notebook );
static void prev_pressed( GtkButton *button, GtkNotebook *notebook );
static void exit_pressed( GtkButton *button, GtkNotebook *notebook );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Using Multiple Containers" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 640, 480 );

  GtkWidget *notebook = gtk_notebook_new();
  GtkWidget *one = gtk_label_new( "One" );
  GtkWidget *two = gtk_label_new( "Two" );
  GtkWidget *three = gtk_label_new( "Three" );
  GtkWidget *four = gtk_label_new( "Four" );
  GtkWidget *tag1 = gtk_label_new( "This is page one" );
  GtkWidget *tag2 = gtk_label_new( "This is page TWO" );
  GtkWidget *tag3 = gtk_label_new( "This is page THree" );
  GtkWidget *tag4 = gtk_label_new( "This is page FouR" );
  GtkWidget *next = gtk_button_new_with_label( "Next" );
  GtkWidget *prev = gtk_button_new_with_label( "Prev" );
  GtkWidget *exit = gtk_button_new_with_label( "Exit" );
  GtkWidget *vpane = gtk_vpaned_new();
  GtkWidget *hbox = gtk_hbox_new( TRUE, 10 );
  GtkWidget *nvbox1 = gtk_vbox_new( TRUE, 5 );
  GtkWidget *nvbox2 = gtk_vbox_new( TRUE, 5 );
  GtkWidget *nvbox3 = gtk_vbox_new( TRUE, 5 );
  GtkWidget *nvbox4 = gtk_vbox_new( TRUE, 5 );
  GtkWidget *expander = gtk_expander_new_with_mnemonic( "click here to show _Next button" );

  gtk_container_add( GTK_CONTAINER( expander ), next );
  gtk_expander_set_expanded( GTK_EXPANDER( expander ), TRUE );
  g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );
  gtk_box_pack_start( GTK_BOX( nvbox1 ), tag1, FALSE, FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( nvbox1 ), expander, FALSE, FALSE, 5 );
  expander = gtk_expander_new_with_mnemonic( "click here to show _Next button" );
  gtk_expander_set_expanded( GTK_EXPANDER( expander ), TRUE );
  next = gtk_button_new_with_label( "Next" );
  g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );
  gtk_container_add( GTK_CONTAINER( expander ), next );
  gtk_box_pack_start( GTK_BOX( nvbox2 ), tag2, FALSE, FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( nvbox2 ), expander, FALSE, FALSE, 5 );
  expander = gtk_expander_new_with_mnemonic( "click here to show _Next button" );
  gtk_expander_set_expanded( GTK_EXPANDER( expander ), TRUE );
  next = gtk_button_new_with_label( "Next" );
  g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );
  gtk_container_add( GTK_CONTAINER( expander ), next );
  gtk_box_pack_start( GTK_BOX( nvbox3 ), tag3, FALSE, FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( nvbox3 ), expander, FALSE, FALSE, 5 );
  expander = gtk_expander_new_with_mnemonic( "click here to show _Next button" );
  gtk_expander_set_expanded( GTK_EXPANDER( expander ), TRUE );
  next = gtk_button_new_with_label( "Next" );
  g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );
  gtk_container_add( GTK_CONTAINER( expander ), next );
  gtk_box_pack_start( GTK_BOX( nvbox4 ), tag4, FALSE, FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( nvbox4 ), expander, FALSE, FALSE, 5 );


  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), nvbox1, one );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), nvbox2, two );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), nvbox3, three );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), nvbox4, four );
  gtk_notebook_set_tab_pos( GTK_NOTEBOOK( notebook ), GTK_POS_TOP );
  gtk_notebook_set_show_tabs( GTK_NOTEBOOK( notebook ), TRUE );

  g_signal_connect( G_OBJECT( prev ), "clicked", G_CALLBACK( prev_pressed ), (gpointer) notebook );
  g_signal_connect( G_OBJECT( exit ), "clicked", G_CALLBACK( exit_pressed ), NULL );

  gtk_box_pack_end( GTK_BOX( hbox ), exit, TRUE, FALSE, 5 );
  gtk_box_pack_end( GTK_BOX( hbox ), prev, TRUE, FALSE, 5 );

  gtk_paned_pack1( GTK_PANED( vpane ), notebook, TRUE, FALSE );
  gtk_paned_pack2( GTK_PANED( vpane ), hbox, TRUE, FALSE );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), vpane );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}

static void next_pressed( GtkButton *button, GtkNotebook *notebook ) {
  gint page = gtk_notebook_get_current_page( notebook );
  page = ( page + 1 ) % 4;
  gtk_notebook_set_current_page( notebook, page );
}

static void prev_pressed( GtkButton *button, GtkNotebook *notebook ) {
  gint page = gtk_notebook_get_current_page( notebook );
  page = ( page + 3 ) % 4;
  gtk_notebook_set_current_page( notebook, page );
}

static void exit_pressed( GtkButton *button, GtkNotebook *notebook ) {
  gtk_main_quit();
}
