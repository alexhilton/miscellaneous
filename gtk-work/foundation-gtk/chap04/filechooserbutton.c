/**
 * filechooserbutton.c
 * show you how to use a filechooserbutton
 */
#include <gtk/gtk.h>

static void folder_selected( GtkFileChooser *forfolder, GtkFileChooser *forfile );
static void file_selected( GtkFileChooser *chooser, GtkLabel *label );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "File Chooser" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  GtkWidget *label = gtk_label_new( "" );

  /* Create two buttons, one to select a folder and one to select a file */
  GtkWidget *forfolder = gtk_file_chooser_button_new( "Chooser a Folder",
						      GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER );
  GtkWidget *forfile = gtk_file_chooser_button_new( "Select a File",
						    GTK_FILE_CHOOSER_ACTION_OPEN );

  /* Moniter when the selected folder or file are changed */
  g_signal_connect( G_OBJECT( forfolder ), "selection_changed", G_CALLBACK( folder_selected ), 
		    (gpointer) forfile );
  g_signal_connect( G_OBJECT( forfile ), "selection_changed", G_CALLBACK( file_selected ), 
		    (gpointer) label );

  /* Set both file chooser buttons to the location of the user's home directory */
  gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER( forfolder ), g_get_home_dir() );
  gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER( forfile ), g_get_home_dir() );

  /* Provide a filter to show all files and one to show only 3 types of images */
  GtkFileFilter *imageFile = gtk_file_filter_new(); /* for image files */
  GtkFileFilter *textfile = gtk_file_filter_new(); /* for text files */
  GtkFileFilter *allfile = gtk_file_filter_new(); /* for all files */
  GtkFileFilter *sourcefile = gtk_file_filter_new(); /* for program source files */
  gtk_file_filter_set_name( imageFile, "Image Files" );
  gtk_file_filter_set_name( allfile, "All Files" );
  gtk_file_filter_set_name( textfile, "Text Files" );
  gtk_file_filter_set_name( sourcefile, "Source Files" );

  /* Add restrictions of file extension for image files and all files */
  gtk_file_filter_add_pattern( imageFile,  "*.png" );
  gtk_file_filter_add_pattern( imageFile, "*.jpg" );
  gtk_file_filter_add_pattern( imageFile, "*.gif" );
  gtk_file_filter_add_pattern( textfile, "*.txt" );
  gtk_file_filter_add_pattern( sourcefile, "*.c" );
  gtk_file_filter_add_pattern( sourcefile, "*.cc" );
  gtk_file_filter_add_pattern( sourcefile, "*.java" );
  gtk_file_filter_add_pattern( allfile, "*" );

  /* Add both the filters to the file chooser button */
  gtk_file_chooser_add_filter( GTK_FILE_CHOOSER( forfile ), imageFile );
  gtk_file_chooser_add_filter( GTK_FILE_CHOOSER( forfile ), allfile );
  gtk_file_chooser_add_filter( GTK_FILE_CHOOSER( forfile ), textfile );
  gtk_file_chooser_add_filter( GTK_FILE_CHOOSER( forfile ), sourcefile );

  /* Arrange all widgets and show it on window */
  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), forfolder, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), forfile, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), label, FALSE, FALSE, 10 );

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void folder_selected( GtkFileChooser *forfolder, GtkFileChooser *forfile ) {
  gchar *folder = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( forfolder ) );
  gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER( forfile ), folder );
}

static void file_selected( GtkFileChooser *chooser, GtkLabel *label ) {
  gchar *filename = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( chooser ) );
  gtk_label_set_text( label, filename );
}
