#include <functional>
#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// To define my types
typedef pair < double, bool > TEqu;
typedef pair < const string, TEqu > TRol;
typedef map < const string, TEqu > TMapRol;
typedef TMapRol::iterator TIMapRol;
typedef pair< TIMapRol, bool > TInsRol;
typedef pair < const string, TMapRol > TCol;
typedef map < const string, TMapRol > TMapCol;
typedef TMapCol::iterator TIMapCol;
typedef pair< TIMapCol, bool > TInsCol;
typedef vector < TEqu > TVecEqu;
typedef TVecEqu::iterator TIVecEqu;

//******************************************************************************
// to declare class of function
//******************************************************************************
class findcolumn : public unary_function < TCol , bool > {
	string _Target;
public:
	explicit findcolumn( const string& f_Target ) :	_Target( f_Target ) {}
	bool operator()( TCol& f_Pair );
};

class findrol : public unary_function < TRol, bool >{
	string _Target;
public:
	explicit findrol( const string& f_Target ) : _Target( f_Target ) {}
	bool operator()( TRol& f_Rol );
};


// To declare workspace 

TMapCol _WorkSpace;
TVecEqu _VecEqu;
//******************************************************************************
// 
//******************************************************************************
bool findrol::operator()( TRol& f_Rol )
{
	TIMapCol next;

	if( f_Rol.second.second )
		return false;
	
	// To mark current of element
	f_Rol.second.second = true;
	// To check name of current of rol with target
	if( f_Rol.first != _Target &&
		( next = _WorkSpace.find( f_Rol.first ) ) != _WorkSpace.end() &&
		!findcolumn( _Target )( *next ) ){
		return false;
		}
	else{
		// To save current step
		_VecEqu.push_back( f_Rol.second );
		return true;
		}

#if 0
	TIMapCol icol;
	bool a = f_Rol.second.second;
	if( f_Rol.second.second == true )
		return false;
	else{
		// To mark current of element
		f_Rol.second.second = true;
 		a = f_Rol.second.second;
		// To check name of current of rol with target
		if( f_Rol.first == _Target ){
			_VecEqu.push_back( f_Rol.second );
			return true;
			}
		TIMapCol next;
		// To find next coloms
		if( ( next = _WorkSpace.find( f_Rol.first ) ) == _WorkSpace.end() )
			return false;
		else if( findcolumn( _Target )( *next ) ){
			_VecEqu.push_back( f_Rol.second );
			}
		else 
			return false;
		}
	return true;
#endif
}

//******************************************************************************
// 
//******************************************************************************
bool findcolumn::operator()( TCol& f_Pair )
{
	TIMapRol end( f_Pair.second.end() );
	// To search in current column
	return find_if( f_Pair.second.begin(), end, findrol( _Target ) ) != end;
}

//******************************************************************************
// This class and function for show worcspace. This function for debuging
//******************************************************************************
class showrol : public unary_function< TRol, void >{
public:
	void operator()( const TRol& rol ) const{
		cout << rol.first << " " << rol.second.first << " "
			<< ( rol.second.second ? "true" : "false" )	<< "; ";
		}
};

class showcol : public unary_function< TCol, void >{
public:
	void operator()( const TCol& col ) const{
		cout << "List col by name " << col.first << "; " ;
		for_each( col.second.begin(), col.second.end(), showrol() );
		cout << endl;
		}
};

void showws()
{
	for_each( _WorkSpace.begin(), _WorkSpace.end(), showcol() );
	cout << endl;
}

//******************************************************************************
// This class and function for clear worcspace
//******************************************************************************
class clearrol : public unary_function< TRol, void >{
public:
	void operator()( TRol& rol ) {
		rol.second.second = false; 
		}
};

class clearcol : public unary_function< TCol, void >{
public:
	void operator()( TCol& f_col ){
		for_each( f_col.second.begin(), f_col.second.end(), clearrol() );
		}
};

void clear()
{
	for_each( _WorkSpace.begin(), _WorkSpace.end(), clearcol() );
}

//******************************************************************************
// To check stream
//******************************************************************************
bool chackstream( ios& f_strem )
{
	bool result;
	if( ( result = !f_strem.good() ) )
		f_strem.clear();
	return result;
}
//******************************************************************************
//To insert next col in to work space 
//******************************************************************************
bool insertcol( double f_firstvalue, const string& f_firstname,
		double f_secondvalue, const string& f_secondname )
{
	TInsCol colinsert;
	TInsRol	rolinsert;
	// To insert col by name first
	colinsert = _WorkSpace.insert( TCol( f_firstname,	TMapRol() ) );
	// To insetr element by name second
	rolinsert = colinsert.first->second.insert( TRol( f_secondname,
			TEqu( f_secondvalue/f_firstvalue, false ) ) );
	return colinsert.second || rolinsert.second; 
}
//******************************************************************************
//To insert next pair in to work space 
//******************************************************************************
bool insertequ( double f_firstvalue, const string& f_firstname,
		double f_secondvalue, const string& f_secondname  )
{
	bool first = insertcol( f_firstvalue, f_firstname,
			f_secondvalue, f_secondname );
	bool second = insertcol( f_secondvalue, f_secondname, f_firstvalue,
			f_firstname );
	return first || second;
}
//******************************************************************************
// This function of find to path
//******************************************************************************
bool findpath( int f_mask, const double f_firstvalue, const string& f_firstname,
		const double f_secondvalue, const string& f_secondname  )
{
	TIMapCol end( _WorkSpace.end() );	
	// To choose target
	string target( f_mask & 1 ? f_secondname : f_firstname );
	// Fo find of begin for search
	TIMapCol start( _WorkSpace.find( f_mask & 1 ? f_firstname : f_secondname ) );
	return start == end ? false : findcolumn( target )( *start );
}
//******************************************************************************
// This function of main 
//******************************************************************************
int main( int ac, char* av[] )
{
	// This is flag of quastion 
	int question;
	// This is Accumulate
	double acc;

	double firstvalue;
	double secondvalue;
	string firstname;
	string secondname;
	string temp;

	cout << av[1] << " " << av[2] << endl;
	
	// This is input file
	ifstream inputfile( av[1] );
	// This is output file
	ofstream outputfile( av[2] );
	// To read file
	while( !inputfile.eof() ){
		question = 0;
		firstname.clear();
		secondname.clear();
		// To read data from file
		inputfile >> firstvalue;
		if( ( question = chackstream( inputfile ) << 1) )	
			inputfile >> temp;
		inputfile >> firstname >> temp; 
		inputfile >> secondvalue;
		if( ( question |= chackstream( inputfile ) ) ){
			//This is quastion
			if( question & 0x1 )
				inputfile >> temp;
			inputfile >> secondname;
			// To check empty parametrs
			if( secondname.empty() || firstname.empty() )
				break;
			// To clear worckspace 
			clear();
			_VecEqu.clear();
			if( !findpath( question, firstvalue, firstname, secondvalue,
					secondname ) )
				outputfile << "No conversion is possible." << endl;
			else{
				// To counting result
				acc = question & 1 ? firstvalue : secondvalue;		
				for( TIVecEqu i = _VecEqu.begin(); i != _VecEqu.end(); ++i )
					acc *= i->first; 
				outputfile << ( question & 1 ? firstvalue : acc ) << " " 
					<< firstname << " = "
					<< ( question & 1 ? acc : secondvalue ) << " " << secondname <<	endl;
				}
			}
		else{
			// This is next equvalents
			inputfile >> secondname;
			insertequ( firstvalue, firstname, secondvalue, secondname );
			}				
		}
	outputfile.close();
	inputfile.close();
	return 0;
}
