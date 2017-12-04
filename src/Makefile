IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)
ODIR=obj

_DEPS = p2psh.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = p2psh.o server.o content_provider.o content_tracker.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

p2psh: $(OBJ)
	gcc -pthread -o $@ $^ $(CFLAGS) -lcrypto

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
