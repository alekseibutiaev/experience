// exe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windll/windll_template.hpp>


int main( int ac, char* av[] ) {
  windll::test2 t2;
  t2.begin();
  windll::keepvector pv;
  std::vector< double >::iterator it = pv.begin();
  
  return 0;
}

