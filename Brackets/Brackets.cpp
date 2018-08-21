#include <iostream>
#include <string>
#include <vector>


bool resolve(const std::string& value) {
  std::vector <std::string::value_type> stack;
  for(const std::string::value_type i : value) {
    if(i == '{' || i == '(' || i == '[') {
      stack.push_back(i);
      continue;
    }
   
    if((i == ']' || i == '}' || i == ')') && stack.empty())
      return false;
    if(i == ']') {
      const std::string::value_type tmp = stack.back();
      stack.pop_back();
      if(tmp == '{' || tmp == '(')
        return false;
    }
    else if(i == '}') {
      const std::string::value_type tmp = stack.back();
      stack.pop_back();
      if(tmp == ']' || tmp == '(')
        return false;
    }
    else if(i == ')') {
      const std::string::value_type tmp = stack.back();
      stack.pop_back();
      if(tmp == '{' || tmp == '[')
        return false;
    }
  }
  return stack.empty();
}

int main()
{
  std::cout << resolve("[{3 + 4} * (8-10)]") << std::endl;
  std::cout << resolve("[{{3 + 4} * (8-10)]") << std::endl;
  std::cout << resolve("") << std::endl;
  std::cout << resolve("d") << std::endl;

  return 0;
}

