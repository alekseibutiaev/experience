TARGET = marble
OBJS = CCell.o CBoard.o CBoardStatus.o CBoardInit.o CSolution.o $(TARGET).o 
LIBS =

CC = gcc
CXX = g++

CXXFLAGS = -O0 -g3 -Werror -Wall -fmessage-length=0
CFLAGS = -O0 -g3 -Werror -Wall -fmessage-length=0

LDFLAGS =
# GTK flags
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-2.0)
GTK_LDFLAGS = $(shell pkg-config --libs gtk+-2.0)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

.c.o:
	$(CC) -c $(CFLAGS) $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -f $(OBJS) $(TARGET)
