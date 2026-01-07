//============================================================================
// Name        : rpn.cpp
// Author      : Butyaev A
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cctype>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>

template< typename T, unsigned int N >
T* begin( T(&arr)[N] ) { return &arr[0]; }

template< typename T, unsigned int N >
T* end( T(&arr)[N] ) { return &arr[N]; }

struct prep
{
  std::string operator()( std::string& init, const char& value ) const
  {
    return init + (std::isdigit( value ) ? std::string( &value, 1 ) :
        '+' == value ? " + " :
        '-' == value ? " - " :
        '*' == value ? " * " :
        '/' == value ? " / " :
        '^' == value ? " ^ " :
        '(' == value ? " ( " :
        ')' == value ? " ) " :
        '.' == value ? "." :
        ',' == value ? "." :
        " ");
  }
};

std::vector<std::string> prepare_string( const std::string& value )
{
  std::stringstream ss( value );
  std::string s = std::accumulate( std::istream_iterator<char>( ss ),
      std::istream_iterator<char>(), std::string(), prep() );
  std::stringstream sss( s );
  std::vector<std::string> result;
  std::copy(std::istream_iterator<std::string>( sss ), std::istream_iterator<std::string>(),
      std::back_inserter(result) );
  return result;
}

struct op_prec{
  op_prec( const std::string& value ) : name(value){}
  bool operator()( const std::pair<std::string, int>& value ) const{
    return value.first == name;
  }
  const std::string& name;
};

int get_precedence( const std::string& value ){
  static const std::pair<std::string, int> op[] = {
    std::pair<std::string, int>( "(", 0 ),
    std::pair<std::string, int>( ")", 0 ),
    std::pair<std::string, int>( "+", 1 ),
    std::pair<std::string, int>( "-", 1 ),
    std::pair<std::string, int>( "/", 2 ),
    std::pair<std::string, int>( "*", 2 ),
    std::pair<std::string, int>( "^", 3 ),
  };
  const std::pair<std::string, int>* it = std::find_if( begin( op ), end( op ), op_prec( value ) );
  return it != end( op ) ? it->second : -1;
}

struct rpn_builder
{
  rpn_builder( std::vector< std::string >& value ) : opertor_( value ){}
  std::vector< std::string > operator()( std::vector< std::string >& init, const std::string& value )
  {
    if( std::string::npos == value.find_first_not_of( "0123456789." ) )
      init.push_back( value );
    else if( "(" == value )
      opertor_.push_back( value );
    else if( ")" == value ) {
      for(;;)
      {
        if( opertor_.empty() )
          throw( std::logic_error( "braces incorrect" ) );
        const std::string tmp = opertor_.back();
        opertor_.pop_back();
        if( "(" == tmp )
          break;
        else
          init.push_back( tmp );
      }
    }
    else if( std::string::npos != value.find_first_of( "+-*/^" ) ) {
      //function
      if( opertor_.empty() )
        opertor_.push_back( value );
      else {
        std::string tmp = value;
        if( get_precedence( value ) <= get_precedence( opertor_.back() ) ) {
          init.push_back( opertor_.back() );
          opertor_.back() = value;
        }
        else
          opertor_.push_back( tmp );
      }
    }
    return init;
  }
  std::vector< std::string >& opertor_;
};

std::vector< std::string > rpn( const std::vector< std::string >& value )
{
  std::vector< std::string > operand;
  std::vector< std::string > result = std::accumulate( value.begin(), value.end(),
      std::vector< std::string >(), rpn_builder(operand) );
  std::copy( operand.rbegin(), operand.rend(), std::back_inserter( result ) );
  return result;
}

std::string pop_front( std::vector< std::string >& prn_set )
{
  if( prn_set.empty() )
    throw( std::runtime_error( "indetermenate expresson" ) );
  const std::string result = prn_set.front();
  prn_set.erase( prn_set.begin() );
  return result;
}

double plus( const double& lvalue, const double& rvalue )
{
  return lvalue + rvalue;
}

double minus( const double& lvalue, const double& rvalue )
{
  return lvalue - rvalue;
}

double multiplies( const double& lvalue, const double& rvalue )
{
  return lvalue * rvalue;
}

double divides( const double& lvalue, const double& rvalue )
{
  return lvalue / rvalue;
}

double _pow( const double& lvalue, const double& rvalue )
{
  return std::pow(lvalue, rvalue);
}

typedef double(*func_t)( const double&, const double& );

std::string applay( std::vector<std::string>& stack, func_t func )
{
  std::string rvalue = stack.back();
  stack.pop_back();
  std::string lvalue = stack.back();
  stack.pop_back();
  const double result = func( std::atof(lvalue.c_str() ), std::atof( rvalue.c_str()));
  std::stringstream ss;
  ss << result;
  return ss.str();
}

struct func_name{
  func_name( const std::string& value ) : name(value){}
  bool operator()( const std::pair< std::string, func_t>& value ) const
  {
    return value.first == name;
  }
  const std::string& name;
};

func_t get_function( const std::string& value )
{
  static const std::pair< std::string, func_t> op_array[] = {
      std::pair< std::string, func_t>( "+", plus ),
      std::pair< std::string, func_t>( "-", minus ),
      std::pair< std::string, func_t>( "*", multiplies ),
      std::pair< std::string, func_t>( "/", divides ),
      std::pair< std::string, func_t>( "^", _pow ),
  };
  const std::pair< std::string, func_t>* it = std::find_if( begin( op_array ),
      end( op_array ), func_name(value) );
  return it != end( op_array ) ? it->second : 0;
}

double calculate( std::vector< std::string >& prn_set )
{
  std::vector<std::string> stack;
  while( !prn_set.empty() )
  {
    const std::string tmp = pop_front( prn_set );
    if( std::string::npos != tmp.find_first_of( "0123456789." ) )
      stack.push_back( tmp );
    else if( func_t f = get_function( tmp ) )
      stack.push_back( applay( stack, f ) );
    else
      throw( std::runtime_error( "unknown operator: " + tmp ) );
  }
  return std::atof( stack.back().c_str() );
}

int main()
{
  try{
    std::string input = "3+4*2/(1-5)^2";
    std::getline( std::cin, input );

    std::vector<std::string> s = prepare_string( input );
    std::copy( s.begin(), s.end(), std::ostream_iterator<std::string>( std::cout, " " ) );
    std::cout << std::endl;
    s = rpn( s );
    std::copy( s.begin(), s.end(), std::ostream_iterator<std::string>( std::cout, " " ) );
//    double r = calculate( s );
    //std::cout << " = " << r << std::endl;
  } catch( const std::exception& e )
  {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
