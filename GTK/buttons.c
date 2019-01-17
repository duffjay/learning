/*
 *  add a button
 *  how do you add multiple buttons?
 *  - note that if you just add a button, at runtime, you'll get an error:
 *   (buttons:17617): Gtk-WARNING **: 
 *       Attempting to add a widget with type GtkButton to a GtkWindow, 
 *       but as a GtkBin subclass a GtkWindow can only contain one widget at a time; 
 *       it already contains a widget of type GtkButton
 *  - see the boxes.c exammple
 */


#include <gtk/gtk.h>

/* custome data structures */


/*
** call backs - forwrd definition
**
*/
static void destroy (GtkWidget*, gpointer);

int main (int argc, char *argv[])
{
    GtkWidget *window, *buttonClose, *button10, *button20;

    gtk_init(&argc, &argv);

    /* initialize windows */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Buttons");
    gtk_container_set_border_width (GTK_CONTAINER (window), 25);
    gtk_widget_set_size_request (window, 200, 100);

    /* connect to call back functions */
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy), NULL);   /* no data passed */


    /* create a button - mnemonic key of Alt+C */
    buttonClose = gtk_button_new_with_mnemonic ("_Close");  
    button10 = gtk_button_new_with_mnemonic ("_Add_10"); 
    button20 = gtk_button_new_with_mnemonic ("_Add_20");   
    gtk_button_set_relief (GTK_BUTTON (buttonClose), GTK_RELIEF_NONE);
    gtk_button_set_relief (GTK_BUTTON (button10), GTK_RELIEF_NONE);
    gtk_button_set_relief (GTK_BUTTON (button20), GTK_RELIEF_NONE);

    /* Connect the button to the clicked signal. 
    ** - the callback function receives the 
    **   window followed by the button because the arguments are swapped
    ** - compare to g_signal_connect (window)
    **              g_signal_connect_swapped (button, window)
    */
    g_signal_connect_swapped (G_OBJECT (buttonClose), "clicked", G_CALLBACK (gtk_widget_destroy), (gpointer) window);

    /* add to the container */
    gtk_container_add (GTK_CONTAINER (window), buttonClose);
    gtk_container_add (GTK_CONTAINER (window), button10);
    gtk_container_add (GTK_CONTAINER (window), button20);
    gtk_widget_show_all (window);

    gtk_main ();
    return 0;
}

/* implementation of functions */

/* stop the GTK+ main loop function. */
static void destroy (GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}