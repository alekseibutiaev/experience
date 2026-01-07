//******************************************************************************
// The Robocode project.
// The file of RobocodeAdapter.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "RobocodeAdapter.h"
//******************************************************************************
#ifndef __ROBOCODEADAPTER_H__
#define __ROBOCODEADAPTER_H__

// The adapter unary_compose has borrowed from STL from SGI
// The given adapter makes functions by way of a = F1( F2( x ) )
template< typename _Func1, typename _Func2 >
class unary_compose : public std::unary_function< typename _Func2::argument_type,
		typename _Func1::result_type > {
protected:
	_Func1 fn1;
	_Func2 fn2;
public:
	unary_compose( const _Func1& __x, const _Func2& __y ) : fn1( __x ),
			fn2( __y ) {};
	typename _Func1::result_type 
	operator()( const typename _Func2::argument_type& __x ) const {
		return fn1( fn2( __x ) );
	}
};

template< typename _Func1, typename _Func2 >
inline unary_compose< _Func1, _Func2 > 
compose1( const _Func1& f_fn1, const _Func2& f_fn2 ){
	return unary_compose< _Func1, _Func2 >( f_fn1, f_fn2 );
};

#endif /*__ROBOCODEADAPTER_H__*/
