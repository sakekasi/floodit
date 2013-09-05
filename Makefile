CXX = clang++
CFLAGS=  -Wall -pedantic -std=c++11 -g
LIBFLAGS= -fPIC -c -O
SDLFLAGS= -lSDL -lSDL_gfx 
PARFLAGS = -lpthread

OBJECTS= floodit-board.o sdl-floodit-board.o sdl-buttons.o board-tree.o board-tree-gen.o board-tree-search.o

all:main

board-tree.o : board-tree-inl.hh
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS) 

board-tree-gen.o : board-tree-gen.hh
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS) 

board-tree-search.o : board-tree-search.hh
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS) 

sdl-floodit-board.o : floodit-board.o sdl-floodit-board-inl.hh sdl-floodit-board.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS) 

sdl-buttons.o : floodit-board.o sdl-buttons-inl.hh sdl-buttons.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS) 

floodit-board.o : floodit-board-inl.hh floodit-board.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS)



shared: shared-library
shared-library: $(OBJECTS)
	$(CXX) -shared -Wl,-soname,libfloodit.so -o libfloodit.so $(OBJECTS) $(CFLAGS)

main: main.cc shared-library
	$(CXX) $@.cc $(CFLAGS) -o main -L. -lfloodit $(HEADERS) $(SDLFLAGS) $(PARFLAGS)

.PHONY: clean
clean:
	rm *~ *.o main *.so *.a
