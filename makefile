#
# main makefile
# 
CC=gcc
DEPS = gtk/gtk.h
gstDEPS = gst/gst.h

# flags
# -- GTK was first
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS= $(shell pkg-config --libs gtk+-2.0)
# -- GST gstreamer
gstCFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gstreamer-1.0)
gstLDFLAGS=$(shell pkg-config --libs gstreamer-1.0)


gtkDIR=GTK/
gstDIR=gstreamer/
	
# executable rule - when the object files change
all:  allGTK allGST

# --- G T K ---
allGTK: $(gtkDIR)helloworld2 $(gtkDIR)panes $(gtkDIR)tables $(gtkDIR)boxes $(gtkDIR)buttons

$GTK/%.o: GTK/%.c $(DEPS)
	$(CC) -c -o GTK/$@ GTK/$< $(CFLAGS) $(LDFLAGS)
	
GTK/helloworld2:  GTK/helloworld2.o 
	$(CC) -o bin/helloworld2 GTK/helloworld2.o $(CFLAGS) $(LDFLAGS) 

GTK/panes:  GTK/panes.o
	$(CC) -o bin/panes GTK/panes.o $(CFLAGS) $(LDFLAGS)
	
GTK/tables:  GTK/tables.o
	$(CC) -o bin/tables GTK/tables.o $(CFLAGS) $(LDFLAGS)

GTK/boxes:  GTK/boxes.o
	$(CC) -o bin/boxes GTK/boxes.o $(CFLAGS) $(LDFLAGS)
	
GTK/buttons:  GTK/buttons.o
	$(CC) -o bin/buttons GTK/buttons.o $(CFLAGS) $(LDFLAGS)

# --- G S t r e a m e r ---
allGST:  basic-tutorial-1 basic-tutorial-2

#use a generic %.o: rule 
#didn't work

basic-tutorial-1: gstreamer/basic-tutorial-1.c
	gcc -o bin/basic-tutorial-1 gstreamer/basic-tutorial-1.c $(gstCFLAGS) $(gstLDFLAGS)

basic-tutorial-2: gstreamer/basic-tutorial-2.c
	gcc -o bin/basic-tutorial-2 gstreamer/basic-tutorial-2.c $(gstCFLAGS) $(gstLDFLAGS)
	
		
clean:
	rm -f $(gtkDIR)*.o
	
.PHONE: all