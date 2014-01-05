/**
 * infodialog.c
 * create a information dialog about current user.
 * there is no window, only a dialog *
 */
#include <gtk/gtk.h>
#include <stdio.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *dialog = gtk_dialog_new_with_buttons( "Edit User Information", NULL,
						   GTK_DIALOG_MODAL, 
						   GTK_STOCK_OK, GTK_RESPONSE_OK,
						   GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL );
  gtk_dialog_set_default_response( GTK_DIALOG( dialog ), GTK_RESPONSE_OK );

  /* create four labels that let user know what to edit */
  GtkWidget *usernamelabel = gtk_label_new( "User Name:" );
  GtkWidget *realnamelabel = gtk_label_new( "Real Name:" );
  GtkWidget *homedirlabel = gtk_label_new( "Home Dir:" );
  GtkWidget *hostnamelabel = gtk_label_new( "Host Name:" );

  /* create four entries that let user to edit info */
  GtkWidget *usernameentry = gtk_entry_new();
  GtkWidget *realnameentry = gtk_entry_new();
  GtkWidget *homedirentry = gtk_entry_new();
  GtkWidget *hostnameentry = gtk_entry_new();

  /* retrieve the user's information for the default values */
  gtk_entry_set_text( GTK_ENTRY( usernameentry ), g_get_user_name() );
  gtk_entry_set_text( GTK_ENTRY( realnameentry ), g_get_real_name() );
  gtk_entry_set_text( GTK_ENTRY( homedirentry ), g_get_home_dir() );
  gtk_entry_set_text( GTK_ENTRY( hostnameentry ), g_get_host_name() );

  /* use a table to organize all those widgets */
  GtkWidget *table = gtk_table_new( 4, 2, FALSE );
  gtk_table_attach_defaults( GTK_TABLE( table ), usernamelabel, 0, 1, 0, 1 );
  gtk_table_attach_defaults( GTK_TABLE( table ), realnamelabel, 0, 1, 1, 2 );
  gtk_table_attach_defaults( GTK_TABLE( table ), homedirlabel, 0, 1, 2, 3 );
  gtk_table_attach_defaults( GTK_TABLE( table ), hostnamelabel, 0, 1, 3, 4 );
  gtk_table_attach_defaults( GTK_TABLE( table ), usernameentry, 1, 2, 0, 1 );
  gtk_table_attach_defaults( GTK_TABLE( table ), realnameentry, 1, 2, 1, 2 );
  gtk_table_attach_defaults( GTK_TABLE( table ), homedirentry, 1, 2, 2, 3 );
  gtk_table_attach_defaults( GTK_TABLE( table ), hostnameentry, 1, 2, 3, 4 );

  gtk_table_set_row_spacings( GTK_TABLE( table ), 5 );
  gtk_table_set_col_spacings( GTK_TABLE( table ), 5 );
  gtk_container_set_border_width( GTK_CONTAINER( table ), 10 );

  gtk_box_pack_start_defaults( GTK_BOX( GTK_DIALOG(dialog)->vbox ), table );
  gtk_widget_show_all( dialog );

  /* run the dialog and output the data if the user clicks the OK button */
  gint result = gtk_dialog_run( GTK_DIALOG( dialog ) );
  if ( result == GTK_RESPONSE_OK ) {
    printf( "User name: %s\n", gtk_entry_get_text( GTK_ENTRY( usernameentry ) ) );
    printf( "Real name: %s\n", gtk_entry_get_text( GTK_ENTRY( realnameentry ) ) );
    printf( "Home Dir: %s\n", gtk_entry_get_text( GTK_ENTRY( homedirentry ) ) );
    printf( "Host name: %s\n", gtk_entry_get_text( GTK_ENTRY( hostnameentry ) ) );
  } else if ( result == GTK_RESPONSE_CANCEL ) {
    printf( "you have been pressed 'Cancel'\n" );
  }

  gtk_widget_destroy( dialog );
  return 0;
}
