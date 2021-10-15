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


# one directory per project, one executable per directory
project_dirs := $(shell find * -maxdepth 0 -type d )

# executables are named after its directory and go into the same directory
exes := $(foreach dir,${project_dirs},${dir}/${dir})

all : ${exes}

#  the rules

.SECONDEXPANSION:

objects = $(patsubst %.cpp,%.o,$(wildcard $(dir ${1})*.cpp))

# link
${exes} : % : $$(call objects,$$*) Makefile
    g++ -o $@ $(filter-out Makefile,$^) ${LDFLAGS} ${LDLIBS}

# compile .o and generate dependencies
%.o : %.cpp Makefile
    g++ -c -o $@ -Wall -Wextra ${CPPFLAGS} ${CXXFLAGS} -MD -MP -MF ${@:.o=.d} $<

.PHONY: clean

clean :
    rm -f $(foreach exe,${exes},$(call objects,${exe})) $(foreach dir,${project_dirs},$(wildcard ${dir}/*.d)) ${exes}
