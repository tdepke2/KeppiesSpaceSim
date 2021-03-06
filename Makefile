CC=g++
CFLAGS=-c -std=c++11 -Wall
SOURCES=main.cpp Body.cpp GraphicsEngine.cpp Simulator.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
PROGRAM=spaceSim

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LIBS) 

.cpp.o: 
	$(CC) $(CFLAGS) $<

depend: .depend

.depend: $(SOURCES)
	rm -f .depend
	$(CC) $(CFLAGS) -MM $^ >> .depend;

include .depend

clean:
	rm -f .depend $(PROGRAM) $(OBJECTS)
