/**
 * passwdentry.c
 * show how to use GtkEntry for password entering.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Passworkd Entry" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  gchar *str = g_strconcat( "What is password for ", g_get_user_name(), "?", NULL );
  GtkWidget *question = gtk_label_new( str );
  GtkWidget *passwd = gtk_label_new( "Password: " );

  GtkWidget *entry = gtk_entry_new();
  gtk_entry_set_visibility( GTK_ENTRY( entry ), FALSE );
  gtk_entry_set_invisible_char( GTK_ENTRY( entry ), '*' );

  GtkWidget *table = gtk_table_new( 2, 2, TRUE );
  gtk_table_attach( GTK_TABLE( table ), question, 0, 2, 0, 1, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), passwd, 0, 1, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), entry, 1, 2, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), table );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
