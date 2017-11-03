//*****************************************************************************
//    Project : pu40
//       File : CSinglton.h
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CSINGLTON_H__
#define __CSINGLTON_H__

#include <boost/smart_ptr.hpp>
#include <boost/utility.hpp>

namespace common {

  namespace Private {
//*****************************************************************************

    class SingltonPolicy {
    public:
      virtual ~SingltonPolicy(){}
      virtual void Deliter() = 0;
    };

  } /* namespace Private */

//*****************************************************************************

  template < typename SingltonPolicy >
  class CSingltonPtr : private boost::shared_ptr< SingltonPolicy > {
    typedef boost::shared_ptr< SingltonPolicy > parent;
  public:
    explicit CSingltonPtr( SingltonPolicy* f_Ptr = 0 ) :
      parent( f_Ptr, CSingltonPtr< SingltonPolicy >::pvDeliter ){
    }
    void reset( SingltonPolicy* f_Ptr ) {
      parent::reset( f_Ptr, CSingltonPtr< SingltonPolicy >::pvDeliter );
    }
    using parent::operator->;
    using parent::operator=;
    using parent::get;
  private:
    static void pvDeliter( SingltonPolicy* f_Ptr ) {
      if( f_Ptr )
        f_Ptr->Deliter();
    }
  };

//*****************************************************************************
  template < typename Class >
  class CSinglton : public Class, Private::SingltonPolicy {
  public:
    static CSingltonPtr< CSinglton< Class > > Instance() {
      if( 0L == pvInstance )
        pvInstance = new CSinglton< Class >();
      ++pvCounter;
      return CSingltonPtr< CSinglton< Class > >( pvInstance );
    }
    void Deliter(){
      if( 0L != pvInstance && 0 == --pvCounter ) {
        delete pvInstance;
        pvInstance = 0L;
      }
    }
  private:
    CSinglton(){}
    ~CSinglton(){}
  private:
    static unsigned long pvCounter;
    static CSinglton< Class >* pvInstance;
  };

  template < typename Class >
  unsigned long CSinglton< Class >::pvCounter;

  template < typename Class >
  CSinglton< Class >* CSinglton< Class >::pvInstance = 0L;

//*****************************************************************************

}; /* namespace common */

#endif /* __CSINGLTON_H__ */
