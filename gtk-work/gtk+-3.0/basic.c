#include <gtk/gtk.h>

static void say_hello(GtkWidget *widget, gpointer user_data) {
    g_print("Hello, world\n");
}

static gboolean on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    g_print("delete event occurred\n");
    return TRUE;
}

static void exit_basic(GtkWidget *widget, gpointer user_data) {
    gtk_main_quit();
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Basic");

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "destroy-event", G_CALLBACK(on_delete_event), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *button = gtk_button_new_with_label("Hello, world");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(say_hello), NULL);
    GtkWidget *option_button = gtk_button_new_with_label("Options");
    g_signal_connect(G_OBJECT(option_button), "clicked", G_CALLBACK(say_hello), NULL);
    GtkWidget *exit_button = gtk_button_new_with_label("Exit");
    g_signal_connect(G_OBJECT(exit_button), "clicked", G_CALLBACK(exit_basic), NULL);

    /* Use grid to layout widgets */
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), option_button, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), exit_button, 0, 1, 2, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
