CXX = g++

TARGET = type_id

CXXFLAGS = -std=c++11 -g3 -O0 -pthread

all: $(TARGET)

$(TARGET): $(TARGET).o 
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean key

clean: 
	rm -fv *.o *.i *~
	rm -fv $(TARGET)

