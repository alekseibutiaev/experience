// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <conio.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>

#include <list>
#include <iostream>
#include <iterator>
#include <exception>
#include <algorithm>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/smart_ptr.hpp>

#include <network/buffer.hpp>
#include <network/handler.hpp>
#include <network/connector.hpp>

const unsigned short port = 36510;

struct convert {
  unsigned char operator()( const unsigned char& f_value ) {
    return isupper( f_value ) ? tolower( f_value ) :
      islower( f_value ) ? toupper( f_value ) :
        isprint( f_value ) ? f_value : '.';
  }
};

class example_client;

typedef boost::shared_ptr< example_client > example_client_ptr;

class manager {
public:
  virtual ~manager() {}
  virtual void add_client( example_client_ptr f_client ) = 0;
  virtual void delete_client( example_client_ptr f_client ) = 0;
};

class example_client : public network::session_receiver,
    public boost::enable_shared_from_this< example_client > {
public:
  example_client( manager* f_manager ) : pv_close_by_server( 0 != rand() % 1 ),
      pv_manager( f_manager ), pv_transmiter( 0 ) {
    std::cout << "example_client::example_client 0x" << this << std::endl;
  }
  ~example_client() {
    std::cout << "example_client::~example_client 0x" << this << std::endl;
  }
  void write( const char& f_data ) {
    network::buffer_ptr data( new network::buffer_ptr::element_type( &f_data, &f_data + 1 ) );
    pv_transmiter->transmit( data );
  }
  void write( const network::buffer_ptr& f_data ) {
    std::cout << "to server: " << f_data->size() << std::endl;
    pv_transmiter->transmit( f_data );
  }
  void close() {
    pv_transmiter->close();
  }
  // network::session_receiver interface
  void connected( network::session_transmiter* f_transmiter ) {
    pv_transmiter = f_transmiter;
    pv_manager->add_client( shared_from_this() );
  }
  void disconnected() {
  }
  void closed() {
    pv_manager->delete_client( shared_from_this() );
  }
  void receive( const network::buffer_ptr& f_data ) {
    std::cout << "from server: " << f_data->size() << std::endl;
  }
  const bool& close_by_server() const {
    return pv_close_by_server;
  }
private:
  bool pv_close_by_server;
  manager* pv_manager;
  network::session_transmiter* pv_transmiter;
  boost::thread pv_thread;
};

class client_manager : public boost::enable_shared_from_this< client_manager >,
    public network::creator, public manager {
public:
  client_manager( boost::shared_ptr< network::connector >& f_nc ) : pv_nc( f_nc ) {
    operation_set[ client_manager::e_open ] = &client_manager::pv_open;
    operation_set[ client_manager::e_close ] = &client_manager::pv_close;
    operation_set[ client_manager::e_send ] = &client_manager::pv_send;
    operation_set[ client_manager::e_pause ] = &client_manager::pv_pause;
    pv_thread = boost::thread( boost::bind( &client_manager::pv_manager_thread, this ) );
  }
  ~client_manager() {
    if( pv_thread.joinable() ) {
      pv_thread.interrupt();
      pv_thread.join();
    }
    client_list clients = pv_clients;
    std::for_each( clients.begin(), clients.end(), boost::bind( &example_client::close, _1 ) );
  }
  void add_client( example_client_ptr f_client ) {
    boost::unique_lock< boost::mutex > _( pv_mutex );
    pv_clients_new.push_back( f_client );
  }
  void delete_client( example_client_ptr f_client ) {
    boost::unique_lock< boost::mutex > _( pv_mutex );
    pv_clients_delete.push_back( f_client );
  }
  network::session_receiver_ptr create() {
    return network::session_receiver_ptr( new example_client( this ) );
  }
private:
  typedef std::list< example_client_ptr > client_list;
  enum operation {
    e_open,
    e_close,
    e_send,
    e_pause,
    e_count
  };
  typedef void(client_manager::*operation_f)();
private:
  void pv_manager_thread() {
    try {
      for(;;) {
        const unsigned int index = rand() % client_manager::e_count;
        (this->*operation_set[ index ])();
        boost::this_thread::interruption_point();
        boost::unique_lock< boost::mutex > _( pv_mutex );
        if( !pv_clients_new.empty() )
          pv_clients.splice( pv_clients.end(), pv_clients_new,
            pv_clients_new.begin(), pv_clients_new.end() );
        if( !pv_clients_delete.empty() ) {
          std::for_each( pv_clients_delete.begin(), pv_clients_delete.end(),
            boost::bind( &client_list::remove, &pv_clients, _1 ) );
          pv_clients_delete.clear();
        }
      }
    }
    catch( const boost::thread_interrupted& ) {
    }
  }
  void pv_open() {
    pv_nc->connect( "localhost", port, this );
  }
  void pv_close() {
    if( 0 < pv_clients.size() ) {
      const unsigned long index = rand() % pv_clients.size();
      client_list::iterator it = pv_clients.begin();
      std::advance( it, index );
      if( !(*it)->close_by_server() )
        (*it)->close();
    }
  }
  void pv_send() {
    if(  0 < pv_clients.size() ) {
      const unsigned long size = rand() % pv_send_limit;
      network::buffer_ptr buf( new network::buffer_ptr::element_type( size ) );
      std::generate( buf->begin(), buf->end(), rand );
      const unsigned long index = rand() % pv_clients.size();
      client_list::iterator it = pv_clients.begin();
      std::advance( it, index );
      (*it)->write( buf );
    }
  }
  void pv_pause() {
//    const long time = rand() % pv_time;
//    boost::this_thread::sleep( boost::posix_time::seconds( time ) );
  }
private:
  boost::shared_ptr< network::connector > pv_nc;
  client_list pv_clients;
  client_list pv_clients_new;
  client_list pv_clients_delete;
  operation_f operation_set[ client_manager::e_count ];
  boost::mutex pv_mutex;
  boost::thread pv_thread;
private:
  static const unsigned int pv_time = 5;
  static const unsigned int pv_send_limit = 16 * 1024;
};


int main( int ac, char* av[] ) {
  try {
    srand( static_cast< unsigned int >( time( 0 ) ) );
    boost::shared_ptr< network::connector > nc( new network::connector() );
    boost::shared_ptr< manager > mg( new client_manager( nc ) );
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
