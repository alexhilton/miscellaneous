/*
 * menubar.c
 * a demo to menubar 
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Menu Bars" );
  gtk_widget_set_size_request( window, 320, -1 );

  GtkAccelGroup *group = gtk_accel_group_new();
  GtkWidget *menubar = gtk_menu_bar_new();
  GtkWidget *file = gtk_menu_item_new_with_label( "File" );
  GtkWidget *edit = gtk_menu_item_new_with_label( "Edit" );
  GtkWidget *help = gtk_menu_item_new_with_label( "Help" );
  GtkWidget *filemenu = gtk_menu_new();
  GtkWidget *editmenu = gtk_menu_new();
  GtkWidget *helpmenu = gtk_menu_new();

  gtk_menu_item_set_submenu( GTK_MENU_ITEM( file ), filemenu );
  gtk_menu_item_set_submenu( GTK_MENU_ITEM( edit ), editmenu );
  gtk_menu_item_set_submenu( GTK_MENU_ITEM( help ), helpmenu );

  gtk_menu_shell_append( GTK_MENU_SHELL( menubar ), file );
  gtk_menu_shell_append( GTK_MENU_SHELL( menubar ), edit );
  gtk_menu_shell_append( GTK_MENU_SHELL( menubar ), help );

  /* Create the file menu content */
  GtkWidget *new = gtk_image_menu_item_new_from_stock( GTK_STOCK_NEW, group );
  GtkWidget *open = gtk_image_menu_item_new_from_stock( GTK_STOCK_OPEN, group );
  GtkWidget *save = gtk_image_menu_item_new_from_stock( GTK_STOCK_SAVE, group );
  GtkWidget *save_as = gtk_image_menu_item_new_from_stock( GTK_STOCK_SAVE_AS, group );
  GtkWidget *quit = gtk_image_menu_item_new_from_stock( GTK_STOCK_QUIT, group );
  gtk_menu_shell_append( GTK_MENU_SHELL( filemenu ), new );
  gtk_menu_shell_append( GTK_MENU_SHELL( filemenu ), open );
  gtk_menu_shell_append( GTK_MENU_SHELL( filemenu ), save );
  gtk_menu_shell_append( GTK_MENU_SHELL( filemenu ), save_as );
  gtk_menu_shell_append( GTK_MENU_SHELL( filemenu ), quit );

  /* Create the Edit menu conetent */
  GtkWidget *cut = gtk_image_menu_item_new_from_stock( GTK_STOCK_CUT, group );
  GtkWidget *copy = gtk_image_menu_item_new_from_stock( GTK_STOCK_COPY, group );
  GtkWidget *paste = gtk_image_menu_item_new_from_stock( GTK_STOCK_PASTE, group );
  GtkWidget *find = gtk_image_menu_item_new_from_stock( GTK_STOCK_FIND, group );
  GtkWidget *replace = gtk_image_menu_item_new_with_label( "Replace" );
  GtkWidget *undo = gtk_image_menu_item_new_from_stock( GTK_STOCK_UNDO, group );
  gtk_menu_shell_append( GTK_MENU_SHELL( editmenu ), undo );
  gtk_menu_shell_append( GTK_MENU_SHELL( editmenu ), cut );
  gtk_menu_shell_append( GTK_MENU_SHELL( editmenu ), copy );
  gtk_menu_shell_append( GTK_MENU_SHELL( editmenu ), paste );
  gtk_menu_shell_append( GTK_MENU_SHELL( editmenu ), find );
  gtk_menu_shell_append( GTK_MENU_SHELL( editmenu ), replace );

  /* Create the Help menu content */
  GtkWidget *contents = gtk_image_menu_item_new_from_stock( GTK_STOCK_HELP, group );
  GtkWidget *about = gtk_image_menu_item_new_from_stock( GTK_STOCK_ABOUT, group );
  gtk_menu_shell_append( GTK_MENU_SHELL( helpmenu ), contents );
  gtk_menu_shell_append( GTK_MENU_SHELL( helpmenu ), about );

  gtk_container_add( GTK_CONTAINER( window ), menubar );
  gtk_window_add_accel_group( GTK_WINDOW( window ), group );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
