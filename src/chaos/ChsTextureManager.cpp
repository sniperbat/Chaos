#include "ChsTextureManager.h"
#include "ChsTextureFactory.h"
#include "ChsTexture2D.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsTexture2D> ChsTextureManager::getTexture2D( const std::string & name ){
		boost::shared_ptr<ChsTexture2D> texture = this->getFromCache( name );
		if( !texture ){
      std::string fullpath = "assets/" + name;
			texture.reset( ChsTextureFactory::sharedInstance()->createTexture2D( fullpath.c_str() ) );
			if( texture ){
				printf( "生成texture:%s\n", fullpath.c_str() );
				insert( this->cache )( name, texture );
			}
		}
	  return texture;
	}
	
	//------------------------------------------------------------------------------------------------
	
}
