/*
 * addremoverows.c
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
 * Add or remove rows or columns.
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
static void add_clicked( GtkButton *add, GtkTreeView *treeview );
static void remove_row( GtkTreeRowReference *ref, GtkTreeModel *model );
static void remove_clicked( GtkButton *add, GtkTreeView *treeview );

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
  /* Create Add and remove buttons */
  GtkWidget *add = gtk_button_new_from_stock( GTK_STOCK_ADD );
  GtkWidget *remove = gtk_button_new_from_stock( GTK_STOCK_REMOVE );
  g_signal_connect( G_OBJECT( add ), "clicked", G_CALLBACK( add_clicked ),
      (gpointer) treeview );
  g_signal_connect( G_OBJECT( remove ), "clicked", 
      G_CALLBACK( remove_clicked ), (gpointer) treeview );
  g_signal_connect( G_OBJECT( window ), "destroy",
		    G_CALLBACK( gtk_main_quit ), NULL );
  GtkWidget *hbox = gtk_hbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( hbox ), add, FALSE, TRUE, 10 );
  gtk_box_pack_start( GTK_BOX( hbox ), remove, FALSE, TRUE, 10 );
  GtkWidget *vbox = gtk_vbox_new( FALSE, 5 );
  gtk_container_add( GTK_CONTAINER( scrolled_window ), treeview );
  gtk_box_pack_start( GTK_BOX( vbox ), scrolled_window, TRUE, TRUE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), hbox, FALSE, FALSE, 10 );
  gtk_container_add( GTK_CONTAINER( window ), vbox );
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

/*
 * Used to add product for treeview.
 */
static void add_clicked( GtkButton *add, GtkTreeView *treeview ) {
  /* create a dialog that will be used to create a new product */
  GtkWidget *dialog = gtk_dialog_new_with_buttons(
      "Add a Product", NULL, GTK_DIALOG_MODAL, GTK_STOCK_ADD, GTK_RESPONSE_OK, 
      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL );

  /* create a combo box that will be packed into the dialog */
  GtkWidget *combobox = gtk_combo_box_new_text();
  GtkWidget *entry = gtk_entry_new();
  GtkWidget *spin = gtk_spin_button_new_with_range( 0, 100, 1 );
  GtkWidget *check = gtk_check_button_new_with_mnemonic( "_Buy the product" );
  gtk_spin_button_set_digits( GTK_SPIN_BUTTON( spin ), 0 );

  /* Add all the categories to the combo box */
  gint i = 0;
  while ( list[ i ].product != NULL ) {
    if ( list[i].product_type == PRODUCT_CATEGORY ) {
      gtk_combo_box_append_text( GTK_COMBO_BOX( combobox ), list[i].product );
    }
    i++;
  }

  GtkWidget *table = gtk_table_new( 4, 2, FALSE );
  gtk_table_set_row_spacings( GTK_TABLE( table ), 5 );
  gtk_table_set_col_spacings( GTK_TABLE( table ), 5 );
  gtk_container_set_border_width( GTK_CONTAINER( table ), 5 );

  /* packing the table that will hold the dialog widgets */
  gtk_table_attach( GTK_TABLE( table ), gtk_label_new( "Category: " ),
        0, 1, 0, 1, GTK_SHRINK | GTK_FILL,
        GTK_SHRINK | GTK_FILL, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), combobox, 1, 2, 0, 1,
	GTK_EXPAND | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), gtk_label_new( "Product: " ),
        0, 1, 1, 2, GTK_SHRINK | GTK_FILL,
	GTK_SHRINK | GTK_FILL, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), entry, 1, 2, 1, 2,
        GTK_EXPAND | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), gtk_label_new( "Quantity: " ),
	0, 1, 2, 3, GTK_SHRINK | GTK_FILL,
        GTK_SHRINK | GTK_FILL, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), spin, 1, 2, 2, 3, 
	GTK_EXPAND | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0 );
  gtk_table_attach( GTK_TABLE( table ), check, 1, 2, 3, 4,
	GTK_EXPAND | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0 );

  gtk_box_pack_start_defaults( GTK_BOX( GTK_DIALOG(dialog)->vbox ), table );
  gtk_widget_show_all( dialog );

  gint quantity;
  const gchar *product;
  gchar *category, *name;
  gboolean buy;
  GtkTreeIter iter, child;
  GtkTreePath *path;
  GtkTreeModel *model;
  /* If the user presses OK, verify the entries and add the product */
  if ( gtk_dialog_run( GTK_DIALOG( dialog ) ) == GTK_RESPONSE_OK ) {
    quantity = (gint) gtk_spin_button_get_value( GTK_SPIN_BUTTON( spin ) );
    product = gtk_entry_get_text( GTK_ENTRY( entry ) );
    category = gtk_combo_box_get_active_text( GTK_COMBO_BOX( combobox ) );
    buy = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( check ) );

    if ( g_ascii_strcasecmp( product, "" ) == 0 || category == NULL ) {
      g_warning( "All of the fields were not correctly filled out!" );
      gtk_widget_destroy( dialog );

      if ( category != NULL ) {
	g_free( category );
      }
      return;
    }

    model = gtk_tree_view_get_model( treeview );
    gtk_tree_model_get_iter_from_string( model, &iter, "0" );

    /* Retrieve an iterator pointing to the selected category */
    do {
      gtk_tree_model_get( model, &iter, PRODUCT, &name, -1 );
      if ( g_ascii_strcasecmp( name, category ) == 0 ) {
	g_free( name );
	break;
      }
      g_free( name );
    } while ( gtk_tree_model_iter_next( model, &iter ) );

    /*
     * Convert the category iterator to a path so taht it will not become
     * invalid and add the new product as a child of the category
     */
    path = gtk_tree_model_get_path( model, &iter );
    gtk_tree_store_append( GTK_TREE_STORE( model ), &child, &iter );
    gtk_tree_store_set( GTK_TREE_STORE( model ), &child, BUY_IT, buy,
	 QUANTITY, quantity, PRODUCT, product, -1 );

    /* Add the quantity to the running total if it is to be purchased */
    if ( buy ) {
      gtk_tree_model_get_iter( model, &iter, path );
      gtk_tree_model_get( model, &iter, QUANTITY, &i, -1 );
      i += quantity;
      gtk_tree_store_set( GTK_TREE_STORE( model ), &iter, QUANTITY, i, -1 );
    }
    gtk_tree_path_free( path );
    g_free( category );
  }

  gtk_widget_destroy( dialog );
}

