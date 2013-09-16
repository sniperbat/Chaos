#include "ChsTextureManager.h"
#include "ChsTextureFactory.h"
#include "ChsTexture2D.h"
#include "ChsTextureEntity.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	std::shared_ptr<ChsTexture2D> ChsTextureManager::getTexture2D( const std::string & name ){
		std::shared_ptr<ChsTexture2D> texture = this->getFromCache( name );
		if( !texture ){
      std::string fullpath = "assets/" + name;
			texture.reset( ChsTextureFactory::sharedInstance()->createTexture2D( fullpath.c_str() ) );
			if( texture ){
				printf( "生成texture:%s\n", fullpath.c_str() );
        this->cache.insert( std::make_pair( name, texture ) );
			}
		}
	  return texture;
	}
	
	//------------------------------------------------------------------------------------------------
	std::shared_ptr<ChsTextureEntity> ChsTextureManager::getTextureEntity( const std::string & name ){
    return std::shared_ptr<ChsTextureEntity> ( new ChsTextureEntity( this->getTexture2D( name ) ) );
  }
  
  //------------------------------------------------------------------------------------------------
}

//--------------------------------------------------------------------------------------------------
