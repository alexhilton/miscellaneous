/**
 * ex0401.c
 * solution to ex0401
 */
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

static void file_selected( GtkFileChooserButton *button, GtkWidget *widget );
static void text_entered( GtkEntry *entry, GtkFileChooserButton *button );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Exercise 0401" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  /* use a file chooser to choose a file of all file types */
  GtkWidget *file = gtk_file_chooser_button_new( "Choose a file", GTK_FILE_CHOOSER_ACTION_OPEN );
  gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER( file ), g_get_home_dir() );
  GtkFileFilter *filter = gtk_file_filter_new();
  gtk_file_filter_set_name( filter, "All Files" );
  gtk_file_filter_add_pattern( filter, "*" );
  gtk_file_chooser_add_filter( GTK_FILE_CHOOSER( file ), filter );

  /* create an entry for user to enter a new for the file selected from file chooser */
  GtkWidget *entry = gtk_entry_new();
  gtk_entry_set_visibility( GTK_ENTRY( entry ), TRUE );
  gtk_entry_set_max_length( GTK_ENTRY( entry ), 255 );
  gtk_editable_set_editable( GTK_EDITABLE( entry ), FALSE );

  /* creating event handler functions */
  g_signal_connect( G_OBJECT( file ), "selection_changed", G_CALLBACK( file_selected ), (gpointer) entry );
  g_signal_connect( G_OBJECT( entry ), "activate", G_CALLBACK( text_entered ), (gpointer) file );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  /* use container vbox to organize the widgets */
  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), file, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), entry, FALSE, FALSE, 10 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void file_selected( GtkFileChooserButton *button, GtkWidget *widget ) {
  gtk_editable_set_editable( GTK_EDITABLE( widget ), TRUE );
}

static void text_entered( GtkEntry *entry, GtkFileChooserButton *button ) {
  const gchar *newname = gtk_entry_get_text( entry );
  const gchar *filename = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( button ) );

  gchar tmp[ 256 ];
  strcpy( tmp, filename );
  gchar *ch = strrchr( tmp, '/' );
  *ch = '\0';
  strcat( tmp, "/" );
  strcat( tmp, newname );
  printf( "rename file '%s' to '%s'\n", filename, tmp );
  if ( rename( filename, tmp ) == 0 ) {
    /* success renaming file */
  } else {
    gtk_widget_set_sensitive( GTK_WIDGET( button ), FALSE );
  }
  gtk_editable_set_editable( GTK_EDITABLE( entry ), FALSE );
}
