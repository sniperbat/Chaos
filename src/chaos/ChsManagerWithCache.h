#ifndef _CHS_MANAGERWITHCACHE_H
#define _CHS_MANAGERWITHCACHE_H

#include "ChsUtility.h"
//--------------------------------------------------------------------------------------------------

namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	template <typename ValueType> class ChsManagerWithCache {
	public:
    void purge( void );
	protected:
		typedef std::map< std::string, boost::shared_ptr<ValueType> > CacheType;
	  CacheType cache;
		boost::shared_ptr<ValueType> getFromCache( const std::string & key );
		void remove( const std::string & key );
	};

	//------------------------------------------------------------------------------------------------
	template < typename ValueType >
	void ChsManagerWithCache< ValueType >::purge( void ) {
		this->cache.clear();
	}
	
	//------------------------------------------------------------------------------------------------
	template < typename ValueType >
	boost::shared_ptr<ValueType> ChsManagerWithCache< ValueType >::getFromCache( const std::string & key ){
		boost::shared_ptr<ValueType> objPtr;
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


#endif//_CHS_MANAGERWITHCACHE_H
