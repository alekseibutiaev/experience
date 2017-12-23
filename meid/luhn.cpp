#include <iostream>
#include <iterator>

template<unsigned int... S>
struct luhn_data
{
  static const unsigned int data[2][sizeof...(S)];
  static const unsigned int size = sizeof...(S);
};

template<unsigned int... S>
const unsigned int luhn_data<S...>::data[2][sizeof...(S)] = {
  {S...},
  {S * 2 % luhn_data<S...>::size + S * 2 / luhn_data<S...>::size ...}
};

template<unsigned int I, unsigned int... S>
struct luhn : luhn<I - 1, I - 1, S...>
{};

template<unsigned int... S>
struct luhn<0, S...> : luhn_data<S...>
{

  using luhn_data<S...>::data;
  using luhn_data<S...>::size;

  static int get_cb(unsigned long long value)
  {
    int sum = 0;
    int index = 0;
    while(value){
      sum += data[++index % 2][value % size];
      value /= size;
    }
    return size - sum % size;
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
    std::cout << "hex table" << std::endl << "0x" << std::hex;

  std::copy(std::begin(luhn16::data[0]), std::end(luhn16::data[0]), std::ostream_iterator<int>(std::cout, " 0x"));
  std::cout << std::endl << "0x";
  std::copy(std::begin(luhn16::data[1]), std::end(luhn16::data[1]), std::ostream_iterator<int>(std::cout, " 0x"));

  std::cout << std::dec << std::endl;

  std::cout << std::endl;
  std::cout << "IMEI 35948605448562/" << luhn10::get_cb(35948605448562) << std::endl;

  std::cout << std::endl;
  std::cout << "MEID A000001D4FEC64/" << luhn16::get_cb(0xA000001D4FEC64) << std::endl;

  return 0;
}

