/*
 * texttag.c
 * Text tags are actually a very simple concept to apply. This application is created that
 * allows the user to apply multiple sytles or remove all of the tags from the selection.
 */
#include <gtk/gtk.h>

typedef struct {
  gchar *str;
  double scale;
} Text_To_Double;

const Text_To_Double text_scales[] = {
  { "Quarter Sized", 0.25f },
  { "Double Extra Small", PANGO_SCALE_XX_SMALL },
  { "Extra Small", PANGO_SCALE_X_SMALL },
  { "Small", PANGO_SCALE_SMALL },
  { "Medium", PANGO_SCALE_MEDIUM },
  { "Large", PANGO_SCALE_LARGE },
  { "Extra Large", PANGO_SCALE_X_LARGE },
  { "Double Extra Large", PANGO_SCALE_XX_LARGE },
  { "Double Sized", 2.f },
  { NULL, 0.f }
};

static void format( GtkWidget *widget, GtkTextView *textview );
static void scale_changed( GtkComboBox *combo, GtkTextView *textview );
static void clear_clicked( GtkButton *button, GtkTextView *textview );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Text Tags" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 640, 480 );

  GtkWidget *textview = gtk_text_view_new();
  GtkTextBuffer *buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( textview ) );

  /* create tags for buffer, the buffer has a tag table storing those tags */
  gtk_text_buffer_create_tag( buffer, "bold", "weight", PANGO_WEIGHT_BOLD, NULL );
  gtk_text_buffer_create_tag( buffer, "italic", "style", PANGO_STYLE_ITALIC, NULL );
  gtk_text_buffer_create_tag( buffer, "strike", "strikethrough", TRUE, NULL );
  gtk_text_buffer_create_tag( buffer, "underline", "underline", PANGO_UNDERLINE_SINGLE, NULL );

  GtkWidget *bold = gtk_button_new_from_stock( GTK_STOCK_BOLD );
  GtkWidget *italic = gtk_button_new_from_stock( GTK_STOCK_ITALIC );
  GtkWidget *underline = gtk_button_new_from_stock( GTK_STOCK_UNDERLINE );
  GtkWidget *strike = gtk_button_new_from_stock( GTK_STOCK_STRIKETHROUGH );
  GtkWidget *clear = gtk_button_new_from_stock( GTK_STOCK_CLEAR );
  GtkWidget *scale = gtk_combo_box_new_text();

  /* add choices to the GtkComboBox widget */
  int i;
  for ( i = 0; text_scales[i].str != NULL; i++ ) {
    gtk_combo_box_append_text( GTK_COMBO_BOX( scale ), text_scales[i].str );
    gtk_text_buffer_create_tag( buffer, text_scales[i].str, "scale",
				text_scales[i].scale, NULL );
  }

  /* add the name of the text tag as a data parameter of the object */
  g_object_set_data( G_OBJECT( bold ), "tag", "bold" );
  g_object_set_data( G_OBJECT( italic ), "tag", "italic" );
  g_object_set_data( G_OBJECT( underline ), "tag", "underline" );
  g_object_set_data( G_OBJECT( strike ), "tag", "strike" );

  /* connect each of the buttons and the combo box to the necessary signals */
  g_signal_connect( G_OBJECT( bold ), "clicked", G_CALLBACK( format ), 
		    (gpointer) textview );
  g_signal_connect( G_OBJECT( italic ), "clicked", G_CALLBACK( format ),
		    (gpointer) textview );
  g_signal_connect( G_OBJECT( underline ), "clicked", G_CALLBACK( format ),
		    (gpointer) textview );
  g_signal_connect( G_OBJECT( strike ), "clicked", G_CALLBACK( format ),
		    (gpointer) textview );
  g_signal_connect( G_OBJECT( scale ), "changed", G_CALLBACK( scale_changed ),
		    (gpointer) textview );
  g_signal_connect( G_OBJECT( clear ), "clicked", G_CALLBACK( clear_clicked ),
		    (gpointer) textview );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  /* pack the widgets into a gtkvbox, and thenon main window */
  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), bold, FALSE, FALSE, 0 );
  gtk_box_pack_start( GTK_BOX( vbox ), italic, FALSE, FALSE, 0 );
  gtk_box_pack_start( GTK_BOX( vbox ), underline, FALSE, FALSE, 0 );
  gtk_box_pack_start( GTK_BOX( vbox ), strike, FALSE, FALSE, 0 );
  gtk_box_pack_start( GTK_BOX( vbox ), scale, FALSE, FALSE, 0 );
  gtk_box_pack_start( GTK_BOX( vbox ), clear, FALSE, FALSE, 0 );

  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  gtk_container_add( GTK_CONTAINER( scrolled_window ), textview );
  gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scrolled_window ),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS );

  GtkWidget *hbox = gtk_hbox_new( FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( hbox ), scrolled_window, TRUE, TRUE, 0 );
  gtk_box_pack_start( GTK_BOX( hbox ), vbox, FALSE, FALSE, 0 );
  gtk_container_add( GTK_CONTAINER( window ), hbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/* retrieve the tag from the 'tag' object data and apply it to the selection */
static void format( GtkWidget *widget, GtkTextView *textview ) {
  gchar *tagname = (gchar *) g_object_get_data( G_OBJECT( widget ), "tag" );
  GtkTextBuffer *buffer = gtk_text_view_get_buffer( textview );
  GtkTextIter start, end;
  gtk_text_buffer_get_selection_bounds( buffer, &start, &end );
  gtk_text_buffer_apply_tag_by_name( buffer, tagname, &start, &end );
}

/* Apply the selected text size property as the tag */
static void scale_changed( GtkComboBox *combo, GtkTextView *textview ) {
  /*
   * A combo's list should start from 0, I guess, so -1 means you did not
   * selecte any thing.
   */
  if ( gtk_combo_box_get_active( combo ) == -1 ) {
    return;
  }
  const gchar *text = gtk_combo_box_get_active_text( combo );
  g_object_set_data( G_OBJECT( combo ), "tag", (gpointer) text );
  format( GTK_WIDGET( combo ), textview );
  /* 
   * Re-initialize combo, for next selection
   * we cannot initialize it as a valid value, because you cannot distinguish it
   * from initialization or a selection 
   */
  gtk_combo_box_set_active( combo, -1 );
}

/* remove all of the tags from the selected text */
static void clear_clicked( GtkButton *button, GtkTextView *textview ) {
  GtkTextBuffer *buffer = gtk_text_view_get_buffer( textview );
  GtkTextIter start, end;
  gtk_text_buffer_get_selection_bounds( buffer, &start, &end );
  /* Remove all the applications of tags between start and end */
  /*
   * It removes all the instance/application of tags, not removing tags from
   * buffer's tag table
   */
  gtk_text_buffer_remove_all_tags( buffer, &start, &end );
}
