#include <ctime>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/functional.hpp>
#include <boost/smart_ptr.hpp>


struct usr {
  usr( const int& f_value ) : value( f_value ) {
  }
  const int value;
};

typedef boost::shared_ptr< usr > usr_ptr;

class deadline_time {
public:
  typedef boost::function< void() > dedline_callback;
public:
  deadline_time() : work( io_service ), thread( boost::bind( &deadline_time::run, this ) ) {
  }
  ~deadline_time() {
    io_service.stop();
    thread.join();
  }
  void set( const unsigned int f_second, dedline_callback f_callback ) {
    deadline_timer_ptr timer( new boost::asio::deadline_timer( io_service ) );
    timer->expires_from_now( boost::posix_time::seconds( f_second ) );
    timer->async_wait( boost::bind( &deadline_time::deadline, this, timer, f_callback, boost::asio::placeholders::error ) );
  }
private:
  typedef boost::shared_ptr< boost::asio::deadline_timer > deadline_timer_ptr;
private:
  void deadline( deadline_timer_ptr, dedline_callback f_callback, const boost::system::error_code& f_error ) {
    f_callback();
  }
  void run() {
    boost::system::error_code error;
    io_service.run( error );
  }
private:
  boost::asio::io_service io_service;
  boost::asio::io_service::work work;
  boost::thread thread;
};

void foo1( usr_ptr f_value ) {
  time_t t;
  time( &t );
  std::cout << __FUNCTION__ << " " << t << " " << f_value->value << std::endl;
}

void foo2( const int f_ivalue, const double& f_dvalue ) {
  time_t t;
  time( &t );
  std::cout << __FUNCTION__ << " " << t << " " << f_ivalue << " " << f_dvalue << std::endl;
}

struct foo3 {
  foo3( std::string f_value ) : value( f_value ) {
  }
  void call( const std::string& f_value ) {
    time_t t;
    time( &t );
    std::cout << __FUNCTION__ << " " << t << " " << value << " " << f_value << std::endl;
  }
  const std::string value;
};

int main( int argc, char* argv[] )
{
  time_t t;
  time( &t );
  std::cout<< "start in " << t << std::endl;
  foo3 f( "first" );

  deadline_time dl;
  dl.set( 5, boost::bind( &foo1, usr_ptr( new usr( 6 ) ) ) );
  dl.set( 7, boost::bind( &foo2, 47, 94.098 ) );
  dl.set( 3, boost::bind( &foo3::call, f, "second" ) );

  for( int i = 0; i < 10; ++i )
    boost::this_thread::sleep( boost::posix_time::seconds( 1 ) );

  time( &t );
  std::cout << "Stop in " << t << std::endl;

  return 0;
}
