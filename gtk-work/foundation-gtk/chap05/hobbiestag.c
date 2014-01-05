/**
 * hobbiestag.c
 * show you how to use GtkAssistant to create a multipage dialog to instruct
 * user to do some configuration to an application, like wiszards in windows
 * Instruct the user select his hobbies and the preferred font and color to be
 * presented.
 */
#include <gtk/gtk.h>
#include <string.h>

static void done_clicked( GtkButton *button, GtkAssistant *assistant );
static void basketball_toggled( GtkCheckButton *button, GtkAssistant *assistant );
static void soccer_toggled( GtkCheckButton *button, GtkAssistant *assistant );
static void football_toggled( GtkCheckButton *button, GtkAssistant *assistant );
static void swimming_toggled( GtkCheckButton *button, GtkAssistant *assistant );
static void font_clicked( GtkFontButton *button, GtkAssistant *assistant );
static void color_clicked( GtkColorButton *button, GtkAssistant *assistant );
static void assistant_cancel( GtkAssistant *assistant, gpointer pointer );
static void assistant_close( GtkAssistant *assistant, gpointer pointer );

static gchar hobbies[ 256 ];

/* this structure contains all the infos needed for each page of assistant */
typedef struct {
  GtkWidget *widget; /* widget which you want to show to use */
  gint index; 
  const gchar *title;
  GtkAssistantPageType type;
  gboolean complete;
} PageInfo;

#define PAGE_SIZE 4 /* number of pages of asistant */

