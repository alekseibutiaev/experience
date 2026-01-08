#include <set>
#include <list>
#include <deque>
#include <array>
#include <forward_list>
#include <vector>
#include <iterator>
#include <iostream>


template<std::input_iterator iter_t>
void algorithm(iter_t) {
  std::cout << "std::input_iterator" << std::endl;
}

#if 1
template<typename type_t, std::output_iterator<type_t> iter_t>
void algorithm(iter_t) {
  std::cout << "std::output_iterator" << std::endl;
}
#endif

template<std::forward_iterator iter_t>
void algorithm(iter_t) {
  std::cout << "std::forward_iterator" << std::endl;
}

template<std::bidirectional_iterator iter_t>
void algorithm(iter_t) {
  std::cout << "std::bidirectional_iterator" << std::endl;
}

template<std::random_access_iterator iter_t>
void algorithm(iter_t) {
  std::cout << "std::random_access_iterator" << std::endl;
}

int main(int ac, char* av[]) {
  std::cout << "test" << std::endl;
  int carray[10];
  std::array<int, 20> array;
  std::istream_iterator<int> iiter;
  std::ostream_iterator<int> oiter(std::cout, ", ");
  std::set<int> set;
  std::list<int> list;
  std::vector<int> vector;

  algorithm(iiter);
  algorithm<int>(oiter);
  algorithm(carray);
  algorithm(std::begin(carray));
  algorithm(array.begin());
  algorithm(set.begin());
  algorithm(list.begin());
  algorithm(vector.begin());
  return 0;
}

