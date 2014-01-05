/**
 * assistant.c
 * show you how to use GtkAssistant to create a multipage dialog to instruct
 * user to do some configuration to an application, like wiszards in windows
 */
#include <gtk/gtk.h>
#include <string.h>

static void entry_changed( GtkEditable *editable, GtkAssistant *assistant );
static void button_toggled( GtkCheckButton *button, GtkAssistant *assistant );
static void button_clicked( GtkButton *button, GtkAssistant *assistant );
static void assistant_cancel( GtkAssistant *assistant, gpointer pointer );
static void assistant_close( GtkAssistant *assistant, gpointer pointer );

/* this structure contains all the infos needed for each page of assistant */
typedef struct {
  GtkWidget *widget; /* widget which you want to show to use */
  gint index; 
  const gchar *title;
  GtkAssistantPageType type;
  gboolean complete;
} PageInfo;

#define PAGE_SIZE 5 /* number of pages of asistant */

/* main program */
int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  /* initialize each page */
  PageInfo page[ PAGE_SIZE ] = {
    { NULL, -1, "Introduction", GTK_ASSISTANT_PAGE_INTRO, TRUE },
    { NULL, -1, NULL, GTK_ASSISTANT_PAGE_CONTENT, FALSE },
    { NULL, -1, "Click the Check Button", GTK_ASSISTANT_PAGE_CONTENT, FALSE },
    { NULL, -1, "Click the Button", GTK_ASSISTANT_PAGE_PROGRESS, FALSE },
    { NULL, -1, "Confirmation", GTK_ASSISTANT_PAGE_CONFIRM, TRUE },
  };

  /* create a new assistant widget with no pages */
  GtkWidget *assistant = gtk_assistant_new();
  gtk_widget_set_size_request( assistant, 450, 300 );
  gtk_window_set_title( GTK_WINDOW( assistant ), "Assistant implements multiple page dialog" );
  gtk_container_set_border_width( GTK_CONTAINER( assistant ), 10 );

  g_signal_connect( G_OBJECT( assistant ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  /* initialize widgets for each page */
  page[ 0 ].widget = gtk_label_new( "This is an example of a GtkAssistant. By\n" \
				    "clicking the forward button, you can continue\n" \
				    "to the next section, Good Luck, man!" );
  page[ 1 ].widget = gtk_hbox_new( FALSE, 5 );
  page[ 2 ].widget = gtk_check_button_new_with_label( "Click me to coninue" );
  page[ 3 ].widget = gtk_alignment_new( 0.5f, .5f, .0f, .0f );
  page[ 4 ].widget = gtk_label_new( "Text has been entered in the label and the\n" \
				    "combo box is clicked. If you are done, then\n" \
				    "it is time to leave!" );

  /* create the necessary widgets for the second page */
  GtkWidget *label = gtk_label_new( "Your name: " );
  GtkWidget *entry = gtk_entry_new();
  gtk_box_pack_start( GTK_BOX( page[1].widget ), label, FALSE, FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( page[1].widget ), entry, FALSE, FALSE, 5 );

  /*
   * create the necessary widgets for the fourth page. The, attach the progress bar
   * to the GtkAlignment widget for later access
   */
  GtkWidget *button = gtk_button_new_with_label( "click me!" );
  GtkWidget *progress = gtk_progress_bar_new();
  GtkWidget *hbox = gtk_hbox_new( FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( hbox ), progress, TRUE, FALSE, 5 );
  gtk_box_pack_start( GTK_BOX( hbox ), button, FALSE, FALSE, 5 );
  gtk_container_add( GTK_CONTAINER( page[3].widget ), hbox );
  g_object_set_data( G_OBJECT( page[3].widget ), "pbar", (gpointer) progress );

  /* add five pages to assistant */
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

  g_signal_connect( G_OBJECT( entry ), "changed", G_CALLBACK( entry_changed ), (gpointer) assistant );
  g_signal_connect( G_OBJECT( page[2].widget ), "toggled", G_CALLBACK( button_toggled ), 
		    (gpointer) assistant );
  g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( button_clicked ),
		    (gpointer) assistant );
  g_signal_connect( G_OBJECT( assistant ), "cancel", G_CALLBACK( assistant_cancel ), NULL );
  g_signal_connect( G_OBJECT( assistant ), "close", G_CALLBACK( assistant_close ), NULL );

  gtk_widget_show_all( assistant );
  gtk_main();
  return 0;
}

/* event handler for entry text of page 2 */
static void entry_changed( GtkEditable *editable, GtkAssistant *assistant ) {
  /* 
   * if there is text in the GtkEntry, set the page as complete. Otherwise,
   * stop the user from pregressing the next page 
   */
  const char *text = gtk_entry_get_text( GTK_ENTRY( editable ) );
  int current_page = gtk_assistant_get_current_page( assistant );
  GtkWidget *this_page = gtk_assistant_get_nth_page( assistant, current_page );
  gtk_assistant_set_page_complete( assistant, this_page, (strlen(text) > 0) );
}

/* event handler for check button of page 3 */
static void button_toggled( GtkCheckButton *toggle, GtkAssistant *assistant ) {
  /*
   * if the check button is toggled, set the page as complete.
   * Othewise, stop user from progressing the next page
   */ 
  gboolean active = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( toggle ) );
  gtk_assistant_set_page_complete( assistant, GTK_WIDGET( toggle ), active );
}

/* event handler for page 4, most important part of this program, a new guy: progressbar comes */
static void button_clicked( GtkButton *button, GtkAssistant *assistant ) {
  /* 
   * Fill up the progress bar, 10% every second when the button is clicked.
   * Then set the page as complete when the progress bar is filled
   */
  /* first, deactive the button */
  gtk_widget_set_sensitive( GTK_WIDGET( button ), FALSE );
  GtkWidget *current_page = gtk_assistant_get_nth_page( assistant, 3 );
  GtkProgressBar *progressbar = GTK_PROGRESS_BAR( g_object_get_data( G_OBJECT(current_page), "pbar" ) );

  gdouble percent = 0.f;
  while ( percent <= 100.f ) {
    gchar *msg = g_strdup_printf( "%.0f%% Complete", percent );
    gtk_progress_bar_set_fraction( progressbar, percent / 100.f );
    gtk_progress_bar_set_text( progressbar, msg );

    while ( gtk_events_pending() ) {
      gtk_main_iteration();
    }

    g_usleep( 500000 );
    percent += 5.f;
  }

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
