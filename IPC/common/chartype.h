//*****************************************************************************
//    Project : pu40
//       File : chartype.h
// Created on : Sep 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CHARTYPE_HPP__
#define __CHARTYPE_HPP__

#ifdef __cplusplus
extern "C" {
#endif

  int wiscntrl( int f_Char );
  int wisspace( int f_Char );
  int wisupper( int f_Char );
  int wislower( int f_Char );
  int wisalpha( int f_Char );
  int wisdigit( int f_Char );
  int wisxdigit( int f_Char );
  int wisalnum( int f_Char );
  int wispunct( int f_Char );
  int wisgraph( int f_Char );
  int wisprint( int f_Char );
  int wtolower( int f_Char );
  int wtoupper( int f_Char );

#ifdef __cplusplus
}
#endif

#endif /* __CHARTYPE_HPP__ */
