CXXFLAGS = -Wall -g3 -O0 -I/usr/include/
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lboost_system

TARGETS = epolltest

all: $(TARGETS)

%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)

%: %.o
	g++ -o $@ $< $(LDFLAGS)

clean:
	rm -rfv *.o $(TARGETS)
