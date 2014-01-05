/*
 * show you how to create a pop up menu
 * GTK+ has so much alike to Java.
 * Creating menu is pretty easy: you create a menu widget, then create many menu
 * items and add them to menu. Then you have to add event handlers for those
 * menu items.
 */
#include <gtk/gtk.h>

static void create_popup_menu( GtkWidget *, GtkWidget *, GtkWidget * );
static void pulse_activated( GtkMenuItem *, GtkProgressBar * );
static void clear_activated( GtkMenuItem *, GtkProgressBar * );
static void fill_activated( GtkMenuItem *, GtkProgressBar * );
static gboolean button_press_event( GtkWidget *, GdkEventButton *,
    GtkWidget * );
static gboolean statusbar_hint( GtkMenuItem *menuItem,
    GdkEventProximity *event, GtkStatusbar *statusbar );

int main( int argc, char **argv ) {
  gtk_init( &argc, &argv );
  GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title( GTK_WINDOW( window ), "Pop up menus" );
  gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
  gtk_widget_set_size_request( window, 550, 160 );

  /* create all necessary widgets and initialize the popup menu */
  GtkWidget *menu = gtk_menu_new();
  GtkWidget *eventbox = gtk_event_box_new();
  GtkWidget *progress = gtk_progress_bar_new();
  gtk_progress_bar_set_text( GTK_PROGRESS_BAR( progress ), 
      "Nothing yet happened" );
  GtkWidget *statusbar = gtk_statusbar_new();
  create_popup_menu( menu, progress, statusbar );

  gtk_progress_bar_set_pulse_step( GTK_PROGRESS_BAR( progress ), 0.05 );
  gtk_event_box_set_above_child( GTK_EVENT_BOX( eventbox ), FALSE );

  g_signal_connect( G_OBJECT( eventbox ), "button_press_event",
      G_CALLBACK( button_press_event ), menu );
  g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ),
       NULL );
  gtk_container_add( GTK_CONTAINER( eventbox ), progress );
  GtkWidget *vbox = gtk_vbox_new( TRUE, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), eventbox, TRUE, TRUE, 10 );
  gtk_box_pack_start( GTK_BOX( vbox ), statusbar, TRUE, TRUE, 10 );
  gtk_container_add( GTK_CONTAINER( window ), vbox );

  gtk_widget_set_events( eventbox, GDK_BUTTON_PRESS_MASK );
  gtk_widget_realize( eventbox );

  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}

/*
 * craete the pop up menu and attach it to the progress bar. This
 * will make sure that the accelerators will work from application
 * load
 */
static void create_popup_menu( GtkWidget *menu, GtkWidget *progress, GtkWidget *statusbar ) {
  GtkWidget *pulse = gtk_menu_item_new_with_label( "Pulse Progress" );
  GtkWidget *fill = gtk_menu_item_new_with_label( "Set as Complete" );
  GtkWidget *clear = gtk_menu_item_new_with_label( "Clear Progress" );
  GtkWidget *separator = gtk_separator_menu_item_new();

  g_signal_connect( G_OBJECT( pulse ), "activate", G_CALLBACK( pulse_activated ),
      progress );
  g_signal_connect( G_OBJECT( fill ), "activate", G_CALLBACK( fill_activated ),
      progress );
  g_signal_connect( G_OBJECT( clear ), "activate", G_CALLBACK( clear_activated ),
      progress );

  /* connect signals to each menu item for status bar messages */
  g_signal_connect( G_OBJECT( pulse ), "enter_notify_event", 
      G_CALLBACK( statusbar_hint ), statusbar );
  g_signal_connect( G_OBJECT( pulse ), "leave_notify_event",
      G_CALLBACK( statusbar_hint ), statusbar );
  g_signal_connect( G_OBJECT( fill ), "enter_notify_event",
      G_CALLBACK( statusbar_hint ), statusbar );
  g_signal_connect( G_OBJECT( fill ), "leave_notify_event",
      G_CALLBACK( statusbar_hint ), statusbar );
  g_signal_connect( G_OBJECT( clear ), "enter_notify_event",
      G_CALLBACK( statusbar_hint ), statusbar );
  g_signal_connect( G_OBJECT( clear ), "leave_notify_event",
      G_CALLBACK( statusbar_hint ), statusbar );
  g_object_set_data( G_OBJECT( pulse ), "menuhint",
      (gpointer) "Pulse the progress bar one step." );
  g_object_set_data( G_OBJECT( fill ), "menuhint",
      (gpointer) "Set the progress bar to 100%." );
  g_object_set_data( G_OBJECT( clear ), "menuhint",
      (gpointer) "Clear the progress bar to 0%." );

  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), pulse );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), separator );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), fill );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), clear );

  gtk_menu_attach_to_widget( GTK_MENU( menu ), progress, NULL );
  gtk_widget_show_all( menu );
}

/*
 * No matter what, this design sucks
 */
static gboolean button_press_event( GtkWidget *eventbox, GdkEventButton *event,
    GtkWidget *menu ) {
  if ( ( event->button == 3 ) && (event->type == GDK_BUTTON_PRESS ) ) {
    gtk_menu_popup( GTK_MENU( menu ), NULL, NULL, NULL, NULL,
        event->button, event->time );
    return TRUE;
  }
  return FALSE;
}

static void pulse_activated( GtkMenuItem *item, GtkProgressBar *progress ) {
  gtk_progress_bar_pulse( progress );
  gtk_progress_bar_set_text( progress, "Pulse" );
}

static void fill_activated( GtkMenuItem *item, GtkProgressBar *progress ) {
  gtk_progress_bar_set_fraction( progress, 1.0 );
  gtk_progress_bar_set_text( progress, "One Hundred Percent" );
}

static void clear_activated( GtkMenuItem *item, GtkProgressBar *progress ) {
  gtk_progress_bar_set_fraction( progress, 0.0 );
  gtk_progress_bar_set_text( progress, "Reset to Zero" );
}

/*
 * Add or remove a status bar menu hint, depending on whether this function is 
 * initialized by a proximity-in-event or proximity-out-event.
 */
static gboolean statusbar_hint( GtkMenuItem *menuitem,
    GdkEventProximity *event, GtkStatusbar *statusbar ) {
  guint id = gtk_statusbar_get_context_id( statusbar, "MenuItemHints" );

  gchar *hint;
  if ( event->type == GDK_ENTER_NOTIFY ) {
    hint = (gchar *) g_object_get_data( G_OBJECT( menuitem ), "menuhint" );
    gtk_statusbar_push( statusbar, id, hint );
  } else if ( event->type == GDK_LEAVE_NOTIFY ) {
    gtk_statusbar_pop( statusbar, id );
  }

  return FALSE;
}
