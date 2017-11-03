#include <memory>
#include <functional>

#include "logger.hpp"

template< typename type >
struct weak_ptr_wraper {
	weak_ptr_wraper( std::weak_ptr< type > _wp, const std::function< void(type&) >& _f )
		: wp( _wp )
		, f( std::move( _f ) )
	{
	}
	void operator()() const {
		if( std::shared_ptr< type > object = wp.lock() )
			f( *object );
		else
			logger::out( "weak_ptr has been expired\n" );
	}
	std::weak_ptr< type > wp;
	std::function< void(type&) > f;		
};

template< typename type >
weak_ptr_wraper<type> make_wrapper( std::shared_ptr< type > _ptr, const std::function< void(type&) >& _f ) {
	return weak_ptr_wraper<type>( _ptr, _f );
}

struct test_class {
	void foo( int a ) const {
		logger::out( __FUNCTION__, ' ', a, '\n' );
	}
};

int main( int ac, char* av[] ) {
	logger::out( STRING_DEFENITION, '\n' );
	try {
		std::function<void()> f;
		{
			std::shared_ptr<test_class> t = std::make_shared<test_class>();
//			std::function<void(test_class&)> ft = std::bind( &test_class::foo, std::placeholders::_1, 5 );
			f = make_wrapper( t, std::function<void(test_class&)>( std::bind( &test_class::foo, std::placeholders::_1, 5 ) ) );
			f();
		}
		f();
	}
	catch( const std::exception& e ) {
		logger::out( e.what(), '\n' );
	}
	return 0;
}

