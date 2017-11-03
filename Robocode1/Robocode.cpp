//******************************************************************************
// The Robocode project.
// Programming by Butaev A.J.
//******************************************************************************
#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <memory>
#include <new>

class CDirection;
class CCommand;
class CUnit;

const int I_PIXEL_PER_SECOND( 20 );
const int I_TANK_SPEED( 1 );
const int I_BULLET_SPEED( 2 );
const int I_MAX_INT_IN_CHAR( 11 );
const int I_BATTLEFIELD_WIDTH( 120 * I_PIXEL_PER_SECOND / 10 );
const int I_BATTLEFIELD_HEIGHT( 120 * I_PIXEL_PER_SECOND / 10 );
const std::string STING_NO_WINNER( "NO WINNER!!" );

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
// The next algorithm to find pair of equal elements
template < typename Iterator, typename BinaryPredicate >
std::pair< Iterator, Iterator > find_equal( Iterator begin, Iterator end,
		BinaryPredicate pred ) {
	Iterator second( begin );
	while( begin != end ){
		second = begin;
		while( ++second != end ){
			if( pred( *begin, *second ) )
				return make_pair( begin, second );
			}
		++begin;
		}
	return make_pair( begin, second );
}

template< typename T >
inline T operator+( T f_First, T f_Second ){
	return T( static_cast< int >( f_First ) + static_cast< int >( f_Second ) );
}
template< typename T >
inline T operator+=( T& f_First, T& f_Fecond ){
	return f_First = f_First + f_Fecond;
}
template< typename T >
inline T operator%( T f_First, T f_Second ){
	return T( static_cast< int >( f_First ) % static_cast< int >( f_Second ) );
}

// The class Exception for project of Robocode.
class CRobocodeException {
	const char* pvWhat;
public:
	CRobocodeException( const char* f_What ) throw() : pvWhat( f_What ) {};
	const char* What(){ return pvWhat; };
};
// To declare type of CIntPair. 
typedef std::pair< int, int > CIntPair;
// To define an operator >> for class a CIntPair
std::istream& operator>>( std::istream& f_is, CIntPair& f_IntPair ){
	if( !( f_is >> f_IntPair.first ).good() )
		f_is.clear( std::ios_base::failbit );
	else
		f_is >> f_IntPair.second;
	return f_is;
}
// The next class a visitor. for use command
class CCommandManager {
public:
	virtual ~CCommandManager(){}
	virtual int Action( CUnit& f_Unit, CCommand& f_Command ) = 0;
};
// The next class is interface, for control a rule of game.
class CReferee : public CIntPair {
public:
	CReferee() throw() : CIntPair( -1, -1 ) {};
	virtual ~CReferee() {}
	virtual void AddUnit( CUnit& f_Unit ) throw( CRobocodeException ) = 0;
	virtual void AddBullet( CUnit& f_Unit ) throw( CRobocodeException ) = 0;
	virtual void AddCommand( const CCommand& f_Command )
			throw( CRobocodeException ) = 0;
	virtual bool StartPeriod( std::string& f_Winer ) = 0;
	virtual bool End() const throw() = 0;
};

