#include <gtk/gtk.h>

static cairo_surface_t *surface = NULL;

static void clear_surface() {
    cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_destroy(cr);
}

static gboolean on_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data) {
    if (surface != NULL) {
        cairo_surface_destroy(surface);
    }
    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR,
            gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height(widget));
    clear_surface();
    return TRUE;
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    return FALSE;
}

static void draw_brush(GtkWidget *widget, gdouble x, gdouble y) {
    cairo_t *cr = cairo_create(surface);
    cairo_rectangle(cr, x - 3, y - 3, 6, 6);
    cairo_fill(cr);
    cairo_destroy(cr);
    gtk_widget_queue_draw_area(widget, x - 3, y - 3, 6, 6);
}

static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (surface == NULL) {
        return FALSE;
    }
    if (event->button == GDK_BUTTON_PRIMARY) {
        draw_brush(widget, event->x, event->y);
    } else if (event->button == GDK_BUTTON_SECONDARY) {
        clear_surface();
        gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

static gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer user_data) {
    if (surface == NULL) {
        return FALSE;
    }
    if (event->state & GDK_BUTTON1_MASK) {
        draw_brush(widget, event->x, event->y);
    }
    return TRUE;
}

static void close_window() {
    if (surface != NULL) {
        cairo_surface_destroy(surface);
    }
    gtk_main_quit();
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Basic Drawing");
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
    gtk_container_add(GTK_CONTAINER(window), frame);

    GtkWidget *draw_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(draw_area, 100, 100);
    gtk_container_add(GTK_CONTAINER(frame), draw_area);

    g_signal_connect(draw_area, "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(draw_area, "configure-event", G_CALLBACK(on_configure_event), NULL);
    g_signal_connect(draw_area, "motion-notify-event", G_CALLBACK(on_motion_notify), NULL);
    g_signal_connect(draw_area, "button-press-event", G_CALLBACK(on_button_press), NULL);

    gtk_widget_set_events(draw_area, gtk_widget_get_events(draw_area) | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
