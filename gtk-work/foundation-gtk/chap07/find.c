/*
 * find.c
 * The application searches for all instances of the specified string within the text
 * buffer. A dialog is presented to the user, displaying how many times the
 * string was count in the document.
 */
#include <gtk/gtk.h>

typedef struct {
  GtkWidget *entry;
  GtkWidget *textview;
} Data;

static void search_clicked( GtkButton *button, Data *data );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Searching Patterns" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 640, 480 );

  Data data;
  data.textview = gtk_text_view_new();
  data.entry = gtk_entry_new();
  gtk_entry_set_text( GTK_ENTRY( data.entry ), "Search for ..." );
  GtkWidget *find = gtk_button_new_from_stock( GTK_STOCK_FIND );
  g_signal_connect( G_OBJECT( find ), "clicked", G_CALLBACK( search_clicked ),
		    (gpointer) &data );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  gtk_widget_set_size_request( scrolled_window, 480, 320 );
  gtk_container_set_border_width( GTK_CONTAINER( scrolled_window ), 10 );
  gtk_container_add( GTK_CONTAINER( scrolled_window ), data.textview );

  GtkWidget *hbox = gtk_hbox_new( FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( hbox ), data.entry, TRUE, TRUE, 0 );
  gtk_box_pack_start( GTK_BOX( hbox ), find, FALSE, TRUE, 0 );

  GtkWidget *vbox = gtk_vbox_new( FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), scrolled_window, TRUE, TRUE, 0 );
  gtk_box_pack_start( GTK_BOX( vbox ), hbox, FALSE, TRUE, 0 );

  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/*
 * Search for the entered string within the GtkTextView. Then tell the
 * user how man times it was count.
 */
static void search_clicked( GtkButton *button, Data *data ) {
  GtkTextIter start, begin, end;
  gboolean found;

  const gchar *pattern = gtk_entry_get_text( GTK_ENTRY( data->entry ) );
  GtkTextBuffer *buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( data->textview ) );
  gint count = 0;

  /*
   * The lower bound of searching
   */
  gtk_text_buffer_get_start_iter( buffer, &start );
  /*
   * The default upper bound for forward search is end of buffer
   * begin and end indicate the bound of first match.
   * The last param NULL is another iter indicating the lower bound of forward
   * search. Setting NULL means end of buffer.
   */
  found = gtk_text_iter_forward_search( &start, (gchar *) pattern, 0,
					  &begin, &end, NULL );
  while ( found ) {
    /* gtk_text_iter_forward_char( &start ); */
    start = end;
    found = gtk_text_iter_forward_search( &start, (gchar *) pattern, 0,
					     &begin, &end, NULL );
    /* start = begin; */
    count++;
  }

  gchar *output = g_strdup_printf( "The pattern '%s' was found %i times!", pattern, count );
  GtkWidget *dialog = gtk_message_dialog_new( NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
					      GTK_BUTTONS_OK, output, NULL );
  gtk_dialog_run( GTK_DIALOG( dialog ) );
  gtk_widget_destroy( dialog );
  g_free( output );
}
