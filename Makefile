CXX = g++
HEADERS = `pkg-config gtkmm-3.0 cairomm-1.0 --cflags`
LIBS = `pkg-config gtkmm-3.0 cairomm-1.0 --libs`
CFLAGS=  -Wall -pedantic -std=c++11
LIBFLAGS= -fPIC -c -O

all:main

gtk-floodit-board.o : floodit-board.o gtk-floodit-board-inl.hh gtk-floodit-board.cc
	$(CXX) $*.cc -o $@ $(HEADERS) $(LIBS) $(LIBFLAGS) $(CFLAGS)

main-window.o : gtk-floodit-board.o main-window-inl.hh main-window.cc
	$(CXX) $*.cc -o $@ $(HEADERS) $(LIBS) $(LIBFLAGS) $(CFLAGS)

floodit-board.o : floodit-board-inl.hh floodit-board.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS)

board-tree.o : floodit-board.o board-tree-inl.hh board-tree.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS)

floodit-solver.o : board-tree.o floodit-solver.hh floodit-solver.cc
	$(CXX) $*.cc -o $@ $(LIBFLAGS) $(CFLAGS)



shared: shared-library
shared-library: gtk-floodit-board.o floodit-board.o main-window.o board-tree.o floodit-solver.o
	$(CXX) -shared -Wl,-soname,libfloodit.so -o libfloodit.so  gtk-floodit-board.o floodit-board.o main-window.o $(CFLAGS)

main: main.cc shared-library
	$(CXX) $@.cc $(CFLAGS) -g -o main -L. -lfloodit $(HEADERS) $(LIBS) -g

.PHONY: clean
clean:
	rm *~ *.o main *.so *.a
