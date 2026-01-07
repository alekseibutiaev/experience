//============================================================================
// Name        : ladder.cpp
// Author      : Butyaev A.Y.
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <iostream>
#include <boost/smart_ptr.hpp>

class CLog {
public:
  CLog( const char* f_FuncName ) : pvFuncName( f_FuncName ) {
    std::cout << "Enter: " << pvFuncName << std::endl;
  }
  ~CLog() {
    std::cout << "Leave: " << pvFuncName << std::endl;
  }
private:
  const char* pvFuncName;
};

class CBaseLadder {
public:
  enum STEP {
    eStep0,
    eStep1,
    eStep2,
    eStep3,
    eStep4,
    eStep5,
    eEnd
  };
  typedef boost::scoped_ptr< CBaseLadder > CLadderPtr;
public:
  CBaseLadder( const CBaseLadder::STEP f_Curent ) : ptCurent( f_Curent ) {
  }
  virtual ~CBaseLadder() {
  }
  virtual const CBaseLadder::STEP Next() = 0;
protected:
  const CBaseLadder::STEP ptCurent;
};

template< CBaseLadder::STEP CURRENT >
class CLadder : public CBaseLadder {
public:
  CLadder() : CBaseLadder( CURRENT ) {
  }
  const CBaseLadder::STEP Next();
};

template<>
const CBaseLadder::STEP CLadder< CBaseLadder::eStep0 >::Next() {
  CLog l( __PRETTY_FUNCTION__ );
  CLadderPtr next( new CLadder< CBaseLadder::eStep1 >() );
  CBaseLadder::STEP returnTo;
  while( ptCurent == ( returnTo = next->Next() ) ) {
  }
  return returnTo;
}

template<>
const CBaseLadder::STEP CLadder< CBaseLadder::eStep1 >::Next() {
  CLog l( __PRETTY_FUNCTION__ );
  CLadderPtr next( new CLadder< CBaseLadder::eStep2 >() );
  CBaseLadder::STEP returnTo;
  while( ptCurent == ( returnTo = next->Next() ) ) {
  }
  return returnTo;
}

template<>
const CBaseLadder::STEP CLadder< CBaseLadder::eStep2 >::Next() {
  CLog l( __PRETTY_FUNCTION__ );
  CLadderPtr next( new CLadder< CBaseLadder::eStep3 >() );
  CBaseLadder::STEP returnTo;
  while( ptCurent == ( returnTo = next->Next() ) ) {
  }
  return returnTo;
}

template<>
const CBaseLadder::STEP CLadder< CBaseLadder::eStep3 >::Next() {
  CLog l( __PRETTY_FUNCTION__ );
  CLadderPtr next( new CLadder< CBaseLadder::eStep4 >() );
  CBaseLadder::STEP returnTo;
  int count = 3;
  while( ptCurent == ( returnTo = next->Next() ) ) {
    if( 0 == --count )
      return CBaseLadder::eEnd;
  }
  return returnTo;
}

template<>
const CBaseLadder::STEP CLadder< CBaseLadder::eStep4 >::Next() {
  CLog l( __PRETTY_FUNCTION__ );
  CLadderPtr next( new CLadder< CBaseLadder::eStep5 >() );
  CBaseLadder::STEP returnTo;
  while( ptCurent == ( returnTo = next->Next() ) ) {
  }
  return returnTo;
}

template<>
const CBaseLadder::STEP CLadder< CBaseLadder::eStep5 >::Next() {
  CLog l( __PRETTY_FUNCTION__ );
  return CBaseLadder::eStep3;
}

int main() {
  CBaseLadder::CLadderPtr begin( new CLadder< CBaseLadder::eStep0 >() );
  begin->Next();
  return EXIT_SUCCESS;
}

