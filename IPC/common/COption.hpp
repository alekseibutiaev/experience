//*****************************************************************************
//    Project : pu40
//       File : CClassName.hpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __COPTION_HPP__
#define __COPTION_HPP__

#include <getopt.h>

#include <string>
#include <vector>

#include "EArgument.hpp"

namespace common {

  struct SOptionData {
    int Short;
    std::string Long;
    std::string Description;
    std::string DefaultValue;
  };

  class COption {
  public:
    enum { eWithoutShort = 256 };
  public:
    COption( const std::string& f_LongOption = std::string(),
        const int& f_ShortOption = 0,
        const EArgument::FLAG& f_ArgFlag = EArgument::eWithoutArg,
        const std::string& f_DefaultValue = std::string(),
        const std::string& f_Description = std::string() );
    ~COption();
    void Update( const char* f_OptArg );
    int& ShortOption();
    const int& ShortOption() const;
    const std::string& LongOption() const;
    const char* Short() const;
    // Get boolean option.
    // If result of function is true the current option is boolean.
    // Status of the option write by f_Value reference.
    // If result of function is false the current option is boolean with parameter.
    // Status of option always is true and write parameter by f_Parameter pointer.
    bool GetValue( bool& f_Value, std::string* f_Parameter = 0L ) const;
    void GetValue( std::string& f_Value ) const;
    SOptionData Help() const;
    struct option GnuOption() const;
  public:
    static const char* BOOLEAN_TRUE;
    static const char* BOOLEAN_FALSE;
  private:
    enum { eShortBuf = 4 };
  private:
    void pvSetBoolean();
  private:
    std::string pvLongOption;
    int pvShortOption;
    EArgument::FLAG pvArgFlag;
    std::string pvDefaultValue;
    std::string pvDescription;
    std::string pvValue;
    mutable char pvBuf[ eShortBuf ];
  };

  typedef std::vector< COption* > COptionArray;

}; /* namespace common */

#endif /* __COPTION_HPP__ */
