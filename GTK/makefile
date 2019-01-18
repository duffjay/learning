#
# GTK make file
#

CC=gcc
DEPS = gtk/gtk.h
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS= `pkg-config --libs gtk+-2.0`


	
# executable rule - when the object files change
all: helloworld2 panes tables

helloworld2:  helloworld2.o
	gcc -o helloworld2 helloworld2.o $(CFLAGS) $(LDFLAGS)
	
panes: panes.o
	gcc -o panes panes.o $(CFLAGS) $(LDFLAGS)

tables: tables.o
	gcc -o tables tables.o $(CFLAGS) $(LDFLAGS)

# object rule
#   object file depends on *.c file and the .h files
#   compile with defined compiler
#   -c  == generate the object file 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)
	
clean:
	rm -f *.o
	
.PHONE: all