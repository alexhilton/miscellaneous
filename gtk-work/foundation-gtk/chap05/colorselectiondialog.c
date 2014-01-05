/**
 * colorselectiondialog.c
 * show you hwo to use color selection dialog.
 * how to catch response signal of dialog and write handle for it.
 */
#include <gtk/gtk.h>

static void run_color_selection_dialog( GtkButton *button, GtkWindow *window, gboolean modal );
static void modal_clicked( GtkButton *button, GtkWindow *window );
static void nonmodal_clicked( GtkButton *button, GtkWindow *window );
static void dialog_response( GtkDialog *dialog, gint result, gpointer pointer );

static GdkColor global_color;
static guint global_alpha = 65535;

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );

  /*
   * Loop through the command line arguments. The first color name that is specified
   * and successfully parsed, it will be used as the initial color of the dialog
   */
  while ( --argc > 0 ) {
    if ( gdk_color_parse( *++argv, &global_color ) ) {
      break;
    }
  }

  /* create and set main window */
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Color Selection Dialog" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 320, 240 );

  /* create two buttons and connect signal to them, one is for modal dialog, the other is for non-modal */
  GtkWidget *modal = gtk_button_new_with_mnemonic( "_Modal" );
  GtkWidget *nonmodal = gtk_button_new_with_mnemonic( "_Nonmodal" );
  g_signal_connect( G_OBJECT( modal ), "clicked", G_CALLBACK( modal_clicked ), (gpointer) window );
  g_signal_connect( G_OBJECT( nonmodal ), "clicked", G_CALLBACK( nonmodal_clicked ), (gpointer) window );

  /* connect destroy signal for window */
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
  /* organize all those widgets onto window and show them */
  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), modal, FALSE, FALSE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), nonmodal, FALSE, FALSE, 10 );
  gtk_container_add( GTK_CONTAINER( window ), vbox );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/* write click event handle for both buttons */
static void modal_clicked( GtkButton *button, GtkWindow *window ) {
  run_color_selection_dialog( button, window, TRUE );
}

/* write click event handle for nonmodal */
static void nonmodal_clicked( GtkButton *button, GtkWindow *window ) {
  run_color_selection_dialog( button, window, FALSE );
}

/* here is the real one: create a color selection dialog */
static void run_color_selection_dialog( GtkButton *button, GtkWindow *window, gboolean domodal ) {
  char *title;
  if ( domodal ) {
    title = "Chooser color -- modal";
  } else {
    title = "chooser color -- non-modal";
  }

  GtkWidget *dialog = gtk_color_selection_dialog_new( title );
  gtk_window_set_modal( GTK_WINDOW( dialog ), domodal );

  /* get color selection widget from structure dialog */
  GtkWidget *colorsel = GTK_COLOR_SELECTION_DIALOG( dialog )->colorsel;
  gtk_color_selection_set_has_opacity_control( GTK_COLOR_SELECTION( colorsel ), TRUE );

  /* initialize the fields of structure color dialog */
  gtk_color_selection_set_current_color( GTK_COLOR_SELECTION( colorsel ), &global_color );
  gtk_color_selection_set_current_alpha( GTK_COLOR_SELECTION( colorsel ), global_alpha );

  /* connect signal response to its handler */
  g_signal_connect( G_OBJECT( dialog ), "response", G_CALLBACK( dialog_response ), NULL );
  gtk_widget_show_all( dialog );
}

/* write response handler for dialog */
static void dialog_response( GtkDialog *dialog, gint result, gpointer data ) {
  GdkColor color = { 0, };
  guint16 alpha = 0;
  GtkWidget *colorsel;

  /* do different actions according to result of dialog */
  switch ( result ) {
  case GTK_RESPONSE_HELP:
    g_print( "Read the GTK+ API deocumentation.\n" );
    break;
  case GTK_RESPONSE_OK:
    colorsel = GTK_COLOR_SELECTION_DIALOG( dialog )->colorsel;
    alpha = gtk_color_selection_get_current_alpha( GTK_COLOR_SELECTION( colorsel ) );
    gtk_color_selection_get_current_color( GTK_COLOR_SELECTION( colorsel ), &color );

    g_print( "#0x%04x%04x%04x%04x\n", color.red, color.green, color.blue, alpha );
    global_alpha = alpha;
    global_color = color;
  default:
    gtk_widget_destroy( GTK_WIDGET( dialog ) );
  }
}