/* main program */
int main( int argc, char **argv ) {
  strcat( hobbies, "Your Favorite Hobbies\0" );
  gtk_init( &argc, &argv );

  /* initialize each page */
  PageInfo page[ PAGE_SIZE ] = {
    { NULL, -1, "Introduction", GTK_ASSISTANT_PAGE_INTRO, TRUE },
    { NULL, -1, "Select your favorite sports", GTK_ASSISTANT_PAGE_CONTENT, FALSE },
    { NULL, -1, "Set your preferences", GTK_ASSISTANT_PAGE_PROGRESS, FALSE },
    { NULL, -1, "Confirmation", GTK_ASSISTANT_PAGE_CONFIRM, TRUE },
  };

  /* create a new assistant widget with no pages */
  GtkWidget *assistant = gtk_assistant_new();
  gtk_widget_set_size_request( assistant, 450, 300 );
  gtk_window_set_title( GTK_WINDOW( assistant ), "Hobbies Presentation" );
  gtk_container_set_border_width( GTK_CONTAINER( assistant ), 10 );

  g_signal_connect( G_OBJECT( assistant ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  /* initialize widgets for each page */
  page[ 0 ].widget = gtk_label_new( "This program will present your hobbies in your\n" \
      "favorite way." );
  page[ 1 ].widget = gtk_table_new( 3, 2, TRUE ); 
  page[ 2 ].widget = gtk_vbox_new( FALSE, 10 );
  page[ 3 ].widget = gtk_label_new("");

  /* create the necessary widgets for the second page */
  GtkWidget *check_basketball = gtk_check_button_new_with_mnemonic( "_Basketball" );
  GtkWidget *check_soccer = gtk_check_button_new_with_mnemonic( "_Soccer" );
  GtkWidget *check_football = gtk_check_button_new_with_mnemonic( "_Football" );
  GtkWidget *check_swimming = gtk_check_button_new_with_mnemonic( "S_wimming" );
  GtkWidget *button_done = gtk_button_new_with_label( "Done with clicking" );
  /* add those check buttons onto table */
  gtk_table_attach( GTK_TABLE(page[1].widget), check_basketball, 0, 1, 0, 1, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE(page[1].widget), check_soccer, 1, 2, 0, 1, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE(page[1].widget), check_football, 0, 1, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE(page[1].widget), check_swimming, 1, 2, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_attach( GTK_TABLE(page[1].widget), button_done, 2, 3, 1, 2, GTK_EXPAND, GTK_SHRINK, 0, 0 );
  gtk_table_set_col_spacings( GTK_TABLE(page[1].widget), 20 );
  gtk_table_set_row_spacings( GTK_TABLE(page[1].widget), 20 );

  /* create the necessary widgets for the third page */
  GtkWidget *button_font = gtk_font_button_new();
  gtk_font_button_set_title( GTK_FONT_BUTTON( button_font ), "Chooser a font" );
  GtkWidget *button_color = gtk_color_button_new();
  gtk_color_button_set_title( GTK_COLOR_BUTTON( button_color ), "Chooser a Color" );
  /* add widgets onto page */
  gtk_box_pack_start( GTK_BOX( page[2].widget ), button_font, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( page[2].widget ), button_color, FALSE, FALSE, 10 );

  /* set data for last page */
  //g_object_set_data( G_OBJECT(page[3].widget), "label", (gpointer) page[3].widget );

  /* add  pages to assistant */
  int i;
  for ( i = 0; i < PAGE_SIZE; i++ ) {
    /* first, append page onto assistant */
    page[ i ].index = gtk_assistant_append_page( GTK_ASSISTANT( assistant ), page[i].widget );
    /* set attributes */
    gtk_assistant_set_page_title( GTK_ASSISTANT( assistant ), page[i].widget, page[i].title );
    gtk_assistant_set_page_type( GTK_ASSISTANT( assistant ), page[i].widget, page[i].type );
    gtk_assistant_set_page_complete( GTK_ASSISTANT( assistant ), page[i].widget, page[i].complete );
  }

  /*
   * set event handler for page 2 and page 4.
   * the handlers will update page2 and page 4 as complete if the pre-conditions
   * are set.
   */
  g_signal_connect( G_OBJECT( check_basketball ), "toggled", G_CALLBACK( basketball_toggled ), 
		    (gpointer) assistant );
  g_signal_connect( G_OBJECT( check_soccer ), "toggled", G_CALLBACK( soccer_toggled ), 
		    (gpointer) assistant );
  g_signal_connect( G_OBJECT( check_football ), "toggled", G_CALLBACK( football_toggled ), 
		    (gpointer) assistant );
  g_signal_connect( G_OBJECT( check_swimming ), "toggled", G_CALLBACK( swimming_toggled ), 
		    (gpointer) assistant );
  g_signal_connect( G_OBJECT( button_font ), "clicked", G_CALLBACK( font_clicked ),
		    (gpointer) assistant );
  g_signal_connect( G_OBJECT( button_color ), "clicked", G_CALLBACK( color_clicked ),
		    (gpointer) assistant );
  g_signal_connect( G_OBJECT( assistant ), "cancel", G_CALLBACK( assistant_cancel ), NULL );
  g_signal_connect( G_OBJECT( assistant ), "close", G_CALLBACK( assistant_close ), NULL );
  g_signal_connect( G_OBJECT( button_done ), "clicked", G_CALLBACK( done_clicked ), (gpointer) assistant );
  
  gtk_widget_show_all( assistant );
  gtk_main();
  return 0;
}

/* event handler for hobbies: basketball, soccer, football and swimming */
static void basketball_toggled( GtkCheckButton *button, GtkAssistant *assistant ) {
  strcat( hobbies, "\nBasketball\0" );
}

static void soccer_toggled( GtkCheckButton *button, GtkAssistant *assistant ) {
  strcat( hobbies, "\nSoccer\0" );
}

static void football_toggled( GtkCheckButton *button, GtkAssistant *assistant ) {
  strcat( hobbies, "\nFootball\0" );
}

static void swimming_toggled( GtkCheckButton *button, GtkAssistant *assistant ) {
  strcat( hobbies, "\nSwimming\0" );
}

/* event handler for color and font buttons */
static void font_clicked( GtkFontButton *button, GtkAssistant *assistant ) {
  const gchar *fontname = gtk_font_button_get_font_name( button );
  PangoFontDescription *desc = pango_font_description_from_string( fontname );

  GtkWidget *fourth_page = gtk_assistant_get_nth_page( assistant, 3 );
  gtk_widget_modify_font( fourth_page, desc );
  GtkWidget *current_page = gtk_assistant_get_nth_page( assistant, 2 );
  gtk_assistant_set_page_complete( assistant, current_page, TRUE );
}

static void color_clicked( GtkColorButton *button, GtkAssistant *assistant ) {
  GdkColor color;
  gtk_color_button_get_color( button, &color );
  GtkWidget *fourth_page = gtk_assistant_get_nth_page( assistant, 3 );
  gtk_widget_modify_bg( fourth_page, GTK_STATE_NORMAL, &color );
  GtkWidget *current_page = gtk_assistant_get_nth_page( assistant, 2 );
  gtk_assistant_set_page_complete( assistant, current_page, TRUE );
}

/* event handler for cancel button of assistant */
static void assistant_cancel( GtkAssistant *assistant, gpointer data ) {
  /*
   * If the dialog is cancelled, delete it from memory and then clean up after
   * the Assistant structure.
   */
  gtk_widget_destroy( GTK_WIDGET( assistant ) );
}

/* event handler for close operation */
static void assistant_close( GtkAssistant *assistant, gpointer data ) {
  g_print( "You would apply your changes now\n" );
  gtk_widget_destroy( GTK_WIDGET( assistant ) );
}

/* event handler for  button done */
static void done_clicked( GtkButton *button, GtkAssistant *assistant ) {
  GtkWidget *current_page = gtk_assistant_get_nth_page( assistant, 1 );
  GtkWidget *fourth_page = gtk_assistant_get_nth_page( assistant, 3 );
  gtk_label_set_text( GTK_LABEL( fourth_page ), hobbies );
  gtk_assistant_set_page_complete( assistant, current_page, TRUE );
}
