/*
 ============================================================================
 Name        : nested.c
 Author      : Butyaev A
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

const int th1 = 10;

int main(void) {
  auto void nested();

  if( 5 < th1 )
    nested();

  void nested() {
    printf( "%s\n", __FUNCTION__ );
  };
  return 0;
}
