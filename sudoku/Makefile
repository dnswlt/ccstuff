TARGET = sudoku.exe 
LIBS = 
CC = g++
CFLAGS = -O2

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cc, %.o, $(wildcard *.cc))
HEADERS = $(wildcard *.h)

%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

winclean:
	del /Q *.o
	del /Q $(TARGET)

clean:
	-rm -f *.o $(TARGET)
