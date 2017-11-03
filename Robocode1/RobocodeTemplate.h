//******************************************************************************
// The Robocode project.
// The file of RobocodeTemplate.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "RobocodeTemplate.h"
//******************************************************************************
#ifndef __ROBOCODETEMPLATE_H__
#define __ROBOCODETEMPLATE_H__

#include "RobocodeAdapter.h"

#include <functional>

// The template of operator of additional.
template< typename T >
inline T operator+( T f_First, T f_Second ){
	return T( static_cast< int >( f_First ) + static_cast< int >( f_Second ) );
}
// The template of operator of additional and assign.
template< typename T >
inline T operator+=( T& f_First, T& f_Fecond ){
	return f_First = f_First + f_Fecond;
}
// The template of operator of modulus.
template< typename T >
inline T operator%( T f_First, T f_Second ){
	return T( static_cast< int >( f_First ) % static_cast< int >( f_Second ) );
}
// The template for execute nent by name/
template < typename Type >
Type GetType( const std::vector< std::pair< std::string, Type > > &
		f_TypeDescription, const std::string& f_Name )
		throw( CRobocodeException ){
	typedef typename std::vector< std::pair< std::string, Type > >::const_iterator
			CConstIterator;
	typedef std::pair< std::string, Type > CNameType;
	// As the index on the end is used twice. We create a variable.
	CConstIterator end( f_TypeDescription.end() );
	// To find pair the NameType by name
	CConstIterator IterNameType( std::find_if( f_TypeDescription.begin(), end,
			compose1( std::bind2nd( std::equal_to< std::string >(), f_Name ),
			std::_Select1st< CNameType >() ) ) );
	// To check up result of search.
	if( IterNameType == end )
		throw( CRobocodeException( ( std::string( "The type of " ) + f_Name + 
				": is not supported." ).c_str() ) );
	// To getting type from pair.
	return std::_Select2nd< CNameType >()( *IterNameType );
};

#endif /*__ROBOCODETEMPLATE_H__*/
