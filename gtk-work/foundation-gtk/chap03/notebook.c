/**
 * notebook.c
 * show you how to use GtkNotebook
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );
static void switch_page( GtkButton *button, GtkNotebook *notebook );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Notebook" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *notebook = gtk_notebook_new();
  GtkWidget *tab1 = gtk_label_new( "Page1" );
  GtkWidget *tab2 = gtk_label_new( "Page2" );
  GtkWidget *page1 = gtk_label_new( "With great power, comes great\nresponsibility" );
  GtkWidget *page2 = gtk_label_new( "the tree of liberty must be refreshed from\ntime to time with the blood\nof patoits and tyrants" );

  g_signal_connect( G_OBJECT( tab1 ), "clicked", G_CALLBACK( switch_page ), (gpointer) notebook );
  g_signal_connect( G_OBJECT( tab2 ), "clicked", G_CALLBACK( switch_page ), (gpointer) notebook );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), page1, tab1 );
  gtk_notebook_append_page( GTK_NOTEBOOK( notebook ), page2, tab2 );
  gtk_notebook_set_tab_pos( GTK_NOTEBOOK( notebook ), GTK_POS_TOP );

  gtk_container_add( GTK_CONTAINER( window ), notebook );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}

static void switch_page( GtkButton *button, GtkNotebook *notebook ) {
  gint page = gtk_notebook_get_current_page( notebook );
  if ( page == 0 ) {
    gtk_notebook_set_current_page( notebook, 1 );
  } else {
    gtk_notebook_set_current_page( notebook, 0 );
  }
}
