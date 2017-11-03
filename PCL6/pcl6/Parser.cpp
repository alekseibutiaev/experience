//*****************************************************************************
//        File: PCL6Parser.cpp
//     Project: kopirkin
//  Created on: 27.11.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "templates/algorithm.hpp"

#include "ParserFunction.hpp"
#include "ParserErrno.hpp"
#include "Parser.hpp"

namespace pcl6 {


  extern const std::size_t MaxBuf;

  extern char* UnknownTag;

  extern char* errorbuf;


  namespace {

    template< int SELECTTAG >
    class CSelect {
    public:
      bool operator()( const COperatorPtr& f_Operator ) const {
        return f_Operator->Tag() == SELECTTAG;
      }
    };

    const std::size_t BYTES_PER_COMMAND = 5;

    bool PerseError( CBProgressShow f_ProgressShow, void* f_UserData ) {
      if( f_ProgressShow )
        f_ProgressShow( 0, static_cast< std::size_t >( -1 ), f_UserData );
      return false;
    }
  }; /* namespace */

  static COperatorsArray sOperators;

  bool Parser( const char* f_FileName, CBProgressShow f_ProgressShow,
      void* f_UserData ) {
    // set error status
    PCLErrno = 0;
    // open file
    std::filebuf file;
    file.open( f_FileName, std::ios::in | std::ios::binary );
    if( !file.is_open() ){
      PCLErrno = PCLErr::OpenError;
      return false;
    }
    // File size
    std::size_t filesize = 0;
    // get size of file
    filesize = file.pubseekoff( 0, std::ios_base::end );
    file.pubseekoff( 0, std::ios_base::beg );
    // clear old data
    sOperators.clear();
    std::size_t expectedCommandCount = filesize / BYTES_PER_COMMAND;
    if( sOperators.capacity() < expectedCommandCount )
      sOperators.reserve( expectedCommandCount );
    FileIperator begin( &file );
    const FileIperator end;

    COperatorPtr currentOperator;
    // Try reading header of the PCL or PJL file.
    if( !ReadPjl( begin, end, currentOperator ) ||
        currentOperator->Tag() != PjlTag::eHeader ) {
      PCLErrno = PCLErr::UnknownFormat;
      return false;
    }
    // store operators of head in to array
    sOperators.push_back( currentOperator );

    CDataTypePtr currentData;
    CAttributePtr currentAttribute;
    CAttributeArray attributes;

    // read file
    while( begin != end ) {
      // check call back function if exists call for shown progress
      if( f_ProgressShow )
        f_ProgressShow( filesize, file.pubseekoff( 0, std::ios_base::cur ),
            f_UserData );

      // Try reading data if current data is empty.
      if( !currentData.get() && ReadData( begin, end, currentData ) )
        continue;
      else if( PCLErrno != PCLErr::NoError )
        return PerseError( f_ProgressShow, f_UserData );
      // Try reading attribute
      if( ReadAttribute( begin, end, currentAttribute ) ){
        // Store current date in to new attribute
        currentAttribute->Data() = currentData;
        // Reset current data;
        currentData.reset();
        // Store attribute in to attribute list
        attributes.push_back( currentAttribute );
        continue;
        }
      else if( PCLErrno != PCLErr::NoError )
        return PerseError( f_ProgressShow, f_UserData );

      // Try reading pcl operator
      if( ReadPcl( begin, end, attributes, currentOperator ) ){
        // clear attributes set.
        attributes.clear();
        // store operators in to array
        sOperators.push_back( currentOperator );
        continue;
      }
      else if( PCLErrno != PCLErr::NoError )
        return PerseError( f_ProgressShow, f_UserData );

      // Try reading embed data
      if( ReadEmbedData( begin, end, currentOperator ) ){
        // store operators in to array
        sOperators.push_back( currentOperator );
        continue;
      }
      else if( PCLErrno != PCLErr::NoError )
        return PerseError( f_ProgressShow, f_UserData );

      // Try reading pjl operator
      if( ReadPjl( begin, end, currentOperator ) ) {
        // store operators in to array
        sOperators.push_back( currentOperator );
        continue;
      }
      else if( PCLErrno != PCLErr::NoError )
        return PerseError( f_ProgressShow, f_UserData );

      PCLErrno = PCLErr::UnknownTag;
      /// SIGSEG
      std::printf( "Unknown pcl6 tag: 0x%02X\n", ( *begin & 0x0ff ) );
      return PerseError( f_ProgressShow, f_UserData );
    }

    // Check last operator
    if( sOperators.back()->Tag() != PjlTag::eHeader ){
      PCLErrno = PCLErr::UnexpectedEnd;
      return PerseError( f_ProgressShow, f_UserData );
    }
    // check call back function if exists call for shown progress 100%
    if( f_ProgressShow )
      f_ProgressShow( filesize, filesize, f_UserData );

    return true;
  }
//*****************************************************************************
  bool StartParser(){
    return true;
  }
//*****************************************************************************
  void FinishParser(){
    sOperators = COperatorsArray();
  }
//*****************************************************************************
  bool StuffInfo( CStuffInfo& f_StuffInfo ){
    typedef COperatorsArray::iterator::difference_type CCountType;
    if( sOperators.empty() ){
      PCLErrno = PCLErr::NotDisassembled;
      return false;
    }

    COperatorsArray::iterator begin = sOperators.begin();
    COperatorsArray::iterator end = sOperators.end();

#if 0
    typedef std::vector< int > CPosition;
    CPosition begpos;
    COperatorsArray::iterator i = begin;
    while( ( i = std::find_if( i, end, CSelect< PclTag::eBeginPage >() ) ) != end )
    {
      int d = std::distance( sOperators.begin(), i );
      begpos.push_back( d );
      ++i;
    }
    CPosition endpos;
    i = begin;
    while( ( i = std::find_if( i, end, CSelect< PclTag::eEndPage >() ) ) != end )
    {
      int d = std::distance( sOperators.begin(), i );
      endpos.push_back( d );
      ++i;
    }
    std::cout << std::endl;
    std::copy( begpos.begin(), begpos.end(), std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << std::endl;
    std::copy( endpos.begin(), endpos.end(), std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << std::endl;
#endif

    CCountType countBeinPage = std::count_if( begin, end,
        CSelect< PclTag::eBeginPage >() );
    // get all end pages operator
    COperatorsArray endpages;
    templates::copy_if( begin, end, std::back_inserter( endpages ),
        CSelect< PclTag::eEndPage >() );
    // check begin & end pages operator.
    if( (std::size_t)countBeinPage != endpages.size() ){
      PCLErrno = PCLErr::UncorrectPageCount;
      return false;
    }
    // set page and sheets count operator.
    std::size_t pages = countBeinPage;
    std::size_t sheets = countBeinPage;

    // find DUPLEX operator
    while( ( begin = std::find_if( begin, end, CSelect< PjlTag::ePJL >() ) )
        != end ) {
      CPjlOperator* pjl;
      if( ( pjl = dynamic_cast< CPjlOperator* >( begin->get() ) ) ){
        if( pjl->Command() == "SET" && pjl->Parameter() == "DUPLEX" &&
            pjl->Value() == "ON" ){
          sheets = sheets % 2 ? sheets / 2 + 1 : sheets / 2;
          break;
          }
        // repeat from next position
        ++begin;
      }
    }

    f_StuffInfo = CStuffInfo( pages, sheets );

    return true;
  }

}; //* namespace pcl6 */

#if 0
{ // for debug
  int curtag = *begin & 0x0ff;
  std::size_t curpos = file.pubseekoff( 0, std::ios_base::cur );
  std::cout << std::hex << "in position 0x" << curpos << " tag 0x" << curtag << std::endl;
  if( curpos == 0x410 )
    curpos = 0;
  if( curtag == 0xc8 )
    curtag = 0;
}
#endif
#if 0
    typedef std::vector< int > CPosition;
    CPosition begpos;
    COperatorsArray::iterator i = begin;
    while( ( i = std::find_if( i, end, CSelect< PclTag::eBeginPage >() ) ) != end )
    {
      int d = std::distance( sOperators.begin(), i );
      begpos.push_back( d );
      ++i;
    }
    CPosition endpos;
    i = begin;
    while( ( i = std::find_if( i, end, CSelect< PclTag::eEndPage >() ) ) != end )
    {
      int d = std::distance( sOperators.begin(), i );
      endpos.push_back( d );
      ++i;
    }
    std::cout << std::endl;
    std::copy( begpos.begin(), begpos.end(), std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << std::endl;
    std::copy( endpos.begin(), endpos.end(), std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << std::endl;
#endif

