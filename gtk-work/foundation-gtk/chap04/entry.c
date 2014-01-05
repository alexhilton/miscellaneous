/**
 * entry.c
 * show how to use GtkEntry for general entering.
 */
#include <gtk/gtk.h>

static void reset_pressed( GtkButton *button, GtkEntry *entry );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Passworkd Entry" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *name = gtk_label_new( "Enter login name you want: " );
  GtkWidget *reset = gtk_button_new_with_label( "Reset" );

  GtkWidget *entry = gtk_entry_new();
  gtk_entry_set_visibility( GTK_ENTRY( entry ), TRUE );
  gtk_entry_set_max_length( GTK_ENTRY( entry ), 6 );
  gtk_editable_set_editable( GTK_EDITABLE( entry ), TRUE );

  g_signal_connect( G_OBJECT( reset ), "clicked", G_CALLBACK( reset_pressed ), (gpointer) entry );

  GtkWidget *table = gtk_table_new( 2, 2, TRUE );
  gtk_table_attach( GTK_TABLE( table ), name, 0, 2, 0, 1, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), entry, 0, 1, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), reset, 1, 2, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), table );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void reset_pressed( GtkButton *button, GtkEntry *entry ) {
  /* two alternatives: using either set text or delete text of GtkEditable is OK */
  gtk_entry_set_text( GTK_ENTRY( entry ), "" );
  /* gtk_editable_delete_text( GTK_EDITABLE( entry ), 0, 6 ); */
}
