#include <list>
#include <algorithm>
#include <iterator>
#include <iostream>


const int list_size = 10;

class Int {
public:
  Int( const int& f_value ) : pv_value( f_value ) {
    std::cout << __FUNCTION__ << std::endl;
  }
  Int( const Int& f_value ) : pv_value( f_value.pv_value ) {
    std::cout << "copy " <<__FUNCTION__ << std::endl;
  }
  ~Int() {
    std::cout << __FUNCTION__ << std::endl;
  }
  void operator=( const Int& f_value ) {
    std::cout << __FUNCTION__ << std::endl;
    pv_value = f_value.pv_value;
  }
  bool operator<( const Int& f_value ) {
    return pv_value < f_value.pv_value;
  }
private:
  int pv_value;
private:
  friend std::ostream& operator<<( std::ostream& f_out, const Int& f_value );
};

std::ostream& operator<<( std::ostream& f_out, const Int& f_value ) {
  f_out << f_value.pv_value;
  return f_out;
}

const Int array0[] = { 25, 55, 75, 35, 65, 45, 15, 05, 95, 85 };
const Int array1[] = { 20, 50, 70, 30, 60, 40, 10, 100, 90, 80 };

int main( int ac, char* av[] ) {
  std::list< Int > list0( &array0[ 0 ], &array0[ list_size ] );
  std::cout << std::endl;
  std::list< Int > list1;
  for( int i = 0; i < list_size; ++i ) {
    std::list< Int >::iterator pos = std::lower_bound( list1.begin(), list1.end(), array1[ i ] );
    list1.insert( pos, array1[ i ] );
  }
  std::copy( list1.begin(), list1.end(), std::ostream_iterator< Int >( std::cout, "|" ) );
  std::cout << std::endl;
  while( !list0.empty() ) {
    std::list< Int >::iterator pos = std::lower_bound( list1.begin(), list1.end(), *list0.begin() );
    const Int& a = *list0.begin();
    list1.splice( pos, list0, list0.begin() );
    std::cerr << a << std::endl;
  }
  std::copy( list1.begin(), list1.end(), std::ostream_iterator< Int >( std::cout, "|" ) );
  std::cout << std::endl;
  return 0;
}
