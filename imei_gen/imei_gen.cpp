#include <iostream>
#include <type_traits>
#include <algorithm>
#include <string>
#include <chrono>
#include <cmath>
#include <random>

const std::size_t imeilenght = 14;

typedef char(&imei_t)[imeilenght + 2];

void calculate_crc(imei_t imei) {

  static const int table [2][10] = {
    {0,1,2,3,4,5,6,7,8,9},
    {0,2,4,6,8,1,3,5,7,9}
  };

  int sum = 0;
  int i;
  for(i = 0; i < imeilenght; ++i)
    sum += table[i%2][imei[i] - '0'];

  sum %= 10;
  imei[i++] = ( 0 == sum ? 0 : 10 - sum) + '0';
  imei[i] = 0;
}

int main(int ac, char* av[])
{
  unsigned int seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  std::minstd_rand0 g1(seed1);
  std::size_t start_from = 0;
  int count = 0;
  std::remove_reference<imei_t>::type result = {0};

  if(ac > 1) {
    try{
      count = std::stoi(av[1]);
    }
    catch(...){
    }
  }

  if(ac > 2) {
    try {
      unsigned long long imsi = std::stoll(av[2], &start_from, 10);
      start_from = std::min(imeilenght, start_from);
      if(imsi){
        for(std::size_t index = start_from; index > 0;) {
          result[--index] = imsi % 10 + '0';
          imsi /= 10;
        }
        result[start_from] = 0;
      }
    }
    catch(...){
    }
  }

  if(0 == count)
      ++count;

  while(count--) {
    for(std::size_t index = start_from; index < imeilenght; ++index)
      result[index] = g1() % 10 + '0';
    calculate_crc(result);
    std::cout << result << std::endl;
  }
  return 0;
}
//06722291398750

