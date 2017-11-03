#include <assert.h>
#include <iostream>
#include <map>
#include <limits>

template<class K, class V>
class interval_map {
	friend void IntervalMapTest();

private:
	std::map<K, V> m_map;


public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	};

	// Assign value val to interval [keyBegin, keyEnd). 
	// Overwrite previous values in this interval. 
	// Do not change values outside this interval.
	// Conforming to the C++ Standard Library conventions, the interval 
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, 
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, const V& val) {
		// INSERT YOUR SOLUTION HERE
		typedef std::map<K, V>::const_iterator iter;
		if (!(keyBegin < keyEnd))
			return;
		V valueend = m_map[std::numeric_limits<K>::lowest()];

		iter il = m_map.lower_bound(keyBegin);
		iter iu = m_map.upper_bound(keyEnd);

		if (il == m_map.end() && iu == m_map.end()) {
		}
		else if (iu == m_map.end()) {
			iter it = il;
			m_map[keyBegin - 1] = (--it)->second;
		}
		else  {
			iter it = iu;
			valueend = (--it)->second;
		}

		m_map.erase(il, iu);
		m_map[keyBegin] = val;
		m_map[keyEnd] = valueend;

	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.

typedef interval_map<int, int> imap;

void IntervalMapTest() {
	imap im(std::numeric_limits<int>::lowest());
	// case a
	im.assign(10, 20, 5);
	std::cout << "im.assign(10, 20, 5);" << std::endl;
	for (int i = 0; i < 35; ++i)
		std::cout << i << " = " << im[i] << std::endl;
	std::cout << std::endl;

	std::cout << "im.assign( 18, 25, 6);" << std::endl;
	im.assign( 18, 25, 6);
	for (int i = 0; i < 35; ++i)
		std::cout << i << " = " << im[i] << std::endl;
	std::cout << std::endl;

	std::cout << "im.assign(5, 12, 4);" << std::endl;
	im.assign(5, 12, 4);
	for (int i = 0; i < 35; ++i)
		std::cout << i << " = " << im[i] << std::endl;
	std::cout << std::endl;

	std::cout << "im.assign(10, 22, 3);" << std::endl;
	im.assign(10, 22, 3);
	for (int i = 0; i < 35; ++i)
		std::cout << i << " = " << im[i] << std::endl;
	std::cout << std::endl;

	std::cout << "im.assign(14, 26, 1);" << std::endl;
	im.assign(14, 26, 1);
	for (int i = 0; i < 35; ++i)
		std::cout << i << " = " << im[i] << std::endl;
	std::cout << std::endl;

	std::cout << "im.assign(5, 27, 0);" << std::endl;
	im.assign(5, 27, 0);
	for (int i = 0; i < 35; ++i)
		std::cout << i << " = " << im[i] << std::endl;
	std::cout << std::endl;

	std::cout << "im.assign(1, 3, 9);" << std::endl;
	im.assign(1, 3, 9);
	for (int i = 0; i < 35; ++i)
		std::cout << i << " = " << im[i] << std::endl;
	std::cout << std::endl;

	std::cout << "im.assign(30, 33, 2);" << std::endl;
	im.assign(30, 33, 2);
	for (int i = 0; i < 35; ++i)
		std::cout << i << " = " << im[i] << std::endl;
	std::cout << std::endl;

}

int main(int argc, char* argv[]) {
	IntervalMapTest();
	return 0;
}
