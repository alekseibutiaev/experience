#include <iostream>
#include <iterator>

template<unsigned int... S>
struct luhn_data
{
  static const unsigned int size = sizeof ...(S);
  static const unsigned int data[2][size];
};

template<unsigned int... S>
const unsigned int luhn_data<S ...>::data[2][luhn_data<S ...>::size] = {
  {S...},
  {S * 2 % luhn_data<S ...>::size + S * 2 / luhn_data<S ...>::size ...}
};

template<unsigned int I, unsigned int... S>
struct luhn : luhn<I - 1, I - 1, S ...>
{};

template<unsigned int... S>
struct luhn<0, S ...> : luhn_data<S...>
{

  using luhn_data<S ...>::data;
  using luhn_data<S ...>::size;

  static unsigned int get_cb(unsigned long long value)
  {
    unsigned int sum = 0;
    int index = 0;
    while(value){
      sum += data[++index % 2][value % size];
      value /= size;
    }
    return (size - sum % size) % size;
  }

};

using luhn10 = luhn<10>;
using luhn16 = luhn<16>;

int main(int, char**)
{
  std::cout << "dec table" << std::endl;

  std::copy(std::begin(luhn10::data[0]), std::end(luhn10::data[0]), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  std::copy(std::begin(luhn10::data[1]), std::end(luhn10::data[1]), std::ostream_iterator<int>(std::cout, " "));

  std::cout << std::endl;
  std::cout << "IMEI 35948605448562/" << luhn10::get_cb(35948605448562) << std::endl;
  std::cout << "IMEI 33075934001217/" << luhn10::get_cb(33075934001217) << std::endl;
  std::cout << "MEID 268435458312832709/" << luhn10::get_cb(268435458312832709) << std::endl;
  std::cout << "MEID 268435458905237860/" << luhn10::get_cb(268435458905237860) << std::endl;
  std::cout << "MEID 293608736500703710/" << luhn10::get_cb(293608736500703710) << std::endl;

  std::cout << std::endl;
  std::cout << "hex table" << std::endl << "0x" << std::hex;

  std::copy(std::begin(luhn16::data[0]), std::end(luhn16::data[0]), std::ostream_iterator<int>(std::cout, " 0x"));
  std::cout << std::endl << "0x";
  std::copy(std::begin(luhn16::data[1]), std::end(luhn16::data[1]), std::ostream_iterator<int>(std::cout, " 0x"));

  std::cout << std::endl;
  std::cout << "MEID A000001D4FEC64/" << luhn16::get_cb(0xA000001D4FEC64) << std::endl;
  std::cout << "MEID A0000017C3CFC5/" << luhn16::get_cb(0xA0000017C3CFC5) << std::endl;
  std::cout << "MEID AF0123450ABCDE/" << luhn16::get_cb(0xAF0123450ABCDE) << std::endl;

  return 0;
}

