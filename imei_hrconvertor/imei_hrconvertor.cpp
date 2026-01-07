//imei=511481816272963923 => 359850080062917
//imsi=444034490731335810 => 280101844078926

#include <iostream>

class human_format
{
  union convert_type {
    struct {
      unsigned char l :4;
      unsigned char h :4;
    } a[sizeof(unsigned long long)];
    unsigned long long b;
  };
public:
  static unsigned long long convert(const unsigned long long value){
    convert_type data;
    data.b = value;
    unsigned long long res = 0;
    for(unsigned long index = 0; index < sizeof(unsigned long long); ++index)
      res = res * 100 + data.a[index].l * 10 + data.a[index].h;
    return res / 10;
  }
};

int main(int, char**) {
  unsigned long long a = 511481816272963923;
  std::cout << a << " " << human_format::convert(a) <<std::endl;
  unsigned long long b = 444034490731335810;
  std::cout << b << " " << human_format::convert(b) <<std::endl;

  return 0;
}
