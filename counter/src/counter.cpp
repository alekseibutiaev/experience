//============================================================================
// Name        : counter.cpp
// Author      : Butyaev A.J.
// Version     : 0.1
// Copyright   : GPLv2
// Description : Coounter in C++, Ansi-style
// e-mail      : primary alexsy@samaradom.ru.
//             : secondary alexsy@list.ru, alexsyrezerv@mail.ru
//============================================================================

#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <functional>

typedef std::vector< std::string > CArrayString;
typedef std::insert_iterator< CArrayString > CInsertIterator;

//*****************************************************************************
// Compare char insensitively case
//*****************************************************************************
class CCharCompare : public std::binary_function< std::string::value_type,
		std::string::value_type, bool >{
public:
	bool operator()( const std::string::value_type& f_A,
			const std::string::value_type& f_B ){
		return toupper( f_A ) < toupper( f_B );
	}
};
typedef std::map< std::string::value_type, unsigned int, CCharCompare >
		CMapLetters;
typedef CMapLetters::value_type CLetterCounter;
typedef CMapLetters::iterator CIteratorMapLetters;
//*****************************************************************************
// Convert std::string from lowercase letter to uppercase
//*****************************************************************************
class CUpper : public std::unary_function< std::string, std::string > {
public:
	const std::string operator()( const std::string& f_Word ) {
		std::string word( f_Word );
		// Convert lowercase letter to uppercase
		std::transform( word.begin(), word.end(), word.begin(),
				static_cast< int(*)(int) >( toupper ) );
		return word;
	}
};
//*****************************************************************************
// Compare std::string insensitively case
//*****************************************************************************
class CStringCompare : public std::binary_function< std::string, std::string,
		bool >{
public:
	bool operator()( const std::string& f_A, const std::string& f_B ){
		CUpper upper;
		return upper( f_A ) < upper( f_B );
	}
};
typedef std::map< std::string, unsigned int, CStringCompare > CMapWords;
typedef CMapWords::value_type CWordCounter;
typedef CMapWords::iterator CIteratorMapWords;
//*****************************************************************************
// delete punctuation marks & test words
//*****************************************************************************
class CFilter : public std::unary_function< std::string, bool >{
public:
	bool operator()( std::string& f_Word ){
		// test bad word. example "test(854)", "63.sd23" or "wo364rd" is bad
		if( find_if( f_Word.begin(), f_Word.end(),
				static_cast< int(*)(int) >( isdigit )  ) != f_Word.end() )
			return true;
		// delete punctuation character. example 
		f_Word.erase( std::remove_if( f_Word.begin(), f_Word.end(),
				static_cast< int(*)(int) >( ispunct ) ), f_Word.end() );
		return false;
	}
};
//*****************************************************************************
// insert to map new element or count if element exist
//*****************************************************************************
template< typename MatType >
class CInsert : public std::unary_function< typename MatType::key_type, void > {
	typedef typename MatType::iterator CMatTypeIterator;
	typedef typename MatType::value_type CMatTypeValue;
	typedef std::pair< CMatTypeIterator, bool > CInsertResult;
	MatType& pvMap;
public:
	explicit CInsert( MatType& f_Map ) : pvMap( f_Map ) {};
	void operator()( const typename MatType::key_type& f_Key ){
		// insert next element
		CInsertResult res( pvMap.insert( CMatTypeValue(  f_Key, 1 ) ) );
		if( !res.second )
			// element exist, increment of counter
			++(res.first->second);
	}
};
//*****************************************************************************
// Fill map
//*****************************************************************************
template< typename MatType, typename DataType >
class CFillMap : public std::unary_function< DataType, void > {
	MatType& pvMap;
public:
	explicit CFillMap( MatType& f_Map ) : pvMap( f_Map ) {};
	void operator()( const DataType& f_Data ){
		// Count letters in words
		std::for_each( f_Data.begin(), f_Data.end(), CInsert< MatType >( pvMap ) );
	}
};
//*****************************************************************************
// The overloaded operator << for type CLetterCounter
//*****************************************************************************
std::ostream& operator<< ( std::ostream& f_out,
		const CLetterCounter f_LetterCounter ){
	f_out << f_LetterCounter.first << " - " << f_LetterCounter.second;
	return f_out;
}
//*****************************************************************************
// The overloaded operator << for type CWordCounter
//*****************************************************************************
std::ostream& operator<< ( std::ostream& f_out,
		const CWordCounter f_WordCounter ){
	f_out << f_WordCounter.first << " - " << f_WordCounter.second;
	return f_out;
}
//*****************************************************************************
// The main
//*****************************************************************************
int main( int ac, char* av[] ) {
	// Create buffer of words.
	CArrayString ArrayString;
	// Create map of letters.
	CMapLetters MapLetters;
	// Create map of word/
	CMapWords MapWords;
	//Get words from input stream.
	std::copy( std::istream_iterator< std::string >( std::cin ),
			std::istream_iterator< std::string >(),
			CInsertIterator( ArrayString, ArrayString.begin() ) );
	// Clear punctuation character & bad words.
	ArrayString.erase( std::remove_if( ArrayString.begin(), ArrayString.end(),
			CFilter() ) , ArrayString.end() );
	// Count letters in all words.
	std::for_each( ArrayString.begin(), ArrayString.end(),
			CFillMap< CMapLetters, CArrayString::value_type >( MapLetters ) );
	// Count words in buffer of words.
	// Create functor
	CFillMap< CMapWords, CArrayString > count( MapWords );
	// Using functor
	count( ArrayString );
	// delete not unique of words
	for( CIteratorMapWords iter( MapWords.begin() ); iter != MapWords.end(); ){
		if( iter->second > 1 )
			MapWords.erase( iter++ );
		else
			++iter;
		}
	// output result.
	std::cout << "Unique words count:" << std::endl;
	std::cout << MapWords.size() << std::endl << "Unique words:" << std::endl;
	// Show unique words.
	for( CIteratorMapWords i( MapWords.begin() ); i != MapWords.end(); ++i )
		std::cout << i->first << ", ";
	std::cout << std::endl << "Letter distribution:" << std::endl;
	// Show letters.
	for( CIteratorMapLetters i( MapLetters.begin() ); i != MapLetters.end();
			++i )
		std::cout << *i << std::endl;
	return 0;
}