// To pre declaration operator >> for class a CDirection, CComand. CUnit.
std::istream& operator>>( std::istream& f_is, CDirection& f_Direction );
std::istream& operator>>( std::istream& f_is, CCommand& f_Command );
std::istream& operator>>( std::istream& f_is, CUnit& f_Unit );
// To define template of function get type by name
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
// To define class of CDirection;
class CDirection {
public:
	enum TYPE{ RIGHT = 0, UP = 90, LEFT = 180, DOWN = 270, CIRCLE = 360,
			TOLEFT = -90 };
	CDirection() throw() :
		pvType( CDirection::RIGHT ) {
		pvInit();
		};
	CDirection( const CDirection& f_Direction ) throw() :
		pvType( f_Direction.pvType ) {
		pvInit();
		};
	CDirection& operator=( const CDirection& f_Direction ) throw() {
		pvType = ( f_Direction.pvType );
		return *this;
		}
	CDirection::TYPE DirectionType( ) const throw() { return pvType; };
	CDirection& operator+( const CDirection& f_Direction ) throw() {
		CDirection::TYPE Type( f_Direction.DirectionType() );
		if( Type == CDirection::UP )
			pvType = ( pvType = pvType + CDirection::UP ) % CDirection::CIRCLE;
		else if( Type == CDirection::TOLEFT )
			pvType = ( pvType = pvType + CDirection::TOLEFT ) < 0 ?
						CDirection::DOWN : pvType;
		else
			pvType = ( pvType + CDirection::LEFT ) % CDirection::CIRCLE;
		return *this;
		}
private:
	friend std::istream& operator>>( std::istream& f_is, CDirection& f_Direction );
	CDirection::TYPE pvType;
	static std::vector< std::pair< std::string, CDirection::TYPE > >
			pvDirectionType;
	void pvInit() throw() {
		if( pvDirectionType.empty() ){
			pvDirectionType.push_back(
					std::pair< std::string, CDirection::TYPE >( "0", CDirection::RIGHT ) );
			pvDirectionType.push_back(
					std::pair< std::string, CDirection::TYPE >( "90", CDirection::UP ) );
			pvDirectionType.push_back(
					std::pair< std::string, CDirection::TYPE >( "-90", CDirection::TOLEFT ) );
			pvDirectionType.push_back(
					std::pair< std::string, CDirection::TYPE >( "180", CDirection::LEFT ) );
			pvDirectionType.push_back(
					std::pair< std::string, CDirection::TYPE >( "270", CDirection::DOWN ) );
		}
	}
};
// Define static of member of class a CDirection
std::vector< std::pair< std::string, CDirection::TYPE > >
		CDirection::pvDirectionType;
