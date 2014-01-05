/**
 * ex0602.c
 * solution to ex0602
 * counters 
 */
#include <gtk/gtk.h>
#include <stdlib.h>

#define TIMEOUT 10 /* when the counter up to 10, the timeout should not be called again */

typedef struct Data {
  GtkWidget *left;
  GtkWidget *right;
} Data;

static void left_button_clicked( GtkButton *button, GtkLabel *label );
static void right_button_clicked( GtkButton *button, GtkLabel *label );
static gboolean increment_counter( Data *data );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Ex0602" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 360, 200 );

  GtkWidget *left_label = gtk_label_new( "0" );
  GtkWidget *right_label = gtk_label_new( "0" );
  GtkWidget *left_button = gtk_button_new_with_mnemonic( "Reset _Left Counter" );
  GtkWidget *right_button = gtk_button_new_with_mnemonic( "Reset _Rigth Counter" );
  Data data;
  data.left = left_label;
  data.right = right_label;

  g_timeout_add( 1000, (GSourceFunc) increment_counter, (gpointer) &data );

  g_signal_connect( G_OBJECT( left_button ), "clicked", G_CALLBACK( left_button_clicked ),
		    (gpointer) left_label );
  g_signal_connect( G_OBJECT( right_button ), "clicked", G_CALLBACK( right_button_clicked ),
		    (gpointer) right_label );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  GtkWidget *left_vbox = gtk_vbox_new( FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( left_vbox ), left_label, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( left_vbox ), left_button, FALSE, FALSE, 10 );
  GtkWidget *right_vbox = gtk_vbox_new( FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( right_vbox ), right_label, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( right_vbox ), right_button, FALSE, FALSE, 10 );
  GtkWidget *hbox = gtk_hbox_new( FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( hbox ), left_vbox, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( hbox ), right_vbox, FALSE, FALSE, 10 );

  gtk_container_add( GTK_CONTAINER( window ), hbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

static void left_button_clicked( GtkButton *button, GtkLabel *label ) {
  gtk_label_set_text( label, "0" );
}

static void right_button_clicked( GtkButton *button, GtkLabel *label ) {
  gtk_label_set_text( label, "0" );
}

static gboolean increment_counter( Data *data ) {
  const gchar *count_text = gtk_label_get_text( GTK_LABEL( data->left ) );
  int count = atoi( count_text );
  if ( count > TIMEOUT ) {
    return FALSE;
  }
  char buf[ 32 ];
  sprintf( buf, "%d", ++count );
  gtk_label_set_text( GTK_LABEL( data->left ), buf );
  count_text = gtk_label_get_text( GTK_LABEL( data->right ) );
  count = atoi( count_text );
  if ( count > TIMEOUT ) {
    return FALSE;
  }
  sprintf( buf, "%d", ++count );
  gtk_label_set_text( GTK_LABEL( data->right ), buf );
  return TRUE;
}
