#include <string>
#include <typeinfo>
#include <iostream>

struct base {
	virtual ~base() = default;
};

struct type_a : public base {
};

struct type_b : public base {
};

std::string get_name( const base& c ) {
	std::string r = typeid( c ).name();
	return r;
}

int main(int ac, char* av[]) {
	type_a a;
	type_b b;
	std::cout << get_name( a ) << std::endl;
	std::cout << get_name( b ) << std::endl;
	std::cout << "Hello world." << std::endl;
	return 0;
}

