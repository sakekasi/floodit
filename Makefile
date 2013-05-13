CXX = g++
CFLAGS=  -Wall -pedantic -std=c++11 -g
LIBFLAGS= -fPIC -c -O
SDLFLAGS= -lSDL -lSDL_gfx

OBJECTS= floodit-board.o sdl-floodit-board.o sdl-buttons.o

all:main

sdl-floodit-board.o : floodit-board.o sdl-floodit-board-inl.hh sdl-floodit-board.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS) $(SDLFLAGS)

sdl-buttons.o : floodit-board.o sdl-buttons-inl.hh sdl-buttons.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS) $(SDLFLAGS)

floodit-board.o : floodit-board-inl.hh floodit-board.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS)



shared: shared-library
shared-library: $(OBJECTS)
	$(CXX) -shared -Wl,-soname,libfloodit.so -o libfloodit.so $(OBJECTS) $(CFLAGS)

main: main.cc shared-library
	$(CXX) $@.cc $(CFLAGS) -o main -L. -lfloodit $(HEADERS) $(SDLFLAGS)

.PHONY: clean
clean:
	rm *~ *.o main *.so *.a
