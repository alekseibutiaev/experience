#include <list>
#include <deque>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <utility>
#include <typeinfo>
#include <iterator>
#include <iostream>
#include <functional>

using gen_f = std::function<std::pair<std::size_t, const char*>(std::size_t)>;

template<typename cont_t>
void test(const std::size_t count, gen_f gen) {
  const auto start = std::chrono::system_clock::now();
  cont_t cont;
  for(std::size_t i = 0; i < count; ++i){
    typename cont_t::iterator it = cont.begin();
    std::advance(it, gen(cont.size()).first);
    cont.insert(it, 0);
  }
  const std::chrono::duration<double> diff = std::chrono::system_clock::now() - start;
  std::cout << typeid(cont).name() << " type: " << gen(0).second <<" time is: " << diff.count() << std::endl;
}

std::pair<std::size_t, const char*> to_front(std::size_t) {
  return {0, __FUNCTION__};
}

std::pair<std::size_t, const char*> to_end(std::size_t val) {
  return {val, __FUNCTION__};
}

std::pair<std::size_t, const char*> to_random(std::size_t val) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<std::size_t> d{ std::size_t(0), val };
  return {std::round(d(gen)), __FUNCTION__};
}

void test() {
  const auto start = std::chrono::system_clock::now();
  std::list<std::size_t> t;
  for(std::size_t i = 0; i < 1000000; ++i)
    t.insert(t.end(), 0);
  const std::chrono::duration<double> diff = std::chrono::system_clock::now() - start;
  std::cout << typeid(t).name() << " type: " << " time is: " << diff.count() << std::endl;
}

void tttt( const std::string& v, bool c) {
  std::cout << v << std::endl;
  return;
}

int main(int ac, char* av[]) {

  tttt("1", true);
  tttt("2", false);

return 0;
  const std::size_t count = 1000000;

  test();
  std::cout << std::endl;
  test<std::vector<long long>>(count, to_front);
  test<std::deque<long long>>(count, to_front);
  test<std::list<long long>>(count, to_front);
  std::cout << std::endl;
  test<std::vector<long long>>(count, to_end);
  test<std::deque<long long>>(count, to_end);
  test<std::list<long long>>(count, to_end);
  std::cout << std::endl;
  test<std::vector<long long>>(count, to_random);
  test<std::deque<long long>>(count, to_random);
  test<std::list<long long>>(count, to_random);

  return 0;
}

