TARGET=mult_matrix
OBJECTS=$(TARGET).o

CC = gcc
CXX = g++

WARNING_FLAGS = -Wall -Werror

CFLAGS = $(WARNING_FLAGS) -O0 -g3
CXXFLAGS = $(WARNING_FLAGS) -O0 -g3
LDFLAGS = 

all: $(TARGET)

$(TARET): $(OBJECTS)
	$(CXX) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $<

.cpp.o:
	$(CXX) -c $(CFLAGS) $<

clean:
	-rm -rfv $(TARGET) *.o *~