/*
 * hellotree.c
 * create a hello world application with Gtktreeview
 */
#include <gtk/gtk.h>

enum { COL_NAME = 0, COL_AGE, NUM_COLS };

static GtkTreeModel *create_and_fill_model( void ) {
  GtkListStore *store;
  GtkTreeIter iter;
  store = gtk_list_store_new( NUM_COLS, G_TYPE_STRING, G_TYPE_UINT );

  /* append a row and fill in some data */
  gtk_list_store_append( store, &iter );
  gtk_list_store_set( store, &iter, COL_NAME, "Alex Hilton",
		      COL_AGE, 6, -1 );

  /* append another row and fill in some data */
  gtk_list_store_append( store, &iter );
  gtk_list_store_set( store, &iter, COL_NAME, "Kevin Garnett",
			 COL_AGE, 23, -1 );

  /* and another */
  gtk_list_store_append( store, &iter );
  gtk_list_store_set( store, &iter, COL_NAME, "Kobe Bryant",
			 COL_AGE, 25, -1 );
  return GTK_TREE_MODEL( store );
}

static GtkWidget *create_view_and_model( void ) {
  GtkCellRenderer *renderer;
  GtkTreeModel *model;
  GtkWidget *view;

  view = gtk_tree_view_new();

  /* ----column #1 ---- */
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes( GTK_TREE_VIEW( view ),
     -1, "Name", renderer, "text", COL_NAME, NULL );

  /* ----Column #2 -----*/
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes( GTK_TREE_VIEW( view ),
     -1, "Age", renderer, "text", COL_AGE, NULL );

  model = create_and_fill_model();
  gtk_tree_view_set_model( GTK_TREE_VIEW( view ), GTK_TREE_MODEL( model ) );

  /*
   * The tree view has acquired its own references to the model, so
   * we can drop ours. That way the model will be freed automatically
   * when the tree view is destroyed 
   * This is sort of same to Garbage Collection of Java.
   * When the references about an object reache zero, it is the time to 
   * collect that object.
   * So here, if you don't release your reference, it will never be
   * released by GTK, even when tree view is destroyed.
   */
  g_object_unref( model );
  return view;
}

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  g_signal_connect( G_OBJECT( window ), "destroy",
		    G_CALLBACK( gtk_main_quit ), NULL );

  GtkWidget *view = create_view_and_model();
  gtk_container_add( GTK_CONTAINER( window ), view );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
