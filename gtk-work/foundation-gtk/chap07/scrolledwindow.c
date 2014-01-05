/**
 * scrolledwindow.c
 * show you how to use scrolled windows and viewports.
 * The scroll window can scroll by itself, it have default adjustments if you
 * don't provide. The viewport needs adjustments to scroll.
 * In this example, we create a scrolled window without specifying adjustments.
 * Then we retrieve the default adjustments of scrolled window and set them to
 * viewport. This will make the two widgets synchronous.
 * viewport and scrolled window are containers with scrolling abilities.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Scrolled window and view port" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 640, 480 );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  /* create the contents of the window, it is a table with 10*10 buttons */
  GtkWidget *table1 = gtk_table_new( 10, 10, TRUE );
  GtkWidget *table2 = gtk_table_new( 10, 10, TRUE );
  gtk_table_set_row_spacings( GTK_TABLE( table1 ), 5 );
  gtk_table_set_row_spacings( GTK_TABLE( table2 ), 5 );
  gtk_table_set_col_spacings( GTK_TABLE( table1 ), 5 );
  gtk_table_set_col_spacings( GTK_TABLE( table2 ), 5 );

  /* pack 100 buttons to both tables */
  GtkWidget *buttons1[ 10 ][ 10 ];
  GtkWidget *buttons2[ 10 ][ 10 ];
  int i, j;
  for ( i = 0; i < 10; i++ ) {
    for ( j = 0; j < 10; j++ ) {
      buttons1[i][j] = gtk_button_new_from_stock( GTK_STOCK_CLOSE );
      buttons2[i][j] = gtk_button_new_from_stock( GTK_STOCK_APPLY );
      gtk_button_set_relief( GTK_BUTTON( buttons1[i][j] ), GTK_RELIEF_NONE );
      gtk_button_set_relief( GTK_BUTTON( buttons2[i][j] ), GTK_RELIEF_NONE );
      gtk_table_attach_defaults( GTK_TABLE( table1 ), buttons1[i][j], i, i+1, j, j+1 );
      gtk_table_attach_defaults( GTK_TABLE( table2 ), buttons2[i][j], i, i+1, j, j+1 );
    }
  }

  /* most important part use scrolled window and veiwport to showing multilines contents */
  /*
   * Create a scrolled window and a viewport, each with one table. Use the adjustments in
   * the scrolled window to sychronize both containers
   */
  /* we use default adjustments for vertical and horizontal scroll */
  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  GtkAdjustment *horizontal = gtk_scrolled_window_get_hadjustment( GTK_SCROLLED_WINDOW( scrolled_window ) );
  GtkAdjustment *vertical = gtk_scrolled_window_get_vadjustment( GTK_SCROLLED_WINDOW( scrolled_window ) );
  GtkWidget *viewport = gtk_viewport_new( horizontal, vertical );

  /* add table into window */
  gtk_container_set_border_width( GTK_CONTAINER( scrolled_window ), 5 );
  gtk_container_set_border_width( GTK_CONTAINER( viewport ), 5 );
  /* set which way the scroll will act, always, automatic(when necessary) or never */
  gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scrolled_window ), 
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
  /**
   * scroll window needs its child having scroll abilities. If not, we should
   * make it have, with a anonymous viewport to it which is done by 
   * gtk_scrolled_window_add_with_viewport.
   * If for GtkViewport or other widgets with scrolling abilities, we can simply
   * add it to scroll window by 
   * gtk_scrolled_window_add.
   */
  gtk_scrolled_window_add_with_viewport( GTK_SCROLLED_WINDOW( scrolled_window ), table1 );
  gtk_container_add( GTK_CONTAINER( viewport ), table2 );

  /* pack the widgets into a gtkbox and then into the main window */
  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start_defaults( GTK_BOX( vbox ), viewport );
  gtk_box_pack_start_defaults( GTK_BOX( vbox ), scrolled_window );
  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
