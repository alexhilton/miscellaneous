/**
 * iochannelpipe.c
 * show you how to use io channel and pipe
 */
#include <gtk/gtk.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static void entry_changed( GtkEditable *editable, GIOChannel *channel );
static void setup_app( gint input[], gint output[], gint pid );
static gboolean iochannel_read( GIOChannel *channel, GIOCondition condition, GtkEntry *entry );

static gulong signal_id = 0;

int main( int argc, char **argv ) {
  gint child_to_parent[ 2 ], parent_to_child[ 2 ], pid, rc;

  /* set up read and write pipes for the child and parent processes. */
  rc = pipe( parent_to_child );
  if ( rc == -1 ) {
    //g_error( "Error: %s\n" g_strerror( errno ) );
    perror( "error: " );
    exit( EXIT_FAILURE );
  }

  rc = pipe( child_to_parent );
  if ( rc == -1 ) {
    perror( "errror" );
    exit( EXIT_FAILURE );
  }

  /* fork the application, setting up both instances accordingly */
  pid = fork();

  switch ( pid ) {
  case -1:
    g_error( "Error: %s\n", g_strerror( errno ) );
    exit( EXIT_FAILURE );
  case 0:
    /* 
     * we are in child process.
     * so we set up for child process
     */
    gtk_init( &argc, &argv );
    setup_app( parent_to_child, child_to_parent, pid );
    break;
  default:
    /*
     * we set up parent proces
     */
    gtk_init( &argc, &argv );
    setup_app( child_to_parent, parent_to_child, pid );
    break;
  }
  gtk_main();
  return 0;
}

/* set up the GUI aspects of each window and setup IO channel watches */
static void setup_app( gint input[], gint output[], gint pid ) {
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  GtkWidget *entry = gtk_entry_new();

  gtk_container_add( GTK_CONTAINER( window ), entry );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 400, 300 );
  gtk_widget_show_all( window );

  /* close the unnecessary pipes for the given process */
  close( input[ 1 ] );
  close( output[ 0 ] );

  /* create read and write channels out of the remaining pipes */
  GIOChannel *channel_read = g_io_channel_unix_new( input[ 0 ] );
  GIOChannel *channel_write = g_io_channel_unix_new( output[ 1 ] );

  if ( channel_read  == NULL || channel_write == NULL ) {
    g_error( "Error: The GIOChannels could not be created\n" );
    return;
  }

  /* watch the read channel for changes. This will send the appropriate data */
  if ( !g_io_add_watch( channel_read, G_IO_IN | G_IO_HUP, (GIOFunc) iochannel_read, (gpointer) entry ) ) {
    g_error( "errro: read watch could not be added to the GIOChannel\n" );
  }

  signal_id = g_signal_connect( G_OBJECT( entry ), 
				"changed", G_CALLBACK( entry_changed ), (gpointer) channel_write );

  /* set the window title depending on the process identifier */
  if ( pid == 0 ) {
    gtk_window_set_title( GTK_WINDOW( window ), "Child Process" );
  } else {
    gtk_window_set_title( GTK_WINDOW( window ), "Parent Process" );
  }

  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
}

/* read the message from the pipe and set the text to the GtkEntry */
static gboolean iochannel_read( GIOChannel *channel, GIOCondition condition, GtkEntry *entry ) {
  /* The pipe has died unexpectedly, so exit the application */
  if ( condition & G_IO_HUP ) {
    g_error( "error: the pipe has died\n" );
  }

  gchar *message;
  gsize length;
  /* read the data that has been sent through the pipe */
  GIOStatus rc = g_io_channel_read_line( channel, &message, &length, NULL, NULL );
  if ( rc == G_IO_STATUS_ERROR ) {
    g_error( "error: the line could not be read \n" );
  }

  /*
   * synchronize the GtkEntry text, blocking the changed signal. Otherwise, and infinite
   * loop of communication would ensure
   */
  g_signal_handler_block( (gpointer) entry, signal_id );
  message[ length-1 ] = '\0';
  gtk_entry_set_text( entry, message );
  g_signal_handler_unblock( (gpointer) entry, signal_id );

  return TRUE;
}

/* write the new contents of the GtkEntry to the write Io channel */
static void entry_changed( GtkEditable *entry, GIOChannel *channel ) {
  gchar *text = g_strconcat( gtk_entry_get_text( GTK_ENTRY( entry )), "\n", NULL );

  /* write the text to the channel so that the other process will get it */
  gsize length;
  GIOStatus rc = g_io_channel_write_chars( channel, text, -1, &length, NULL );

  if ( rc == G_IO_STATUS_ERROR ) {
    g_error( "error: the changes could not be written to the pipe\n" );
  } else {
    g_io_channel_flush( channel, NULL );
  }

}
