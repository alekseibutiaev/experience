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

using luhn_data10 = luhn_data<0,1,2,3,4,5,6,7,8,9>;


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
    	sum += data[++index % 2][value % 16];
    	value /= size;
  	}
		return size - sum % size;		
	}

};

using luhn10 = luhn<10>;


int main(int, char**)
{
  static FactorialArray<10> f;
  for (std::size_t i = 0; i < f.size(); i++)
    std::cout << i << "! = " << f[i] << '\n';

  for(int i = 0; i < luhn_data10::size; ++i)
    std::cout << luhn_data10::data[0][i] << " " << luhn_data10::data[1][i] << std::endl;

	std::cout << std::endl;

  for(int i = 0; i < luhn10::size; ++i)
    std::cout << luhn10::data[0][i] << " " << luhn10::data[1][i] << std::endl;

	std::cout << std::endl;

	std::cout << luhn10::get_cb(35948605448562) << std::endl;

  return 0;
}

