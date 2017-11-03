//============================================================================
// Name        : VirtualInheritance.cpp
// Author      : Butyaev A.Y.
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/shared_ptr.hpp>

class CInterface {
public:
  virtual ~CInterface(){}
  virtual void foo() = 0;
  virtual void check() = 0;
  void SetValue( int f_Value ) {
    ptValue = f_Value;
  }
protected:
  CInterface() : ptValue( 0 ) {
  }
  int ptValue;
};

class CObject1 : public virtual CInterface {
public:
  void foo() {
    ++ptValue;
    std::cout << "CObject1::foo " << ptValue << std::endl;
  }
  void check() {}
};

class CObject2 : public virtual CInterface {
public:
  void foo() {
    ++ptValue;
    std::cout << "CObject2::foo " << ptValue << std::endl;
  }
  void check() {}
};

class CObject3 : public virtual CInterface, public CObject1, public CObject2 {
public:
  CObject3() : pvFlag( false ) {
  }
  void foo() {
    if( pvFlag ) {
      CObject2::foo();
      pvFlag = false;
    }
    else {
      CObject1::foo();
      pvFlag = true;
    }
  }
  void check() {}
private:
  bool pvFlag;
};

int main() {
  std::cout << "!!!Hello World!!!" << std::endl;
  boost::shared_ptr< CObject3 > obj3( new CObject3 );
  CInterface* f = obj3.get();
  for( int i = 0; i < 10; i++ ) {
    f->SetValue( i * i );
    f->foo();
  }
  return 0;
}
