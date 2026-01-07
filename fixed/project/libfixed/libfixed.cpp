#include <cmath>
#include <iostream>
#include <libfixed.h>

namespace {

  const unsigned int exp[] = { 1, 10, 100, 1000, 10000, 10000, 1000000, 100000000 };

/*
  fp::fix_pount_t::value_t get() {
    fp::fix_pount_t::value_t res;
    res.exp = 1;
    res.significand = 0;
    return res;
  }
*/

  fp::fix_pount_t::value_t get(long long value = 0) {
    fp::fix_pount_t::value_t res;
    res.exp = 1;
    while(value > fp::fix_pount_t::max_int) {
      ++res.exp;
      value /= 10;
    }
    res.significand = value;
    return res;
  }

  fp::fix_pount_t::value_t get(double value) {
    fp::fix_pount_t::value_t res;
    const auto sign = 0.0 < value;
    const auto fraction  = 1 < value;
    std::cout << sign << " " << fraction << std::endl;
    return res;
  }

} /* namespace */

namespace fp {

  fix_pount_t::fix_pount_t()
    : m_value(get()) {
  }

  fix_pount_t::fix_pount_t(int value)
    : m_value(get(static_cast<long long>(value))) {
  }

  fix_pount_t::fix_pount_t(long long value)
    : m_value(get(value)) {
  }

  fix_pount_t::fix_pount_t(double value)
    : m_value(get(value)) {
  }

  fix_pount_t::operator double() const {
    return std::pow(static_cast<double>(m_value.significand), static_cast<double>(m_value.exp));
  };


} /* namespace fp */
