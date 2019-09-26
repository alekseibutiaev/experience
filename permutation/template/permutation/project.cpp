#include <set>
#include <vector>
#include <limits>
#include <utility>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <functional>

namespace {

  const int& get_ref(std::size_t pos, std::size_t size, const int* array, std::size_t idx) {
    const int* r = 0;
    if(0 == pos && std::numeric_limits<std::size_t>::max() == idx)
      r = (array + size + pos + idx);
    else if(1 == size - pos)
      if(std::numeric_limits<std::size_t>::max() == idx)
        r = (array + pos + idx);
      else if(1 == idx)
        r = (array + pos - size + idx);
      else
        r = (array + pos + idx);
    else
      r = (array + pos + idx);
    return *r;
  }

  class cell_t {
  public:
    cell_t(std::size_t pos, std::size_t size, const int* array)
        : m_a(get_ref(pos, size, array, -1))
        , m_b(get_ref(pos, size, array, 0))
        , m_c(get_ref(pos, size, array, 1)) {
    }
    bool is_valid() const {
      return m_a != m_b && m_b != m_c && m_a != m_c;
    }
    bool operator==(const cell_t& rv) const {
      return m_a == rv.m_a and m_b == rv.m_b and m_c == rv.m_c;
    }
  private:
    const int& m_a;
    const int& m_b;
    const int& m_c;
  };


  using reelinfo_t = std::pair<std::size_t, std::size_t>;
  struct reelinfo_pred_t {
    bool operator()(const reelinfo_t& lv, const reelinfo_t& rv) const {
      return lv.second > rv.second || (!(rv.second > lv.second) && lv.first < rv.first);
    }
  };

  using reelset_t = std::set<reelinfo_t, reelinfo_pred_t>;
  using cells_t = std::vector<cell_t>;

  const std::size_t _size = 32;
  int reel[_size];
  std::size_t count = 0;
  const cell_t cells[_size] = {
    {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel},
    {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel},
    {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel},
    {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel},
    {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel},
    {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel},
    {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel},
    {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}, {count++, _size, reel}
  };

  const reelset_t rsi = {{0, 2}, {1, 4}, {2, 4}, {3, 3}, {4, 4}, {5, 4}, {6, 3}, {7, 3}, {8, 2}, {9, 2}, {10, 1}};

  void next(const reelset_t&) {

  }

} /* namespace */


int main(int ac, char* av[]) {
  std::size_t r[_size] = {0, 1, 8, 6, 2, 5, 3, 1, 6, 4, 7, 2, 5, 1, 9, 7, 4, 3, 5,10, 2, 1, 8, 3, 5, 0, 4, 2, 6, 7, 9, 4};
  std::sort(&r[0], &r[_size]);
  std::copy(&r[0], &r[_size], std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;

  std::fill(&reel[0], &reel[_size], -1);
  const reelset_t& rr = rsi;
  const cell_t(&a)[_size] = cells;
  std::cout << a[0].is_valid() << std::endl;
  std::cout << std::count(&a[0], &a[_size], a[0]) << std::endl;
  next(rr);
#if 0
  unsigned long long count = 0;
  while(std::next_permutation(&r[0], &r[32])){
    ++count;
    if(0 != count%100000)
      continue;
    std::cout << "permutation count: " << count << std::endl;    
    std::copy(&r[0], &r[32], std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
  }
  std::cout << "permutation count: " << count << std::endl;
#endif
  return 0;
}