#include <set>
#include <tuple>
#include <iostream>

#include <library/logger.hpp>

template <typename type>
class _icmp {
public:
	_icmp( const type& value = type() ) : m_value(value) {}
	_icmp( const _icmp<type>& ) = default;
	_icmp( _icmp<type>&& ) = default;
	_icmp& operator=( const _icmp<type>& ) = default;
	_icmp& operator=( _icmp<type>&& ) = default;
	operator type() const { return m_value; }
	friend inline bool operator<( const _icmp<type>& lv, const _icmp<type>& rv ) {
		return rv.m_value < lv.m_value;
	}
	friend bool inline operator==( const _icmp<type>& lv, const _icmp<type>& rv ) {
		return rv.m_value == lv.m_value;
	}
	friend std::ostream& operator<<( std::ostream& stream, const _icmp<type>& v ) {
		stream << v.m_value;
		return stream;
	}
private:
	type m_value;
};

template<typename type>
inline bool operator>( const _icmp<type>& lv, const _icmp<type>& rv ) {
	return rv < lv;
}

template<typename type>
inline bool operator<=( const _icmp<type>& lv, const _icmp<type>& rv ) {
	return !( rv < lv );
}

template<typename type>
inline bool operator>=( const _icmp<type>& lv, const _icmp<type>& rv ) {
	return !( lv < rv );
}

template<typename type>
bool inline operator!=( const _icmp<type>& lv, const _icmp<type>& rv ) {
	return !( rv == lv );
}

using _int = _icmp<int>;
using tuple1 = std::tuple<int, int>;
using tuple2 = std::tuple<_int, int>;

using set_1 = std::set<tuple1>;
using set_2 = std::set<tuple2>;

int main( int ac, char* av[] ) {
	logger::out( __FUNCTION__, ' ', av[ 0 ], ' ', __DATE__, logger::endl );

	logger::out( "_int( 5 ) < _int( 6 ) is: ", _int( 5 ) < _int( 6 ), logger::endl );
	logger::out( "_int( 6 ) < _int( 5 ) is: ", _int( 6 ) < _int( 5 ), logger::endl );
	logger::out( "_int( 5 ) < _int( 5 ) is: ", _int( 5 ) < _int( 5 ), logger::endl, logger::endl );

	logger::out( "_int( 5 ) > _int( 6 ) is: ", _int( 5 ) > _int( 6 ), logger::endl );
	logger::out( "_int( 6 ) > _int( 5 ) is: ", _int( 6 ) > _int( 5 ), logger::endl );
	logger::out( "_int( 5 ) > _int( 5 ) is: ", _int( 5 ) > _int( 5 ), logger::endl, logger::endl );

	logger::out( "_int( 6 ) <= _int( 6 ) is: ", _int( 6 ) <= _int( 6 ), logger::endl );
	logger::out( "_int( 6 ) >= _int( 6 ) is: ", _int( 6 ) >= _int( 6 ), logger::endl, logger::endl );

	logger::out( _int(66), logger::endl );

	const set_1 t1 = { tuple1( 1, 30 ), tuple1( 2, 20 ), tuple1( 3, 10 ) };
	const set_2 t2( t1.begin(), t1.end() );

	for ( const set_1::value_type& i : t1 )
		logger::out( "set_1 first: ", std::get<0>(i), ", second: ", std::get<1>(i), logger::endl );
	logger::out(logger::endl );
	for ( const set_2::value_type& i : t2 )
		logger::out( "set_2 first: ", std::get<0>(i), ", second: ", std::get<1>(i), logger::endl );
	return 0;
}

