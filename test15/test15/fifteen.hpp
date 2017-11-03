#pragma once

#ifndef __FIFTEEN_HPP__
#define __FIFTEEN_HPP__

#include <vector>

class fifteen {
public:
  enum direction {
    e_left, e_right, e_top, e_bottom, e_COUNT
  };
  typedef std::vector< int > field;
  typedef field::iterator iterator;
  typedef field::const_iterator const_iterator;

public:
  fifteen();
  int select( const unsigned int& f_pos );
  unsigned int can_move( const fifteen::direction& f_direction );
  void move( const unsigned int& f_from, const unsigned int& f_to );
  bool ready() const;
  const_iterator begin() const;
  const_iterator end() const;
public:
  static const unsigned int max_pieces = 16;
  static const int unused_cell = -1;
  static const unsigned int field_width = 4;
  static const unsigned int field_height = 4;
private:
  std::vector< unsigned int > pv_can_be_selected( const unsigned int& f_to );
private:
  std::vector< int > pv_field;
  unsigned int pv_selected;
//  unsigned int pv_to;
private:
  static const int pv_last_cell = 15;
  static const unsigned int pv_mix_count = 100;

};

#endif /* __FIFTEEN_HPP__ */