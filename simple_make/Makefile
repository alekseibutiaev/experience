#CXXFLAGS =	-O2 -g -Wall -fmessage-length=0
#OBJS =		test.o
#LIBS =
#TARGET =	test
#$(TARGET):	$(OBJS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
#all:	$(TARGET)
#clean:
#	rm -f $(OBJS) $(TARGET)

CXXFLAGS = -Wall -g3 -O0
LDFLAGS = -lm
all: test1 test0

%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)

%: %.o
	g++ -o $@ $< $(LDFLAGS)

clean:
	rm -rfv *.o test1 test0