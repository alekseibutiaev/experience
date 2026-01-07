/*
 * CTag.hpp
 *
 *  Created on: 27.11.2009
 *      Author: alexsy
 */

#ifndef __CTAG_HPP__
#define __CTAG_HPP__

#include <memory>
#include <iterator>
#include <string>

#include <vector>
#include <boost/smart_ptr.hpp>

namespace pcl6{

  const int StringTag = 256;
  const int InvalidTag = 257;

//  const bool Tested = true;
#ifdef OPERATOR_NAME_PRINT
  #define OPERATOR_NAME std::cout << __FUNCTION__ << std::endl
#else
  #define OPERATOR_NAME
#endif

  class CBaseTag;
  class CBaseOperator;
  class CStringOperator;

  typedef unsigned char Byte;
  typedef std::istreambuf_iterator< char, std::char_traits< char > > FileIperator;

  typedef boost::shared_ptr< CBaseTag > CTagPtr;
  typedef boost::shared_ptr< CStringOperator > CStringOperatorPtr;

//******************************************************************************
  // Base tag
  class CBaseTag {
  public:
    const int Tag() const {
      return pvTag;
    }
  protected:
    CBaseTag( const int& f_Tag ) : pvTag( f_Tag ) {}
    virtual ~CBaseTag(){};
  private:
    int pvTag;
  };
//******************************************************************************
  class CBaseWhiteSpace : public CBaseTag {
  public:
    virtual ~CBaseWhiteSpace(){};
  };

}; /* namespace pcl6 */

#endif /* __CTAG_HPP__ */

