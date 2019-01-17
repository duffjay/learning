/*
 * toggle buttons
 *    the book's listing was missting some stuff - interesting test :)
 */

#include <gtk/gtk.h>

/* -- call back functions header declaration -- */
static void button_toggled (GtkToggleButton*, GtkWidget*);

int main (int argc, char *argv[])
{
    GtkWidget *window, *vbox, *toggle1, *toggle2;

    gtk_init (&argc, &argv);

    /* window initialization */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Toggle Buttons");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 350, 150);  /* added - without this, too small */

    /* vbox configuration */
    vbox = gtk_vbox_new (TRUE, 5);
    toggle1 = gtk_toggle_button_new_with_mnemonic ("_Deactivate the other one!");
    toggle2 = gtk_toggle_button_new_with_mnemonic ("_No! Deactivate that one!");

    /* you have to add the buttons to the vbox */
    gtk_box_pack_start_defaults (GTK_BOX (vbox), toggle1);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), toggle2);

    /* connect signals 
    **   note that the signature is dependent on the callback signature
    **        in this case, the two (2) toggles
    */
    g_signal_connect (G_OBJECT (toggle1), "toggled", G_CALLBACK (button_toggled), (gpointer) toggle2);  
    g_signal_connect (G_OBJECT (toggle2), "toggled", G_CALLBACK (button_toggled), (gpointer) toggle1);

    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show_all (window);

    gtk_main();
    return 0;
}

/* -- call back function implementation -- */

/*
 * if the toggle button was activated, sets the other as disabled, 
 * Otherwise, enable the other togle button
 */

/* static function means it can only be called from this file:  togglebuttons.c
 * that's great - otherwise, we could have a duplication conflict amount other files
 * e.g.  we had destroy functions in a couple of lessons - the compiler would have had problems with that
 */

static void button_toggled (GtkToggleButton *toggle, GtkWidget *other_toggle)
{
    gchar *strval;

    g_object_get (toggle, "name", &strval, NULL);  /* if you forget null, missing sentinal warning */
    g_print ("widget name: %s\n", strval);

    if (gtk_toggle_button_get_active (toggle))
    {
        g_print ("primary F -> T - so make the secondary F\n");
        gtk_widget_set_sensitive (other_toggle, FALSE);
    }
    else
    {
        g_print ("primary T -> F - so make the secondary T\n");
        gtk_widget_set_sensitive (other_toggle, TRUE);
    }
}



