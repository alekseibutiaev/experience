#pragma once

#ifndef __ARRAY_HELP_HPP__
#define __ARRAY_HELP_HPP__

template < typename TYPE, unsigned int SIZE >
unsigned int array_size( TYPE(&array)[SIZE] ) {
  return SIZE;
}

template < typename TYPE, unsigned int SIZE >
TYPE* array_begin( TYPE (&f_array)[SIZE] ) {
  return &f_array[ 0 ];
}

template < typename TYPE, unsigned int SIZE >
TYPE* array_end( TYPE (&f_array)[SIZE] ) {
  return &f_array[ SIZE ];
}

#endif /* __ARRAY_HELP_HPP__ */