/*
 * liststore.c
 * Use GtkListStore to create a grocery list..
 * You must understand the relationships between GtkTreeModel, GtkTreeView,
 * GtkTreeViewColumn and GtkCellRenderer.
 * GtkTreeModel is used to store data, it is an interface implementated by
 * GtkListStore and GtkTreeStore.
 * GtkTreeView is used to display the data stored in a GtkTreeModel.
 * Chances are that we can have multiple representations with GtkTreeView about
 * one data--gtkTreeModel.
 * Each column(GtkTreeViewColumn) needs at least one renderer to decorate the
 * coloumns.
 */
#include <gtk/gtk.h>

enum{ BUY_IT = 0x01, QUANTITY = 0x01, PRODUCT = 0x02, COLUMNS = 0x03 };
enum { PRODUCT_CATEGORY, PRODUCT_CHILD };

typedef struct {
  gint product_type;
  gboolean buy;
  gint quantity;
  gchar *product;
} GroceryItem;

GroceryItem list[] = {
  { PRODUCT_CATEGORY, TRUE, 0, "Cleaning Supplies" },
  { PRODUCT_CHILD, TRUE, 1, "Paper Towels" },
  { PRODUCT_CHILD, TRUE, 3, "Toilet Paper" },
  { PRODUCT_CATEGORY, TRUE, 0, "Food" },
  { PRODUCT_CHILD, TRUE, 2, "Bread" },
  { PRODUCT_CHILD, FALSE, 1, "Butter" },
  { PRODUCT_CHILD, TRUE, 1, "Milk" },
  { PRODUCT_CHILD, FALSE, 3, "Chips" },
  { PRODUCT_CHILD, TRUE, 4, "Soda" },
  { PRODUCT_CATEGORY, FALSE, 0, NULL }
};

static void setup_tree_view( GtkWidget *widget );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  /* create and set properties for main window */
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Grocery List" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 480 );

  /* create and set up a tree view */
  GtkWidget *treeview = gtk_tree_view_new();
  setup_tree_view( treeview );

  /* create a new tree model with three columns, as string, gint and guint */
  GtkTreeStore *store = gtk_tree_store_new( COLUMNS, G_TYPE_BOOLEAN, 
					 G_TYPE_INT, G_TYPE_STRING );

  /* add all of the products to the GtkTreeStore */
  GtkTreeIter iter, child;
  int i = 0, j = 0;
  while ( list[i].product != NULL ) {
    /* 
     * If the product type is a category, count the quantity of all of
     * the products in the category that are going to be bought.
     */
    if ( list[ i ].product_type == PRODUCT_CATEGORY ) {
      j = i + 1;
      /* Calculate how many products will be bought in the category */
      while ( list[j].product != NULL && 
	      list[j].product_type != PRODUCT_CATEGORY ) {
	if ( list[ j ].buy ) {
	  list[ i ].quantity += list[ j ].quantity;
	}
	j++;
      }

      /* Add the category as a new root element */
      gtk_tree_store_append( store, &iter, NULL );
      gtk_tree_store_set( store, &iter, BUY_IT, list[ i ].buy,
			  QUANTITY, list[ i ].quantity,
			  PRODUCT, list[ i ].product, -1 );
    } else {
      /* Otherwise, add the product as a child of the category */
      gtk_tree_store_append( store, &child, &iter );
      gtk_tree_store_set( store, &child, BUY_IT, list[ i ].buy,
			  QUANTITY, list[ i ].quantity,
			  PRODUCT, list[ i ].product, -1 );
    }
    i++;
  }

  /* 
   * Add the tree model to the tree view and unreference it so that the
   * model will be destroyed along with the tree view 
   */
  gtk_tree_view_set_model( GTK_TREE_VIEW( treeview ), GTK_TREE_MODEL( store ) );
  gtk_tree_view_expand_all( GTK_TREE_VIEW( treeview ) );
  g_object_unref( store );

  GtkWidget *scrolled_window = gtk_scrolled_window_new( NULL, NULL );
  gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scrolled_window ),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );

  g_signal_connect( G_OBJECT( window ), "destroy",
		    G_CALLBACK( gtk_main_quit ), NULL );
  gtk_container_add( GTK_CONTAINER( scrolled_window ), treeview );
  gtk_container_add( GTK_CONTAINER( window ), scrolled_window );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/*
 * Add three columns to the GtkTextView. All three of the columns will
 * be displayed as text, although one is a boolean value and another is
 * an integer.
 */
static void setup_tree_view( GtkWidget *treeview ) {
  /* 
   * Create a new GtkCellRenderText, add it to the tree view column
   * and append the column to the tree view 
   */
  GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
      "Buy", renderer, "text", BUY_IT, NULL );
  gtk_tree_view_append_column( GTK_TREE_VIEW( treeview ), column );

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(
      "Count", renderer, "text", QUANTITY, NULL );
  gtk_tree_view_append_column( GTK_TREE_VIEW( treeview ), column );
  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(
        "Product", renderer, "text", PRODUCT, NULL );
  gtk_tree_view_append_column( GTK_TREE_VIEW( treeview ), column );
}
