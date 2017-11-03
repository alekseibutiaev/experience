//*****************************************************************************
//    Project : pu40
//       File : chartype.c
// Created on : Sep 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************
#include <ctype.h>

#include "chartype.h"

//*****************************************************************************
int wiscntrl( int f_Char ) {
  return f_Char > 255 ? 0 : iscntrl( f_Char );
}
//*****************************************************************************
int wisspace( int f_Char ){
  return f_Char > 255 ? 0 : isspace( f_Char );
}
//*****************************************************************************
int wisupper( int f_Char ){
  return f_Char > 255 ? 0 : isupper( f_Char );
}
//*****************************************************************************
int wislower( int f_Char ){
  return f_Char > 255 ? 0 : islower( f_Char );
}
//*****************************************************************************
int wisalpha( int f_Char ){
  return f_Char > 255 ? 0 : isalpha( f_Char );
}
//*****************************************************************************
int wisdigit( int f_Char ){
  return f_Char > 255 ? 0 : isdigit( f_Char );
}
//*****************************************************************************
int wisxdigit( int f_Char ){
  return f_Char > 255 ? 0 : isxdigit( f_Char );
}
//*****************************************************************************
int wisalnum( int f_Char ){
  return f_Char > 255 ? 0 : isalnum( f_Char );
}
//*****************************************************************************
int wispunct( int f_Char ){
  return f_Char > 255 ? 0 : ispunct( f_Char );
}
//*****************************************************************************
int wisgraph( int f_Char ){
  return f_Char > 255 ? 0 : isgraph( f_Char );
}
//*****************************************************************************
int wisprint( int f_Char ){
  return f_Char > 255 ? 0 : isprint( f_Char );
}
//*****************************************************************************
int wtolower( int f_Char ) {
  return f_Char > 255 ? ' ' : tolower( f_Char );
}
int wtoupper( int f_Char ) {
  return f_Char > 255 ? ' ' : toupper( f_Char );
}
//*****************************************************************************

