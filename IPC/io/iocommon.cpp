//*****************************************************************************
//    Project : pu40
//       File : iocommon.cpp
// Created on : Mar 9, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <common/common.hpp>
#include "iocommon.hpp"

#include <fcntl.h>

#include <cerrno>
#include <cstring>

namespace io {

  namespace Private {

//*****************************************************************************
    int AccessModeToPosix( const EAccess::MODE& f_Access ) {
      FUNCTION_LOG;
      return f_Access == EAccess::eRead ? O_RDONLY :
        f_Access == EAccess::eWrite ? O_WRONLY : O_RDWR;
    }
//*****************************************************************************
    int CreateModeToPosix( const ECreate::MODE& f_Create ) {
      FUNCTION_LOG;
      int result = 0;
      result |= f_Create & ECreate::eOtherRead ? S_IROTH : 0;
      result |= f_Create & ECreate::eOtherWrite ? S_IWOTH : 0;
      result |= f_Create & ECreate::eOtherExecute ? S_IXOTH : 0;
      result |= f_Create & ECreate::eGroupRead ? S_IRGRP : 0;
      result |= f_Create & ECreate::eGroupWrite ? S_IWGRP : 0;
      result |= f_Create & ECreate::eGroupExecute ? S_IXGRP : 0;
      result |= f_Create & ECreate::eUserRead ? S_IRUSR : 0;
      result |= f_Create & ECreate::eUserWrite ? S_IWUSR : 0;
      result |= f_Create & ECreate::eUserExecute ? S_IXUSR : 0;
      return result;
    }
//*****************************************************************************
    void CloseDescriptor( int& f_Descriptor ) {
      FUNCTION_LOG;
      common::Log()->Out( common::ELogLevel::eInfo, __FILE__, __FUNCTION__,
          "Close descriptor %d.\n", f_Descriptor );
      if( io::INVALID_DESCRIPTOR != f_Descriptor ) {
        if( io::INVALID_RESULT == close( f_Descriptor ) )
          common::Log()->Out( common::ELogLevel::eErr, __FILE__, __FUNCTION__,
              "Can not close pipe. Reason: %s\n", strerror( errno ) );
        f_Descriptor = io::INVALID_DESCRIPTOR;
      }
    }

  }; /* namespace Private */

}; /* namespace io */
