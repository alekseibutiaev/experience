/*
 * Parser.hpp
 *
 *  Created on: 27.11.2009
 *      Author: alexsy
 */

#ifndef __PCL6PARSER_HPP__
#define __PCL6PARSER_HPP__

#include <utility>

#include "ParserErrno.hpp"

namespace pcl6 {

  // CStuffInfo: Quantity of pages and sheets of paper
  // first: pages.
  // second: sheets.
  typedef std::pair< std::size_t, std::size_t > CStuffInfo;
  // call back for shown progress
  typedef void (*CBProgressShow)( std::size_t f_FileSize,
      std::size_t f_CurPosition, void* f_UserData );

  // Disassemble PCL6 file.
  bool Parser( const char* f_FileName, CBProgressShow f_ProgressShow = 0,
      void* f_UserData = 0 );
  bool StartParser();
  // Finish parser
  void FinishParser();
  // get stuff info
  bool StuffInfo( CStuffInfo& f_StuffInfo );

}; //* namespace pcl6 */

#endif /* __PCL6PARSER_HPP__ */
