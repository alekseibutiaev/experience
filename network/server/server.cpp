// server.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <conio.h>

#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstdlib>

#include <list>
#include <iostream>
#include <algorithm>
#include <exception>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/smart_ptr.hpp>

#include <network/acceptor.hpp>
#include <network/handler.hpp>

const unsigned short port = 36510;

inline unsigned long abs_( const long& f_value ) {
  return 0 > f_value ? -f_value : f_value;
}

struct convert {
  unsigned char operator()( const unsigned char& f_value ) {
    return isupper( f_value ) ? tolower( f_value ) :
      islower( f_value ) ? toupper( f_value ) :
        isprint( f_value ) ? f_value : '.';
  }
};

class example_server;
typedef boost::shared_ptr< example_server > example_server_ptr;
typedef boost::weak_ptr< example_server > example_server_ref;

class manager {
public:
  virtual ~manager(){}
  virtual void add_server( example_server_ptr f_server ) = 0;
  virtual void delete_server( example_server_ptr f_server ) = 0;
};

class example_server : public network::session_receiver,
  public boost::enable_shared_from_this< example_server > {
public:
  example_server( manager* f_manager ) : pv_transmiter( 0 ), pv_manager( f_manager ) {
    std::cout << "example_server::example_server 0x" << this << std::endl;
  }
  ~example_server() {
    std::cout << "example_server::~example_server 0x" << this << std::endl;
  }
  // network::session_receiver interface
  void connected( network::session_transmiter* f_transmiter ) {
    pv_transmiter = f_transmiter;
    pv_manager->add_server( shared_from_this() );
  }
  void disconnected() {
  }
  void closed() {
    pv_manager->delete_server( shared_from_this() );
  }
  void receive( const network::buffer_ptr& f_data ) {
    std::cout << "from client: " << f_data->size() << std::endl;
    network::buffer_ptr data( new network::buffer_ptr::element_type() );
    std::transform( f_data->begin(), f_data->end(), std::back_inserter( *data ), convert() );
    pv_transmiter->transmit( data );
  }
  void close() {
    pv_transmiter->close();
  }
private:
  manager* pv_manager;
  network::session_transmiter* pv_transmiter;
};

class delete_pointer {
public:
  delete_pointer( example_server_ptr f_ptr = example_server_ptr() ) : pv_ptr( f_ptr ) {
  }
  bool operator()( example_server_ref f_value ) const {
    if( example_server_ptr ptr = f_value.lock() )
      return pv_ptr == ptr;
    else
      return true;
  }
private:
  example_server_ptr pv_ptr;
};

class server_manager : public network::creator , public manager {
public:
  server_manager() {
    pv_thread = boost::thread( boost::bind( &server_manager::pv_manager_routine, this ) );
  }
  ~server_manager() {
    if( pv_thread.joinable() ) {
      pv_thread.interrupt();
      pv_thread.join();
    }
  }
  network::session_receiver_ptr create() {
    return network::session_receiver_ptr( new example_server( this ) );
  }
  unsigned long size() const {
    mutex_type::scoped_lock _( pv_mutex );
    return pv_servers.size();
  } 
  void add_server( example_server_ptr f_server ) {
    mutex_type::scoped_lock _( pv_mutex );
    pv_servers.remove_if( delete_pointer() );
    pv_servers.push_back( f_server );
    std::cout << "server count: " << pv_servers.size() << std::endl;
  }
  void delete_server( example_server_ptr f_server ) {
    mutex_type::scoped_lock _( pv_mutex );
    pv_servers.remove_if( delete_pointer( f_server ) );
    std::cout << "server count: " << pv_servers.size() << std::endl;
  }
private:
  typedef std::list< example_server_ref > server_list;
  typedef boost::mutex mutex_type;
private:
  void pv_change_limits() {
    const unsigned long first = rand() % pv_max_servers + 1;
    unsigned long second;
    while( abs_( ( second = rand() % pv_max_servers + 1 ) - first ) < pv_min_limit_range ) {
    }
    pv_min_limit = std::min( first, second );
    pv_max_limit = std::max( first, second );
  }
  void pv_manager_routine() {
    try {
      bool del = false;
      pv_change_limits();
      for(;;) {
        boost::this_thread::sleep( boost::posix_time::seconds( rand() % pv_time_range ) );
        const unsigned long server_count = pv_servers.size();
        if( server_count < pv_min_limit && del ) {
          del = false;
          pv_change_limits();
        }
        if( server_count > pv_max_limit )
          del = true;
        if( del && 0 < server_count ) {
          const unsigned long index = rand() % server_count;
          server_list::iterator it = pv_servers.begin();
          std::advance( it, index );
          if( example_server_ptr server_ptr = it->lock() )
            server_ptr->close();
        }
      }
    }
    catch( const boost::thread_interrupted& ) {
    }
  }
private:
  unsigned long pv_min_limit;
  unsigned long pv_max_limit;
  mutable mutex_type pv_mutex;
  server_list pv_servers;
  boost::thread pv_thread;
private:
  static const long pv_time_range = 15;
  static const unsigned long pv_min_limit_range = 3;
  static const unsigned long pv_max_servers = 7;

};

int main( int ac, char* av[] ) {
  try {
    srand( static_cast< unsigned int >( time( 0 ) ) );
    boost::shared_ptr< server_manager > mg( new server_manager() );
    network::acceptor acceptor( port, boost::shared_ptr< network::creator >( mg ) );
    std::cout << "Press ESC for stop program." << std::endl;
    while( _getch() != 27 ) {
    }
    std::cout << std::endl;
  }
  catch( const std::exception& e ) {
    std::cerr << e.what() << std::endl;
  }
  std::cout << "Press ESC for exit." << std::endl;
  boost::this_thread::sleep( boost::posix_time::seconds( 1 ) );
  while( _getch() != 27 ) {
  }
	return 0;
}
