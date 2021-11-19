#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>

#include <libfixed/libfixed.h>

namespace {

  double align(double val, double step, bool down = false) {
    const double dx = down? 0.0: val > 0 ? 0.5 : -0.5;
    if (step == 0)
      modf(val + dx, &val);
    else if (step < 1.0) {
      double n;
      const auto f = modf(val, &n);
      double n2;
      modf((f / step) + dx, &n2);
      double m_val2 = n + (n2 * step);    //abz
      if(val - m_val2 > step / 2)         //abz
        val = n + (n2 * step) + step;     //abz
      else
        val = n + n2 * step;            //abz
    }
    else {
      modf((val / step) + dx, &val);
      val *= step;
    }
    return val;
  }

} /* namespace */


int main(int ac, char* av[]) {
    std::size_t m_dec;
    const char* src = "6578364578.8898";
    if(const char* pp = std::strchr(src, '.'))
      m_dec =  std::strlen(src) - std::size_t(pp - src) - 1;
    std::cout << m_dec << std::endl;
  double a = 200041753.42;
  double b;
  double c = std::modf(a, &b);
  std::cout << a << " " << b << " " << c << std::endl;

  double ss = align(a, 1/std::pow(10, 8));
  std::cout << std::fixed << std::setprecision(8) << a << " " << b << " " << c << " " << ss << std::endl;
  std::cout << std::fixed << std::setprecision(10) << ss << std::endl;
  std::cout << std::fixed << std::setprecision(8) << ss << std::endl;
  std::cout << std::fixed << std::setprecision(6) << ss << std::endl;
  std::cout << std::fixed << std::setprecision(4) << ss << std::endl;
  std::cout << std::fixed << std::setprecision(2) << ss << std::endl;

  printf("%.10f %.8f %.6f %.4f %.2f\n", ss, ss, ss, ss, ss);

#if 0
  std::cout << "project" << std::endl;
  {
    fp::fix_pount_t a;
    std::cout << sizeof a << ' ' << static_cast<double>(a) << std::endl;
  }
  {
    fp::fix_pount_t a(88343434);
    auto r = static_cast<double>(a);
    std::cout << std::fixed << sizeof a << ' ' << static_cast<double>(a) << " " << r << std::endl;
  }
  {
    fp::fix_pount_t a(static_cast<long long>(9223372036854775807));
  }
#endif
  return 0;
}