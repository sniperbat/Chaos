#ifndef _CHS_UTILITY_H
#define _CHS_UTILITY_H

#include <vector>
#include <boost/foreach.hpp>
#include <boost/checked_delete.hpp>
#define BOOST_NO_CHAR16_T
#define BOOST_NO_CHAR32_T
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "ChsDefine.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	size_t getGLDataTypeSize( int type );
  int getTexWrapValue( const std::string & valueName );
	//------------------------------------------------------------------------------------------------
	template< typename Type > void safeRelease( Type **pptr ) {
		if ( * pptr ) {
			( * pptr )->Release();
			* pptr = nullptr;
		}
	}

	//------------------------------------------------------------------------------------------------
	template< typename Type > void safeRelease( Type **pptr, std::string msg ) {
		if ( * pptr ) {
			( * pptr )->Release();
			* pptr = nullptr;
			//if(!msg.empty())
			//LOGMSG(msg.c_str());
		}
	}

	//------------------------------------------------------------------------------------------------
	template< typename Type > void safeDelete( Type ** pptr ) {
		if( * pptr ) {
			boost::checked_delete( * pptr );
			* pptr = nullptr;
		}
	}

  //------------------------------------------------------------------------------------------------
	template< typename Type > void safeDelete( Type ** pptr, std::string msg ) {
		if( * pptr ) {
			//LOGMSG(msg.c_str());
			boost::checked_delete( * pptr );
			*pptr = nullptr;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	template< typename Type > void safeDeleteArray( Type ** pArrayPtr ) {
		if( * pArrayPtr ) {
			boost::checked_array_delete( * pArrayPtr );
			*pArrayPtr = nullptr;
		}
	}

	//------------------------------------------------------------------------------------------------
	template< typename Type > void safeDeleteArray( Type ** pArrayPtr, std::string msg ) {
		if( * pArrayPtr ) {
			//LOGMSG(msg.c_str());
			boost::checked_array_delete( * pArrayPtr );
			*pArrayPtr = nullptr;
		}
	}

	//------------------------------------------------------------------------------------------------
	template<typename T>
	void lexicalCastToArray( std::vector<T> & array, std::string stream ){
		std::vector<std::string> rs;
		boost::split( rs, stream, boost::is_any_of("\n ") );
		BOOST_FOREACH( const std::string & str, rs){
			if(!str.empty())
				array.push_back( boost::lexical_cast<T>( str ) );
		}
	}
	
	//------------------------------------------------------------------------------------------------
	template<typename T>
	void skipData( T * & data, int count ){
		data += count;
	}
  
  //------------------------------------------------------------------------------------------------
	template<typename T>
	T readData( char * & data ){
		T value = *( reinterpret_cast<T*>( data ) );
		skipData( data, sizeof( T ) );
		return value;
	}
  
  //------------------------------------------------------------------------------------------------
	std::string readString( char * & data );

}//namespace

#endif //_CHS_UTILITY_H
