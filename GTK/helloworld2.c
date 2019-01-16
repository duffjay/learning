#include <gtk/gtk.h>

/*
 * hello world version 2 
 * - i changed it to pass a custom data structure through the callbacks
 *   similar to gstreamer
 * a) define the structure
 * b) define the callback header definitions to reflect the structure (they were NULL)
 * c) pass it in (as a pointer) on the call back connection
 * d) consume them in the functions
 *    data->var1 = 2
 * 
 */

/* 
** my custom DataStructure
** - pass this through the callbacks
*/
typedef struct _CustomData {
    gint64 var1;
    gint64 var2;
    gint64 var3;
} CustomData;

/* define the callback functions
** changed from book - pass a pointer to your custom structure
** CustomData*
*/
static void destroy (GtkWidget*, CustomData*);
static gboolean delete_event (GtkWidget*, GdkEvent*, CustomData*);

int main(int argc, char *argv[])
{
    GtkWidget *window, *label;
    CustomData data;  /* my custom structure for passing data around */

    gtk_init(&argc, &argv);
    
    /* -- window display attributes -- */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "Hello World");   // cast window as a GTK_WINDOW, it's defined as a widget
                                                                // a window is a child of widget
    gtk_container_set_border_width(GTK_CONTAINER (window), 10); // now you casting window as a GTK_CONTAINER
    gtk_widget_set_size_request(window, 200,100);

    /* -- connect the main window signals to call-backs --
        - destroy
        - delete event
    */

    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy), &data);   // data is my revision
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (delete_event), &data);

    /* Createa new TtkLabel widget that is selectable */
    label = gtk_label_new ("Hello World");  /* widget label*/
    gtk_label_set_selectable(GTK_LABEL(label), TRUE);

    /* add the labbel as a child widget of the window.
    ** - you are adding to the container
    */
    gtk_container_add (GTK_CONTAINER (window), label);
    gtk_widget_show_all (window);

    gtk_main();  /* this starts the main loop - no way out!  except via the call backs */
    g_print("end of program - what's in our data structure?\n");
    g_print("data.var1 %" G_GUINT64_FORMAT "\n", data.var1);  /* data.var1 was declared as a gint64 */
    g_print("data.var2 %" G_GUINT64_FORMAT "\n", data.var2);
    return 0;

}

/*
   C A L L    B A C K    F U N C T I O N S
*/

/* destroy call back - stop the GTK+ main loop function when the window */
static void destroy (GtkWidget *window, CustomData *data)
{
    g_print("destroy callback function called\n");
    data->var2 = 20;
    gtk_main_quit();   /* this is what shuts down the main loop */
}

/* Return False to destroy the widget
** by returning True, you can cancel a delete-event.
** This can be used to confirm quitting the application 
** - this is called when you click the X to close the window
**   - which evidently calls a destroy function (you passed FALSE to destroy)
**     in between here, you could have added, "are you really sure?"
*/
static gboolean delete_event (GtkWidget *window, GdkEvent *event, CustomData *data)
{
    g_print("delete_event callback function called\n");
    data->var1 = 10;
    return FALSE;
}
