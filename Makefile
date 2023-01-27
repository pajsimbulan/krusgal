#------------------------------------------------------------------------------
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c11 -Wall -c 
LINK           = gcc -std=c11 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

MWST : MWST.o $(BASE_OBJECTS)
	$(LINK) MWST MWST.o $(BASE_OBJECTS)

MWST.o : MWST.c $(HEADERS)
	$(COMPILE) MWST.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) MWST MWST.o $(BASE_OBJECTS)

