/*
 * boxes.c
 *    example of a vertical box == vbox
 *    note - the call back on the "signal" is to destroy
 *         - so when you click - it destroys
 * 
 *    challenge - create a custom data structure
 *              - alter the data on each click
 *                - how do you know what button was clicked?
 */

#include <gtk/gtk.h>

/* data definitions */
#define NUM_NAMES 4
const gchar* names[] = { "Andrew", "Joe", "Samantha", "Jonathan"};

/* call back functions */


/* -- main -- */
int main (int argc, char *argv[])
{
    gint i;
    GtkWidget *window, *vbox;

    gtk_init (&argc, &argv);

    /* initial containers & windows */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "V-Boxes");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 200, -1);

    vbox = gtk_vbox_new (TRUE, 5);   /* (homogeneous -it figures out size, spacing) */

    /* add NUM_NAMES buttons to the vertical box */
    for (i = 0; i < NUM_NAMES; i++)
    {
        GtkWidget *button = gtk_button_new_with_label (names[i]);  /* so *button is a pointer to an array of buttons */
        gtk_box_pack_start_defaults (GTK_BOX (vbox), button);      /* pack all widgets by reference */
        /* connect signals to callback functions */
        g_signal_connect_swapped (G_OBJECT (button), "clicked", G_CALLBACK (gtk_widget_destroy), (gpointer) button);
    }

    gtk_container_add (GTK_CONTAINER (window), vbox); 
    gtk_widget_show_all (window);

    gtk_main ();
    return 0;
}