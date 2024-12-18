#include <iostream>

class base
{
public:
  virtual ~base() {}
  virtual void print() const = 0;
};

class parent_a : public base {
public:
  virtual void method_a() const = 0;
};

class parent_b : public base {
public:
  virtual void method_b() const = 0;
};

class child_a : public parent_a {
public:
  void print() const {
    std::cout << "class name: " << "child_a function: " << __FUNCTION__ << std::endl;
  }
  void method_a() const {
    std::cout << "class name: " << "child_a function: " << __FUNCTION__ << std::endl;
  }
};

class child_b : public parent_b {
public:
  void print() const {
    std::cout << "class name: " << "child_b function: " << __FUNCTION__ << std::endl;
  }
  void method_b() const {
    std::cout << "class name: " << "child_b function: " << __FUNCTION__ << std::endl;
  }
};

void print(const base* value) {
  value->print();
  if(const parent_a* p = dynamic_cast<const parent_a*>(value))
    p->method_a();
  else
    std::cout << std::hex << "class: 0x" << value << " can`t by cast to parent_a" << std::endl;
  if (const parent_b* p = dynamic_cast<const parent_b*>(value))
    p->method_b();
  else
    std::cout << std::hex << "class: 0x" << value << " can`t by cast to parent_b" << std::endl;
}

int main()
{
  child_a a;
  child_b b;
  print(&a);
  print(&b);
  return 0;
}
