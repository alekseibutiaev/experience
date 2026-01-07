#include <iostream>
#include <algorithm>
#include <iterator>


#define BOOST_TEST_MODULE karnaught_test
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../gray.h"
#include "../karnaugh.h"

namespace {

  const std::size_t gray[] = {0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8};

  struct test4 {
    static const std::size_t arg_count;
    static const kh::khmap_t::value_t table[ 16 ];
    static const kh::khmap_t::value_t map[ 4 ][ 4 ];
  };
  const std::size_t test4::arg_count = 4;
  const kh::khmap_t::value_t test4::table[ 16 ] = {0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1};
  const kh::khmap_t::value_t test4::map[ 4 ][ 4 ] = { {0, 0, 1, 0 }, {0, 1, 1, 1 }, {1, 1, 1, 1 }, {0, 1, 1, 1 } };


} /* namespace */

namespace tools {

  template<typename type_t, std::size_t N>
  std::size_t size(const type_t(&)[N]) {
    return N;
  }

  template<typename type_t, std::size_t N>
  type_t* begin(type_t(&a)[N]) {
    return &a[0];
  }

  template<typename type_t, std::size_t N>
  type_t* end(type_t(&a)[N]) {
    return &a[N];
  }

} /* namespace tools */

BOOST_AUTO_TEST_SUITE(karnaught)

BOOST_AUTO_TEST_CASE(gray_code_encoder_decoder) {
// encoder
  for(std::size_t i = 0; i < tools::size(gray); ++i)
    BOOST_REQUIRE_EQUAL(gray[i], kh::to_gray(i));
  BOOST_REQUIRE_EQUAL(16, kh::to_gray(std::size_t(31)));
// decoder
  for(std::size_t i = 0; i < tools::size(gray); ++i)
    BOOST_REQUIRE_EQUAL(i, kh::from_gray(gray[i]));
  BOOST_REQUIRE_EQUAL(31, kh::from_gray(std::size_t(16)));
}

BOOST_AUTO_TEST_CASE(karnaught_initialize) {
  kh::khmap_t kh4(5);
  BOOST_REQUIRE_EQUAL(4, kh4.m_array.size());
  BOOST_REQUIRE_EQUAL(4, kh4.m_array[0].size());
  BOOST_REQUIRE_EQUAL(4, kh4.m_array[1].size());
  BOOST_REQUIRE_EQUAL(4, kh4.m_array[2].size());
  BOOST_REQUIRE_EQUAL(4, kh4.m_array[3].size());
  BOOST_REQUIRE_EQUAL(2, kh4.m_y_shift);
  BOOST_REQUIRE_EQUAL(3, kh4.m_x_mask);
  BOOST_REQUIRE_EQUAL(3, kh4.m_y_mask);
}

BOOST_AUTO_TEST_CASE(karnaught_set) {
  kh::khmap_t kh(test4::arg_count);
  for(std::size_t i = 0; i < tools::size(test4::table); ++i)
    kh.set(i, test4::table[i]);
  BOOST_CHECK_EQUAL_COLLECTIONS(kh.m_array[0].cbegin(), kh.m_array[0].cend(), tools::begin(test4::map[0]), tools::end(test4::map[0]));
  BOOST_CHECK_EQUAL_COLLECTIONS(kh.m_array[1].cbegin(), kh.m_array[1].cend(), tools::begin(test4::map[1]), tools::end(test4::map[1]));
  BOOST_CHECK_EQUAL_COLLECTIONS(kh.m_array[2].cbegin(), kh.m_array[2].cend(), tools::begin(test4::map[2]), tools::end(test4::map[2]));
  BOOST_CHECK_EQUAL_COLLECTIONS(kh.m_array[3].cbegin(), kh.m_array[3].cend(), tools::begin(test4::map[3]), tools::end(test4::map[3]));
}

BOOST_AUTO_TEST_SUITE_END()
