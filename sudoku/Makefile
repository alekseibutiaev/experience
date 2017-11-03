CXXFLAGS = -Wall -g3 -O0
LDFLAGS =
TARGETS = sudoku

all: $(TARGETS)

%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)

%: %.o
	g++ -o $@ $< $(LDFLAGS)

clean:
	rm -rfv *.o $(TARGETS)
