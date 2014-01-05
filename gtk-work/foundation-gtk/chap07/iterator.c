/**
 * iterator.c
 * A simple example that performs two functions. When the 'insert text' button
 * is clicked, the string shown in the GtkEntry widgets is inserted at the
 * current cursor position.When the 'get text' button is clicked, any selected 
 * text is output with g_print()
 */
#include <gtk/gtk.h>

typedef struct {
  GtkWidget *entry;
  GtkWidget *textview;
} Data;

static void insert_clicked( GtkButton *button, Data *data );
static void retrieve_clicked( GtkButton *button, Data *data );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Text Iterator" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 640, 480 );

  Data data;
  data.textview = gtk_text_view_new();
  data.entry = gtk_entry_new();
  GtkWidget *button_insert = gtk_button_new_with_label( "Insert Text" );
  GtkWidget *button_retrieve = gtk_button_new_with_label( "Get Text" );

  g_signal_connect( G_OBJECT( button_insert ), "clicked", G_CALLBACK( insert_clicked ),
		    (gpointer) &data );
  g_signal_connect( G_OBJECT( button_retrieve ), "clicked", G_CALLBACK( retrieve_clicked ),
		    (gpointer) &data );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  gtk_container_add( GTK_CONTAINER( scrolled_window ), data.textview );
  /* use a hbox to arrange entry and two buttons */
  GtkWidget *hbox = gtk_hbox_new( FALSE, 5 );
  gtk_box_pack_start_defaults( GTK_BOX( hbox ), data.entry );
  gtk_box_pack_start_defaults( GTK_BOX( hbox ), button_insert );
  gtk_box_pack_start_defaults( GTK_BOX( hbox ), button_retrieve );

  /* use vbox to arrange scrolled window and hbox */
  GtkWidget *vbox = gtk_vbox_new( FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), scrolled_window, TRUE, TRUE, 0 );
  gtk_box_pack_start( GTK_BOX( vbox ), hbox, FALSE, TRUE, 0 );
  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/* event handler for button insert */
/* when this button is clicked, the text in entry will be inserted into textview */
static void insert_clicked( GtkButton *button, Data *data ) {
  GtkTextBuffer *buffer;
  GtkTextMark *mark;
  GtkTextIter iter; /* it is created on stack, re-usibility. */
  buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( data->textview ) );
  const gchar *text = gtk_entry_get_text( GTK_ENTRY( data->entry ) );
  /*
   * There are two marks that are created by default, insert and
   * selection-bound.
   */
  /* retrieve the mark 'insert' */
  mark = gtk_text_buffer_get_insert( buffer );
  /*
   * Once we get the mark, we can translate it into iterator, so it can be used
   * to maniputlate text buffer.
   */
  gtk_text_buffer_get_iter_at_mark( buffer, &iter, mark );
  gtk_text_buffer_insert( buffer, &iter, text, -1 );
  gtk_entry_set_text( GTK_ENTRY( data->entry ), "" );
}

/* Retrieve the selected text from the GtkTextView and display it to the user */
static void retrieve_clicked( GtkButton *button, Data *data ) {
  GtkTextBuffer *buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( data->textview ) );
  GtkTextIter start, end;
  /* retrieve iters on mark 'selection_bound' */
  gtk_text_buffer_get_selection_bounds( buffer, &start, &end );
  gchar *text = gtk_text_buffer_get_text( buffer, &start, &end, FALSE );
  g_print( "%s\n", text );
}
