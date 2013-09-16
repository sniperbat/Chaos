#ifndef _CHS_MANAGERWITHCACHE_H
#define _CHS_MANAGERWITHCACHE_H
//--------------------------------------------------------------------------------------------------
#include <map>
#include "core/ChsUtility.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	template <typename ValueType> class ChsManagerWithCache {
	public:
    virtual void purge( void );
	protected:
		typedef std::map< std::string, std::shared_ptr<ValueType> > CacheType;
	  CacheType cache;
		std::shared_ptr<ValueType> getFromCache( const std::string & key );
		void remove( const std::string & key );
	};

	//------------------------------------------------------------------------------------------------
	template < typename ValueType >
	void ChsManagerWithCache< ValueType >::purge( void ) {
		this->cache.clear();
	}
	
	//------------------------------------------------------------------------------------------------
	template < typename ValueType >
	std::shared_ptr<ValueType> ChsManagerWithCache< ValueType >::getFromCache( const std::string & key ){
		std::shared_ptr<ValueType> objPtr;
		typename CacheType::iterator iter = this->cache.find( key );
		if( iter != this->cache.end() )
			objPtr = iter->second;
		return objPtr;
	}
	
	//------------------------------------------------------------------------------------------------
	template < typename ValueType >
	void ChsManagerWithCache< ValueType >::remove( const std::string & key ){
		this->cache.erase( key );
	}
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_MANAGERWITHCACHE_H