/*
 * Remove rows
 */
static void remove_row( GtkTreeRowReference *ref, GtkTreeModel *model ) {
  GtkTreeIter parent, iter;
  GtkTreePath *path;
  gboolean buy;
  gint quantity, pnum;
  path = gtk_tree_row_reference_get_path( ref );
  gtk_tree_model_get_iter( model, &iter, path );

  /* Only remove the row if it is not a root row */
  if ( gtk_tree_model_iter_parent( model, &parent, &iter ) ) {
    gtk_tree_model_get( model, &iter, BUY_IT, &buy, QUANTITY, &quantity, -1 );
    gtk_tree_model_get( model, &parent, QUANTITY, &pnum, -1 );

    if ( buy ) {
      pnum -= quantity;
      gtk_tree_store_set( GTK_TREE_STORE( model ), &parent, quantity, pnum, -1 );
    }

    gtk_tree_model_get_iter( model, &iter, path );
    gtk_tree_store_remove( GTK_TREE_STORE( model ), &iter );
  }
}

/*
 * remove products
 */
static void remove_clicked( GtkButton *remove, GtkTreeView *treeview ) {
  GtkTreeSelection *selection = gtk_tree_view_get_selection( treeview );
  GtkTreeModel *model = gtk_tree_view_get_model( treeview );
  GList *rows = gtk_tree_selection_get_selected_rows( selection, &model );

  /* Create tree row references to all of the selected rows */
  GList *ptr = rows;
  GtkTreeRowReference *ref;
  GList *references = NULL;
  while ( ptr != NULL ) {
    ref = gtk_tree_row_reference_new( model, (GtkTreePath *) ptr->data );
    references = g_list_prepend( references, gtk_tree_row_reference_copy( ref ) );
    gtk_tree_row_reference_free( ref );
    ptr = ptr->next;
  }

  /* Remove each of the selected rows pointed to by the row reference */
  g_list_foreach( references, (GFunc) remove_row, model );

  /* Free the tree paths, tree row references and lists */
  g_list_foreach( references, (GFunc) gtk_tree_row_reference_free, NULL );
  g_list_foreach( rows, (GFunc) gtk_tree_path_free, NULL );
  g_list_free( references );
  g_list_free( rows );
}
