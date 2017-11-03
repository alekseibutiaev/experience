#include <set>
#include <iostream>
#include <iterator>
#include <algorithm>

struct test {
	test( int a, int b = 0 ) 
		: m_a( a )
		, m_b( b )
	{}
	int m_a;
	int m_b;
};

bool operator<( const test& lvalue, const test& rvalue )
{
	return lvalue.m_a < rvalue.m_a; 
}

std::ostream& operator<<(std::ostream& out, const test& value )
{
	out << "( " << value.m_a << ", " << value.m_b << " )";
	return out;
}

using test_set_t = std::set<test>;

int main( int ac, char* av[] ) {
	test_set_t sets;
	for(int i = 0; i < 10; ++i)
		sets.insert( test( i, i * 2 ) );
	std::copy( sets.begin(), sets.end(), std::ostream_iterator<test>( std::cout, "\n" ) );

	for(int i = 0; i < 10; ++i)
		sets.insert( test( i ) );
	std::copy( sets.begin(), sets.end(), std::ostream_iterator<test>( std::cout, "\n" ) );

	return 0;
}

