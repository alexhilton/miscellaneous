/**
 * table.c
 * demonstration of using GtkTable
 */
#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer pointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_widget_set_size_request( window, 320, 240 );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_window_set_title( GTK_WINDOW( window ), "Table" );

  GtkWidget *table = gtk_table_new( 2, 2, TRUE );
  GtkWidget *hint = gtk_label_new( "Entering the following information..." );
  GtkWidget *name = gtk_label_new( "Name: " );
  GtkWidget *entry = gtk_entry_new();

  /* now attatch labels and entry onto table, note the positioning */
  gtk_table_attach( GTK_TABLE( table ), hint, 0, 2, 0, 1, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), name, 0, 1, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), entry, 1, 2, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( destroy ), NULL );

  /* add five more pixels for spacing */
  gtk_table_set_row_spacings( GTK_TABLE( table ), 5 );
  gtk_table_set_col_spacings( GTK_TABLE( table ), 5 );

  gtk_container_add( GTK_CONTAINER( window ), table );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void destroy( GtkWidget *widget, gpointer pointer ) {
  gtk_main_quit();
}
