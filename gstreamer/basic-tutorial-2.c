#include <gst/gst.h>


/*
  source -> filter -> sink
*/

int main(int argc, char *argv[]) {
  GstElement *pipeline, *source, *sink;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* 
    Create the elements 
      use the element factory (element type, name of element)
      videotestsrc - source element (produces) a test video signal
      autovideosink - sink element (consumes) - automatically selects capabilities?
  */
  source = gst_element_factory_make ("videotestsrc", "source");
  sink = gst_element_factory_make ("autovideosink", "sink");

  /* 
    Create the empty pipeline 
      you need this before you can put elements in it
  */
  pipeline = gst_pipeline_new ("test-pipeline");
  // check for successful creation
  if (!pipeline || !source || !sink) {
    g_printerr ("Not all elements could be created.\n");
    return -1;
  }

  /* 
    Build the pipeline 
      bin contains elements
      pipeline is a type of bin (top level?)
        casting (to pipeline)
        NULL terminated list
  */
  gst_bin_add_many (GST_BIN (pipeline), source, sink, NULL);
  // elements must be in the same bin before they can be linked
  // order is important source -> sink
  if (gst_element_link (source, sink) != TRUE) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (pipeline);
    return -1;
  }

  /* 
    Modify the source's properties
      looks like a GObject model - not a gst_ function/object 
      elements have read/write properties
         g_object_get (read)
         g_object_set (write)
    gst-inpect-1.0 tool exposes all properties
  */
  g_object_set (source, "pattern", 0, NULL);    // set source.pattern property = 0

  /* Start playing */
  ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (pipeline);
    return -1;
  }

  /* 
    get the bus
      the bus delivers messages to the elements within the pipeline
      handles the complexity of threading
    keep an eye on the bus to get messages - e.g. error messages from the elements
    
    Wait until error or EOS 
  */
  bus = gst_element_get_bus (pipeline);
  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

  /* 
     Parse message 
       fancier message handling than the last example
  */
  if (msg != NULL) {
    GError *err;
    gchar *debug_info;
    g_print ("msg received\n");
    // utilizes a GLib Gerror structure
    switch (GST_MESSAGE_TYPE (msg)) {    // get type of message
      case GST_MESSAGE_ERROR:
        gst_message_parse_error (msg, &err, &debug_info);
        g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
        g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
        g_clear_error (&err);
        g_free (debug_info);
        break;
      case GST_MESSAGE_EOS:
        g_print ("End-Of-Stream reached.\n");
        break;
      default:
        /* We should not reach here because we only asked for ERRORs and EOS */
        g_printerr ("Unexpected message received.\n");
        break;
    }
    gst_message_unref (msg);
  }

  /* Free resources */
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  return 0;
}