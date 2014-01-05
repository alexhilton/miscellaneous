/**
 * aboutdialog.c
 * how to use and create an about dialog.
 */
#include <gtk/gtk.h>

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  const gchar *authors[] = {
    "Author #1",
    "Author #2",
    NULL,
  };
  const gchar *docs[] = {
    "Doc #1",
    "Doc #2", 
    NULL,
  };
  GtkWidget *dialog = gtk_about_dialog_new();
  GError *error = NULL;
  GdkPixbuf *logo = gdk_pixbuf_new_from_file( "/home/alex/work/gtk-work/foundation-gtk/chap05/logo.png", &error );

  /* set the application logo or handle the errors */
  if ( error == NULL ) { /* no error, set the logo */
    gtk_about_dialog_set_logo( GTK_ABOUT_DIALOG( dialog ), logo );
  } else {
    if ( error->domain == GDK_PIXBUF_ERROR ) {
      g_print( "GdkPixbufError: %s\n", error->message );
    } else if ( error->domain == G_FILE_ERROR ) {
      g_print( "GFileError: %s\n", error->message );
    } else {
      g_print( "An Error in the domain: %d has occured!\n", error->domain );
    }
    g_error_free( error );
  }

  /* set application data that will be displayed in the main dialog */
  gtk_about_dialog_set_name( GTK_ABOUT_DIALOG( dialog ), "NEFW" );
  gtk_about_dialog_set_version( GTK_ABOUT_DIALOG( dialog ), "3.2.0.02" );
  gtk_about_dialog_set_copyright( GTK_ABOUT_DIALOG( dialog ), "(c) 2009 Alex Hilton" );
  gtk_about_dialog_set_comments( GTK_ABOUT_DIALOG( dialog ), "All about dialog" );

  /* set licese tex */
  gtk_about_dialog_set_license( GTK_ABOUT_DIALOG( dialog ), "Free to everyone" );
  gtk_about_dialog_set_website( GTK_ABOUT_DIALOG( dialog ), "http://book.alexhilton.net" );
  gtk_about_dialog_set_website_label( GTK_ABOUT_DIALOG( dialog ), "book.alexhilton.net" );

  /* set the application authors, docs and translators */
  gtk_about_dialog_set_authors( GTK_ABOUT_DIALOG( dialog ), authors );
  gtk_about_dialog_set_documenters( GTK_ABOUT_DIALOG( dialog ), docs );
  gtk_about_dialog_set_translator_credits( GTK_ABOUT_DIALOG( dialog ), "tran #1\nTran #2" );

  gtk_dialog_run( GTK_DIALOG( dialog ) );
  gtk_widget_destroy( dialog );
  return 0;
}
