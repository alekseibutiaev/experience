#include <list>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

template< typename TYPE >
class queue {
public:
  void push( const TYPE& f_value ) {
    boost::unique_lock< boost::mutex > _( pv_mux );
    const bool empty = pv_list.empty();
    pv_list.push_back( f_value );
    if( empty )
      pv_cond.notify_all();      
  }
  TYPE pop() {
    boost::unique_lock< boost::mutex > _( pv_mux );
    while( pv_list.empty() )
      pv_cond.wait( _ );
    TYPE result = pv_list.front();
    pv_list.pop_front();
    return result;
  }
private:
  std::list< TYPE > pv_list;
  boost::mutex pv_mux;
  boost::condition_variable pv_cond;
};

class process {
public:
  process() : pv_thread( boost::bind( &process::pv_func, this ) ) {
  }
  ~process() {
    if( pv_thread.joinable() ) {
      pv_thread.interrupt();
      pv_thread.join();
    }
  }
  void push_data( const int& f_value ) {
    pv_queue.push( f_value );
  }
private:
  void pv_func() {
    try {
      for(;;) {
        const int a = pv_queue.pop();
        std::cout << a << std::endl;
        boost::this_thread::interruption_point();
      }
    }
    catch( const boost::thread_interrupted& ) {
    }
  }
private:
  boost::thread pv_thread;
  queue< int > pv_queue;
};

int main( int ac, char* av[] ) {

  process p;
  for( int a = 0; a < 10; ++a ) {
    p.push_data( a );
  }
  return 0;
}

