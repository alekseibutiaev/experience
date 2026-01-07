//*****************************************************************************
//    Project : pu40
//       File : iocommon.hpp
// Created on : Mar 9, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __IOCOMMON_HPP__
#define __IOCOMMON_HPP__

#include <string>

namespace io {

  static const int INVALID_DESCRIPTOR = -1;
  static const int INVALID_RESULT = -1;
  static const int INVALID_PID = 0;
  static const int INFINITE_TIMEOUT = -1;
  static const std::string IPC_PREFIX = "/tmp/";

  namespace EAccess {
    enum MODE {
      eRead,
      eWrite,
      eRdWr
    };
  }; /* namespace EAccess */

  namespace ECreate {
    enum MODE {
      eOtherRead = 1L << 2,
      eOtherWrite = 1L << 1,
      eOtherExecute = 1L << 0,
      eOtherRWX = eOtherRead | eOtherWrite | eOtherExecute,
      eOtherRW = eOtherRead | eOtherWrite,
      eGroupRead = eOtherRead << 3,
      eGroupWrite = eOtherWrite << 3,
      eGroupExecute = eOtherExecute << 3,
      eGroupRWX = eOtherRWX << 3,
      eGroupRW = eOtherRW << 3,
      eUserRead = eGroupRead << 3,
      eUserWrite = eGroupWrite << 3,
      eUserExecute = eGroupExecute << 3,
      eUserRWX = eGroupRWX << 3,
      eUserRW = eGroupRW << 3,
      eRuleMask = eUserRWX | eGroupRWX | eOtherRWX
    };
  }; /* namespace ERule */

  namespace Private {
    int AccessModeToPosix( const EAccess::MODE& f_Access );
    int CreateModeToPosix( const ECreate::MODE& f_Create );
    void CloseDescriptor( int& f_Descriptor );
  }; /* namespace Private */

}; /* namespace io */

#endif /* __IOCOMMON_HPP__ */
