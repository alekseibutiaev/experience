#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

template <unsigned int base>
int add(std::vector<int>& lvalue, const std::vector<int>& rvalue) {
	std::vector<int>::reverse_iterator lit = lvalue.rbegin();
	std::vector<int>::const_reverse_iterator rit = rvalue.rbegin();
	int cary = 0;
	bool nlend = true;
	bool nrend = true;
	for (; nrend || nlend; ) {
		int tmp = 0;
		int& l = nlend  ? *lit : tmp;
		const int& r = nrend ? *rit : 0;
		l = r + l + cary;
		cary = l / base;
		if (l >= base)
			l = l % base;
		if ( lit != lvalue.rend())
			nlend = ++lit != lvalue.rend();
		else
			lvalue.insert(lvalue.begin(), l);
		if (rit != rvalue.rend())
			nrend = ++rit != rvalue.rend();
	}
	return cary;
}

void print(const int& c, const std::vector<int>& value) {
	std::cout << c << '.';
	std::copy(value.begin(), value.end(), std::ostream_iterator<int>(std::cout, "."));
	std::cout << std::endl;
}

template <unsigned int base>
void check_duble( const int& value, int& last) {
	std::vector<int> flags( base );
	int v = value;
	for (; v;) {
		int index = v % base;
		v /= base;
		if (++flags[index] > 1) {
			std::cout << value << " " << value - last << std::endl;
			last = value;
			return;
		}
	}

}

int main() {
	{
		std::vector<int> a = { 3, 5, 9 };
		std::vector<int> b = { 6, 2 };
		int c = add<10>(a, b);
		print(c, a);
	}
	{
		std::vector<int> a = { 6, 2 };
		std::vector<int> b = { 3, 5, 9 };
		int c = add<10>(a, b);
		print(c, a);
	}
	{
		std::vector<int> a = { 1, 7, 6, 5 };
		std::vector<int> b = { 1, 3, 4 };
		int c = add<8>(a, b);
		print(c, a);
	}
	{
		std::vector<int> a = { 1, 0, 1, 1 };
		std::vector<int> b = { 1, 1, 1 };
		int c = add<2>(a, b);
		print(c, a);
	}
	int last = 0;
	for (int i = 0; i < 1000; ++i)
		check_duble<10>(i, last);
	return 0;
}

