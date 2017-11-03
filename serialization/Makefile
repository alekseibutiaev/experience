CXXFLAGS = -Wall -g3 -O0 -I/usr/local/boost/1.55.0/
LDFLAGS = -L/usr/local/boost/1.55.0/lib64 -lssl -lboost_system -lboost_serialization

TARGETS = server client

all: $(TARGETS)

%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)

%: %.o
	g++ -o $@ $< $(LDFLAGS)

client: session.hpp stock.hpp
server: session.hpp stock.hpp

clean:
	rm -rfv *.o $(TARGETS)
