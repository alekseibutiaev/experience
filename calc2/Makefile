TARGET=calc2
CXX=c++
RM=rm

all: calc2.o
	$(CXX) $^ -o $(TARGET)

.cpp.o:
	$(CXX) -c $<

clean:
	$(RM) -rf *.o $(TARGET)
