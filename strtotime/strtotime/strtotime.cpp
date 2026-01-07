#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>


int main()
{
  struct std::tm tm = {0};
  const std::string d = __DATE__;
  std::istringstream ss(__DATE__);
  ss >> std::get_time(&tm, "%b %e %Y"); // or just %T in this case
  std::time_t time = mktime(&tm);
  return 0;
}

