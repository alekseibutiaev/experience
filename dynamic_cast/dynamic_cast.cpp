// dynamic_cast.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class base1 {
public:
  virtual ~base1() {
  }
  virtual void foo1(){
  }
};

class base2 {
public:
  virtual ~base2() {
  }
  virtual void foo2(){
  }
};

class derived1 : public base1, public base2 {
public:
  void foo1(){
  }
  void foo2(){
  }
};

class derived2 : public base1 {
public:
  void foo1(){
  }
};

#if defined( WIN32 ) || defined( WIN64 )
int _tmain( int ac, _TCHAR* av[] ) {
#else
int main( int ac, char* av[] ) {
#endif
  derived1 d1;
  derived2 d2;
  base1* db1a = &d1;
  base1* db2a = &d2;

  base2* dp1 = dynamic_cast< base2* >( db1a );
  base2* dp2 = dynamic_cast< base2* >( db2a );
	return 0;
}

