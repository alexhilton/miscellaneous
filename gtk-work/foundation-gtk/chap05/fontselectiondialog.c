/**
 * fontselectiondialog.c
 * show you how to use font selectiondialg
 * and this dialog is a top level window.
 * with response handle for it.
 */
#include <gtk/gtk.h>

static void font_dialog_response( GtkFontSelectionDialog *dialog, gint result, gpointer data );

int main( int argc, char **argv ) {
  gtk_init( &argc,&argv );

  /* use the font selection dialog as teh toplevel widget */
  GtkWidget *dialog = gtk_font_selection_dialog_new( "Choose a Font" );
  gtk_font_selection_dialog_set_font_name( GTK_FONT_SELECTION_DIALOG( dialog ), "Sans Bold Italic 12" );
  gtk_font_selection_dialog_set_preview_text( GTK_FONT_SELECTION_DIALOG( dialog ), "Alex Hilton" );

  /* connnect response handler to dialog */
  g_signal_connect( G_OBJECT( dialog ), "response", G_CALLBACK( font_dialog_response ), NULL );
  g_signal_connect( G_OBJECT( dialog ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

  gtk_widget_show_all( dialog );
  gtk_main();
  return 0;
}

/* handle response for dialog */
/*
 * If the user clicks "Apply", display the font but do not destroy the dialog.
 * If "OK" is clicked, display the font and destory the dialog. Otherwise, just
 * destroy the dialog.
 */
static void font_dialog_response( GtkFontSelectionDialog *dialog, gint result, gpointer data ) {
  gchar *font;
  GtkWidget *msg;

  switch ( result ) {
  case GTK_RESPONSE_APPLY:
  case GTK_RESPONSE_OK:
    /* retrieve the font */
    font = gtk_font_selection_dialog_get_font_name( dialog );
    /* create a new message dialog, to show user the new font selected */
    msg = gtk_message_dialog_new( NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
				  GTK_BUTTONS_OK, font );
    gtk_window_set_title( GTK_WINDOW( msg ), "Selected font" );
    gtk_dialog_run( GTK_DIALOG( msg ) );
    gtk_widget_destroy( msg );
    g_free( font );
    break;
  default:
    gtk_widget_destroy( GTK_WIDGET( dialog ) );
  }

  if ( result == GTK_RESPONSE_OK ) {
    gtk_widget_destroy( GTK_WIDGET( dialog ) );
  }
}