// To define operator >> for class a TDirection
std::istream& operator>>(std::istream& f_is, CDirection& f_Direct ) {
	std::string temp;
	try{
		if( !( f_is >> temp ).fail() )
			f_Direct.pvType = GetType< CDirection::TYPE >( f_Direct.pvDirectionType,
					temp );
		}
	catch( CRobocodeException& err ) {
		std::cerr << err.What() << std::endl;
		f_is.clear( std::ios_base::failbit );
		}
	return f_is;
};
// Define class a command.
class CCommand{
public:
	enum TYPE{ MOVE, STOP, TURN, SHOOT, UNKNOWN };
	CCommand() throw() : pvType( CCommand::UNKNOWN ), pvTime( 0 ),
		pvAngle(), pvTo() {
		pvInit();
		};
	CCommand( CCommand::TYPE f_Type, int f_Time, CDirection f_Angle ) throw() :
			pvType( f_Type ), pvTime( f_Time * I_PIXEL_PER_SECOND / 10 ),
			pvAngle( f_Angle ), pvTo() {
		pvInit();
		};
	CCommand( const CCommand& f_Command ) throw() : pvType( f_Command.pvType ),
			pvTime( f_Command.pvTime ), pvAngle( f_Command.pvAngle ),
			pvTo( f_Command.pvTo ) {
		pvInit();
		};
	CCommand& operator=( const CCommand& f_Command ) throw(){
		pvType = f_Command.pvType;
		pvTime = f_Command.pvTime;
		pvAngle = f_Command.pvAngle;
		pvTo = f_Command.pvTo;
		return *this;
		};
	const std::string& To() const throw() { return pvTo; };
	int UseCommand( CCommand::TYPE& f_Type, CDirection& f_Angle ) throw(){
		f_Type = pvType;
		f_Angle = pvAngle;
		return pvTime--;
		};
	CCommand::TYPE Type() { return pvType; };
private:
	CCommand::TYPE pvType;
	int pvTime;
	CDirection pvAngle;
	std::string pvTo;
	friend std::istream& operator>>( std::istream& f_is, CCommand& f_Cmd );
	static std::vector< std::pair< std::string, CCommand::TYPE > > pvCommandType;
	void pvInit() {
		if( pvCommandType.empty() ){
			pvCommandType.push_back(
				std::pair< std::string, CCommand::TYPE >( "MOVE", CCommand::MOVE ) );
			pvCommandType.push_back(
				std::pair< std::string, CCommand::TYPE >( "STOP", CCommand::STOP ) );
			pvCommandType.push_back(
					std::pair< std::string, CCommand::TYPE >( "TURN", CCommand::TURN ) );
			pvCommandType.push_back(
					std::pair< std::string, CCommand::TYPE >( "SHOOT", CCommand::SHOOT ) );
			}
		}
};
//******************************************************************************
std::vector< std::pair< std::string, CCommand::TYPE > > CCommand::pvCommandType;
// The operator>> for class a CCommand.
std::istream& operator>>( std::istream& f_is, CCommand& f_Command ){
	std::string type;
	int time;
	if( ( f_is >> time ).fail() )
		return f_is;
	else if( ( f_is >> f_Command.pvTo ).fail() )
		return f_is;
	else if( ( f_is >> type ).fail() )
		return f_is;
	else {
		try {
			f_Command.pvType = GetType< CCommand::TYPE >( f_Command.pvCommandType,
					type );
			}
		catch( CRobocodeException& err ){
			std::cerr << err.What() << std::endl;
			f_is.clear( std::ios_base::failbit );
			return f_is;
			}
		}
	if( f_Command.pvType == CCommand::TURN || f_is.good() )
			f_is >> f_Command.pvAngle;
	f_Command.pvTime = time * I_PIXEL_PER_SECOND;
	return f_is;
};
// Declare type queue of command.
typedef std::queue< CCommand > CCommandQueue;
// Declare class of unit
class CUnit : public CIntPair, public CDirection {
public:
	enum TYPE{ TANK, BULLET };
	CUnit() throw() {};
	CUnit( CIntPair f_IntPair, CDirection f_Direction, CUnit::TYPE f_Type,
			const std::string& f_Name ) throw() : CIntPair( f_IntPair ),
			CDirection( f_Direction ), pvType( f_Type ), pvName( f_Name ) {};
	CUnit( const CUnit& f_Unit ) throw() : CIntPair( f_Unit ),
		CDirection( f_Unit ), pvType( f_Unit.pvType ), pvName( f_Unit.pvName ),
		pvQueueCommand( f_Unit.pvQueueCommand ){};
	CUnit& operator=( const CUnit& f_Unit ) throw() {
		static_cast< CIntPair& >( *this ) = f_Unit;
		static_cast< CDirection& >( *this ) = f_Unit;
		pvType = f_Unit.pvType;
		pvName = f_Unit.pvName;
		pvQueueCommand = f_Unit.pvQueueCommand;
		return *this;
		};
	void AddCommand( const CCommand& f_Command ) throw() {
		pvQueueCommand.push( f_Command );
		};
	std::size_t HaveCommand() const { return pvQueueCommand.size(); };
	const std::string& Name() const throw() { return pvName; };
	const CUnit::TYPE& UnitType() const throw() { return pvType; };
	void Action( CCommandManager& f_CommandManager ){
		if( !pvQueueCommand.empty() ){
			CCommand& Command( pvQueueCommand.front() );
			if( !f_CommandManager.Action( *this, Command ) && pvType ==
					CUnit::TANK )
				pvQueueCommand.pop();
			}
		}
private:
	friend std::istream& operator>>( std::istream& f_is, CUnit& f_Unit );
	CUnit::TYPE pvType;
	std::string pvName;
	CCommandQueue pvQueueCommand;
};
// The operator>> for class a CCommand.
std::istream& operator>>( std::istream& f_is, CUnit& f_Unit ){
	f_Unit.pvType = CUnit::TANK;
	CIntPair IntPair;
	if( !( f_is >> f_Unit.pvName).good() ){
		f_is.clear( std::ios_base::failbit );
		return f_is;
		}
	else if( ( f_is >> IntPair  ).fail() )
		return f_is;
	else
		f_is >> static_cast< CDirection& >( f_Unit );
	IntPair.first *= I_PIXEL_PER_SECOND / 10;
	IntPair.second *= I_PIXEL_PER_SECOND / 10;
	static_cast< CIntPair& >( f_Unit ) = IntPair;
	return f_is;
}
// The class of function.
// The given class compares a name of the unit with required
class CFindUnitByName : public std::binary_function< CUnit, std::string, bool >{
public:
	bool operator()( const CUnit& f_Unit, const std::string& f_Name ) const {
		return f_Unit.Name() == f_Name;
	}
};
// The class of function.
// The given class compares a type of the unit with required
class CFindUnitByType : public std::binary_function< CUnit, CUnit::TYPE, bool >{
public:
	bool operator()( const CUnit& f_Unit, const CUnit::TYPE& f_Type ) const {
		return f_Unit.UnitType() == f_Type;
	}
};
// The command manager for Robocode project
class CRobocodeCommandManager : public CCommandManager {
	void pvMove( CUnit& f_Unit ) {
		CDirection::TYPE Direction( f_Unit.DirectionType() );
		int speed( f_Unit.UnitType() == CUnit::TANK ? I_TANK_SPEED : I_BULLET_SPEED );
		int* Axis = ( Direction == CDirection::RIGHT ||
				Direction == CDirection::LEFT ) ? &f_Unit.first : &f_Unit.second;
		*Axis = ( Direction == CDirection::RIGHT || Direction == CDirection::UP ) ?
				*Axis + speed : *Axis - speed;
	};
	CReferee& pvReferee;
	unsigned int pvShootCount;
public:
	CRobocodeCommandManager( CReferee& f_Referee ) throw () :
		pvReferee( f_Referee ), pvShootCount( 0 ) {};
	int Action( CUnit& f_Unit, CCommand& f_Command ) {
		CCommand::TYPE Type;
		CDirection Angle;
		int Time = f_Command.UseCommand( Type, Angle );
		if( Type == CCommand::MOVE )
			pvMove( f_Unit );
		else if( Type == CCommand::TURN && !( Time % I_PIXEL_PER_SECOND ) )
			static_cast< CDirection >( f_Unit ) = static_cast< CDirection >( f_Unit )
					+ Angle;
		else if( Type == CCommand::SHOOT && !( Time % I_PIXEL_PER_SECOND ) ){
			CUnit bullet( f_Unit, f_Unit, CUnit::BULLET, "BULLET" );
			bullet.AddCommand( CCommand( CCommand::MOVE, 10, f_Unit ) );
			pvMove( bullet );
			pvReferee.AddBullet( bullet );
			}
		return ( --Time % I_PIXEL_PER_SECOND );;
	}
};
//The rule of Robocode game.
class CRobocodeReferee : public CReferee {
	// first - Count of unit on battlefielf. second - Count of command for Unit
	std::auto_ptr< CCommandManager > pvCommandManager;
	typedef std::vector< CUnit > CBattlefield;
	typedef CBattlefield::iterator CBattlefieldIterator;
	typedef std::pair< CBattlefieldIterator, CBattlefieldIterator > CHit;
	CBattlefield pvBattlefield;
	CBattlefield pvBullet;
	// To check up an output for limits of a battlefield.
	class COutOfRange : public std::unary_function< CUnit , bool >{
	public:
		bool operator()( CUnit& f_Unit ) throw() {
			if( f_Unit.UnitType() == CUnit::TANK ){
				f_Unit.first = f_Unit.first > I_BATTLEFIELD_WIDTH ?
						I_BATTLEFIELD_WIDTH : f_Unit.first < 0 ? 0 : f_Unit.first;
				f_Unit.second = f_Unit.second > I_BATTLEFIELD_HEIGHT ?
						I_BATTLEFIELD_HEIGHT : f_Unit.second < 0 ? 0 : f_Unit.second;
				return false;
				}
			else{
				if( f_Unit.first < 0 || f_Unit.first > I_BATTLEFIELD_WIDTH )
					return true;
				else if( f_Unit.second < 0 || f_Unit.second > I_BATTLEFIELD_HEIGHT )
					return true;
				else
					return false;
				}
			};
		};
	//To check up hit.
	class CHitTest : public std::binary_function< CUnit, CUnit, bool >{
	public:
		bool operator()( const CUnit& f_First, const CUnit& f_Second ) const {
			return f_First.Name() != f_Second.Name() && 
					static_cast< const CIntPair& >( f_First ) ==
					static_cast< const CIntPair& >( f_Second );
			}
		};
public:
	CRobocodeReferee() throw( CRobocodeException ) {
		try{
			pvCommandManager = std::auto_ptr< CCommandManager >(
					new CRobocodeCommandManager( *this ) );
			}
		catch( std::bad_alloc ){
			throw( CRobocodeException( "Can`t create a Referee class." ) );
			}
		}
	void AddUnit( CUnit& f_Unit ) throw( CRobocodeException ) {
		if( pvBattlefield.size() >= static_cast< std::size_t >( first ) )
			throw( CRobocodeException( "The limit of tanks is exceeded" ) );
		pvBattlefield.push_back( f_Unit );
		};
	void AddBullet( CUnit& f_Unit ) throw( CRobocodeException ){
		pvBullet.push_back( f_Unit );
		}
	void AddCommand( const CCommand& f_Command )
			throw( CRobocodeException ) {
		// As the index on the end is used twice. We create a variable.
		CBattlefieldIterator End( pvBattlefield.end() );
		// to find tank by name
		CBattlefieldIterator Tank( std::find_if( pvBattlefield.begin(), End,
				std::bind2nd( CFindUnitByName(), f_Command.To() ) ) );
		if( Tank == End )
			throw( CRobocodeException( "The tank for which belongs a command"
					" is not found" ) );
		if( Tank->HaveCommand() >= static_cast< std::size_t >( second ) )
			throw( CRobocodeException( "The limit of command is exceeded" ) );
		Tank->AddCommand( f_Command );
		}
	bool StartPeriod( std::string& f_Winer ){
		if( !pvBattlefield.size() )
			return false;
		CUnit::TYPE BulletType( CUnit::BULLET );
		while( true ) {
			if( pvBattlefield.empty() ){
				f_Winer = STING_NO_WINNER;
				break;
				}
			if( pvBattlefield.size() == 1 &&
					pvBattlefield.front().UnitType() == CUnit::TANK ){
				f_Winer = pvBattlefield.front().Name();
				break;
				}
			// To check up presence of commands at unit being on a battlefield and
			// To check up presence bullet on the battlefield.;
			if( std::find_if( pvBattlefield.begin(), pvBattlefield.end(),
						std::mem_fun_ref( &CUnit::HaveCommand ) ) == pvBattlefield.end()
						&& std::find_if( pvBattlefield.begin(), pvBattlefield.end(),
						std::bind2nd( CFindUnitByType(), BulletType ) ) ==
						pvBattlefield.end() ){
				f_Winer = STING_NO_WINNER;
				break;
				}
			// One second in game
			for( int loop = 0; loop < I_PIXEL_PER_SECOND; ++loop ){
				// To make action of each unit
				for( CBattlefieldIterator UnitPtr( pvBattlefield.begin() );
						UnitPtr != pvBattlefield.end(); ++UnitPtr )
					UnitPtr->Action( *pvCommandManager );
				// To check a have new bullet.
				if( !pvBullet.empty() ){
					pvBattlefield.insert( pvBattlefield.end(), pvBullet.begin(),
							pvBullet.end() );
					pvBullet.clear();
					}
				// To check position of unit and remove bullet outside.
				pvBattlefield.erase( remove_if( pvBattlefield.begin(),
						pvBattlefield.end(), CRobocodeReferee::COutOfRange() ),
						pvBattlefield.end() );
				// To check hit heppenes
				bool loop( true );
				while( loop ){
					CHit Hit( find_equal( pvBattlefield.begin(), pvBattlefield.end(),
							CRobocodeReferee::CHitTest() ) );
					if( ( loop = Hit.first != Hit.second ) ){
						// To remove the collided objects
						pvBattlefield.erase( Hit.first );
						pvBattlefield.erase( Hit.second );
						}
					}
				}
			}
		// To clear of battlefield/ for next game.
		pvBattlefield.clear();
		return true;
		};
	bool End() const throw() { return !static_cast< bool >( first || second ); };

};
// Is Referee.
bool IsReferee( const std::string& f_String, CReferee& f_Referee ){
	std::istringstream ss( f_String );
	return ( ss >> static_cast< CIntPair& >( f_Referee ) ).eof();
}
// Is Unit.
bool IsUnit( const std::string& f_String, CUnit& f_Unit ){
	std::istringstream ss( f_String );
	return ( ss >> f_Unit ).eof();
}
// Is Command.
bool IsCommand( const std::string& f_String, CCommand& f_Command ){
	std::istringstream ss( f_String );
	return ( ss >> f_Command ).eof();
}
