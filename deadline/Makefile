CXXFLAGS = -Wall -g3 -O0 -I/usr/local/boost/1.55.0/include
LDFLAGS = -L/usr/local/boost/1.55.0/lib64 -lboost_thread -lboost_system

TARGETS = deadline

all: $(TARGETS)

%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)

%: %.o
	g++ -o $@ $< $(LDFLAGS)

clean:
	rm -rfv *.o $(TARGETS)
