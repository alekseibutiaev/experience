//============================================================================
// Name        : singleton.cpp
// Author      : Butyaev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cassert>
#include <new>
#include <stdexcept>
#include <iostream>
#include <boost/smart_ptr.hpp>

template< typename OBJECT >
class CSingleton : public OBJECT {
public:
  typedef boost::shared_ptr< CSingleton< OBJECT > > CSingletonPtr;
public:
  static CSingletonPtr Instance( CSingletonPtr* f_ExternalInstance = 0L ) {
    assert( 0L != pvExternalInstance || 0L != f_ExternalInstance );
    if( 0L == pvExternalInstance && 0L != f_ExternalInstance ) {
      *f_ExternalInstance = CSingletonPtr( new CSingleton< OBJECT >(), CSingleton::CDeliter() );
      pvExternalInstance = f_ExternalInstance;
    }
    return *pvExternalInstance;
  }
protected:
  CSingleton(){
    std::cout << __FUNCTION__ << std::endl;
  }
  virtual ~CSingleton(){
    std::cout << __FUNCTION__ << std::endl;
  };
private:
  class CDeliter {
  public:
    void operator()( CSingleton< OBJECT >* f_Object ) {
      delete f_Object;
    }
  };
  friend class CDeliter;
private:
  static CSingletonPtr* pvExternalInstance;
};

template< typename OBJECT >
typename CSingleton< OBJECT >::CSingletonPtr* CSingleton< OBJECT >::pvExternalInstance = 0L;


class CTest0 {
public:
  CTest0() {
    std::cout << __FUNCTION__ << std::endl;
  }
  ~CTest0() {
    std::cout << __FUNCTION__ << std::endl;
  }
  void Foo() {
    std::cout << "CTest0::" << __FUNCTION__ << std::endl;
  }
};

typedef CSingleton< CTest0 > CTest0Singleton;
typedef CTest0Singleton::CSingletonPtr CTest0SingletonPtr;

class CTest1 {
public:
  CTest1() {
    std::cout << __FUNCTION__ << std::endl;
  }
  ~CTest1() {
    std::cout << __FUNCTION__ << std::endl;
  }
  void Foo() {
    std::cout << "CTest1::" << __FUNCTION__ << std::endl;
    CTest0Singleton::Iinstance()->Foo();
  }
};

typedef CSingleton< CTest1 > CTest1Singleton;
typedef CTest1Singleton::CSingletonPtr CTest1SingletonPtr;

int main() {
  CTest0SingletonPtr ptr0;
  CTest1SingletonPtr ptr1;
  ptr0 = CTest0Singleton::Iinstance( &ptr0 );
  ptr0->Foo();
  ptr1 = CTest1Singleton::Iinstance( &ptr1 );
  ptr1->Foo();
  return 0;
}
