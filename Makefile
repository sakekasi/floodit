CXX = g++
HEADERS = `pkg-config gtkmm-3.0 cairomm-1.0 --cflags`
LIBS = `pkg-config gtkmm-3.0 cairomm-1.0 --libs`
CFLAGS= -Wall -pedantic -std=c++11

all:main

gtk-floodit-board.o : gtk-floodit-board.hh gtk-floodit-board.cc
	$(CXX) $*.cc -fPIC -c -O -o $@ $(HEADERS) $(LIBS) $(CFLAGS)

floodit-board.o : floodit-board.hh floodit-board.cc
	$(CXX) $*.cc -fPIC -c -O -o $@ $(CFLAGS)

main-window.o : main-window.hh main-window.cc
	$(CXX) $*.cc -fPIC -c -O -o $@ $(HEADERS) $(LIBS) $(CFLAGS)



shared: shared-library
shared-library: gtk-floodit-board.o floodit-board.o main-window.o
	$(CXX) -shared -Wl,-soname,libfloodit.so -o libfloodit.so  gtk-floodit-board.o floodit-board.o main-window.o $(CFLAGS)

main: main.cc shared-library
	$(CXX) $@.cc $(CFLAGS) -g -o main -L. -lfloodit $(HEADERS) $(LIBS) -lboost_system  -g

.PHONY: clean
clean:
	rm *~ *.o main *.so *.a
