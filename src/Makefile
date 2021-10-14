IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=build
LDIR =../lib

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hellomake.o hellofunc.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

squaredmake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

oneginmake:


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
