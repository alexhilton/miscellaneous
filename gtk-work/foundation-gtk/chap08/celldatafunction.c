/*
 * celldatafunction.c
 * Use celldata function to renderer cells, change the color 
 * according to the data stored in the cell.
 */
#include <gtk/gtk.h>

enum { COLOR = 0x00, COLUMNS  = 0x01 };

const gchar *color[ 6 ] = { "00", "33", "66", "99", "CC", "FF" };

static void setup_tree_view( GtkWidget *treeview );
static void cell_data_func( GtkTreeViewColumn *column,
    GtkCellRenderer *renderer, GtkTreeModel *model,
    GtkTreeIter *iter, gpointer );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  /* create and set the main window */
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Color List" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 250, 175 );

  GtkWidget *treeview = gtk_tree_view_new();
  setup_tree_view( treeview );
  GtkListStore *store = gtk_list_store_new( COLUMNS, G_TYPE_STRING );

  /* Add all of the products to the gtkListStore */
  GtkTreeIter iter;
  int i, j, k, size = 6;
  for ( i = 0; i < size; i ++ ) {
    for ( j = 0; j < size; j++ ) {
      for ( k = 0; k < size; k++ ) {
	gchar *color_name = g_strconcat( "#", color[i], color[j], color[k],
		 NULL );
	gtk_list_store_append( store, &iter );
	gtk_list_store_set( store, &iter, COLOR, color_name, -1 );
	g_free( color_name );
      }
    }
  }

  gtk_tree_view_set_model( GTK_TREE_VIEW( treeview ), GTK_TREE_MODEL( store ) );
  g_object_unref( store );

  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scrolled_window ),
	  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ),
      NULL );

  gtk_container_add( GTK_CONTAINER( scrolled_window ), treeview );
  gtk_container_add( GTK_CONTAINER( window ), scrolled_window );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/*
 * Add three columns to the GtkTreeView. all three of the columns will be
 * displayed as text, although one is a gboolean value and another is
 * an integer
 */
static void setup_tree_view( GtkWidget *treeview ) {
  GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
	"Standard Colors", renderer, "text", COLOR, NULL );
  gtk_tree_view_append_column( GTK_TREE_VIEW( treeview ), column );
  gtk_tree_view_column_set_cell_data_func( column, renderer, 
        cell_data_func, NULL, NULL );
}

/* Cell Data function */
static void cell_data_func( GtkTreeViewColumn *column, 
	    GtkCellRenderer *renderer, GtkTreeModel *model,
	    GtkTreeIter *iter, gpointer data ) {
  gchar *text;
  /* Get the color string stored by the colun and make it the foreground color */
  gtk_tree_model_get( model, iter, COLOR, &text, -1 );
  g_object_set( renderer, "foreground", "#FFFFFF", "foreground_set", TRUE,
	"background", text, "background_set", TRUE, "text", text, NULL );
  g_free( text );
}
