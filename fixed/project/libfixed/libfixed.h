#pragma once
#include <iostream>
#include <string>

namespace fp {

  class fix_pount_t {
  public:
    enum {
      max_int = 576460752303423487,
      max_dec_exp = 7
    };
    union value_t {
      struct {
        long long significand : 60;
        int exp : 4;
      };
      unsigned long long value;
    };
  public:
    fix_pount_t();
    fix_pount_t(int value);
    fix_pount_t(long long value);
    fix_pount_t(double value);
    operator double() const;
  private:
  private:
    value_t m_value;  
  };

  std::ostream& operator<<(std::ostream& os, int);

} /* namespace fp */
