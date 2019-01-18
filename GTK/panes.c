/* added to make file */

#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
    GtkWidget *window, *hpaned, *button1, *button2;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Panes");

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 225, 150);

    /* hpaned is a widget - a box, horizontally stacked */
    hpaned = gtk_hpaned_new ();
    button1 = gtk_button_new_with_label ("Resize");
    button2 = gtk_button_new_with_label ("Me!");

    /* no custom callback - just call gtk_widget_destroy directly */
    g_signal_connect_swapped (G_OBJECT (button1), "clicked", G_CALLBACK (gtk_widget_destroy), (gpointer) window);
    g_signal_connect_swapped (G_OBJECT (button2), "clicked", G_CALLBACK (gtk_widget_destroy), (gpointer) window);

    /* pack both buttons as the two children of the GtkPaned widget */
    gtk_paned_add1 (GTK_PANED (hpaned), button1);
    gtk_paned_add2 (GTK_PANED (hpaned), button2);

    gtk_container_add (GTK_CONTAINER (window), hpaned);
    gtk_widget_show_all (window);

    gtk_main();
    return 0;
}
