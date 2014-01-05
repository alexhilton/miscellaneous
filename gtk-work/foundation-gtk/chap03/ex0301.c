/*
 * ex0301.c
 * solution to ex0301
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
  GtkWidget *next = gtk_button_new_with_label( "Next" );
  GtkWidget *prev = gtk_button_new_with_label( "Prev" );
  GtkWidget *exit = gtk_button_new_with_label( "Exit" );
  GtkWidget *vbox = gtk_vbox_new( TRUE, 10 );
  GtkWidget *hbox = gtk_hbox_new( TRUE, 10 );

  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), next, one );
  g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );
  next = gtk_button_new_with_label( "Next" );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), next, two );
  g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );
  next = gtk_button_new_with_label( "Next" );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), next, three );
  g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );
  next = gtk_button_new_with_label( "Next" );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), next, four );
  g_signal_connect( G_OBJECT( next ), "clicked", G_CALLBACK( next_pressed ), (gpointer) notebook );

  gtk_notebook_set_tab_pos( GTK_NOTEBOOK( notebook ), GTK_POS_TOP );

  g_signal_connect( G_OBJECT( exit ), "clicked", G_CALLBACK( exit_pressed ), NULL );
  g_signal_connect( G_OBJECT( prev ), "clicked", G_CALLBACK( prev_pressed ), (gpointer) notebook );

  gtk_box_pack_end( GTK_BOX( hbox ), exit, TRUE, FALSE, 5 );
  gtk_box_pack_end( GTK_BOX( hbox ), prev, TRUE, FALSE, 5 );

  gtk_box_pack_start( GTK_BOX( vbox ), notebook, TRUE, TRUE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), hbox, FALSE, FALSE, 10 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), vbox );
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
