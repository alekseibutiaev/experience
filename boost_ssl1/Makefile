CXXFLAGS = -Wall -g3 -O0 -I/usr/local/boost/1.55.0/
LDFLAGS = -L/usr/local/boost/1.55.0/lib64 -lssl -lboost_system

TARGETS = server client

all: $(TARGETS)

%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)

%: %.o
	g++ -o $@ $< $(LDFLAGS)

clean:
	rm -rfv *.o $(TARGETS)
