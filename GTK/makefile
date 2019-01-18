CC=gcc
DEPS = gtk/gtk.h
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS= `pkg-config --libs gtk+-2.0`

# object rule
#   object file depends on *.c file and the .h files
#   compile with defined compiler
#   -c  == generate the object file 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)
	
# executable rule - when the object files change
helloworld2:  helloworld2.o
	gcc -o helloworld2 helloworld2.o $(CFLAGS) $(LDFLAGS)