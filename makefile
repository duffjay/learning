#
# main makefile
# 
CC=gcc
DEPS = gtk/gtk.h
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS= `pkg-config --libs gtk+-2.0`

gtkDIR=GTK/

	
# executable rule - when the object files change
all: $(gtkDIR)helloworld2 $(gtkDIR)panes $(gtkDIR)tables $(gtkDIR)boxes $(gtkDIR)buttons

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
		
clean:
	rm -f $(gtkDIR)*.o
	
.PHONE: all