#include <iostream>
#include <cinttypes>
#include <array>

using std::uint64_t;

// Helper template that computes the factorial of one integer
template<uint64_t I> struct Factorial
{ static constexpr uint64_t value = I * Factorial<I-1>::value; };

template<> struct Factorial<0> { static constexpr uint64_t value = 1; };

// FactorialArray recursively assembles the desired array as a variadic
// template argument pack from a series of invocations of Factorial
template<uint64_t I, uint64_t... Values> struct FactorialArray
  : FactorialArray<I-1, Factorial<I>::value, Values...>
{};

// and in the base case, initializes a std::array with that pack
template<uint64_t... Values> struct FactorialArray<uint64_t(-1), Values...>
  : std::array<uint64_t, sizeof...(Values)>
{
  constexpr FactorialArray()
    : std::array<uint64_t, sizeof...(Values)> ({{Values...}})
  {}
};

template<int... S>
struct luhn
{
  static const unsigned int data[2][sizeof...(S)];
  static const unsigned int size = sizeof...(S);
};

template<int... S>
const unsigned int luhn<S...>::data[2][sizeof...(S)] = {
  {S...},
  {S * 2 % luhn<S...>::size + S * 2 / luhn<S...>::size ...}
};

using luhn10 = luhn<0,1,2,3,4,5,6,7,8,9>;

int main(int, char**)
{
  static FactorialArray<10> f;
  for (std::size_t i = 0; i < f.size(); i++)
    std::cout << i << "! = " << f[i] << '\n';

  std::cout << data0<10, 5>::value << std::endl;
  std::cout << data1<10, 6>::value << std::endl;

  for(int i = 0; i < luhn10::size; ++i)
    std::cout << luhn10::data[0][i] << " " << luhn10::data[1][i] << std::endl;

  return 0;
}

