#ifndef _CHS_TEXTUREMANAGER_H
#define _CHS_TEXTUREMANAGER_H
//--------------------------------------------------------------------------------------------------
#include "ChsManagerWithCache.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{
  
  //------------------------------------------------------------------------------------------------
	class ChsTexture2D;	
  class ChsTextureEntity;
	//------------------------------------------------------------------------------------------------
	class ChsTextureManager : public ChsManagerWithCache< ChsTexture2D > {
	public:
		std::shared_ptr<ChsTexture2D> getTexture2D( const std::string & name );
 		std::shared_ptr<ChsTextureEntity> getTextureEntity( const std::string & name );
	};
	
	//------------------------------------------------------------------------------------------------
	
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_TEXTUREMANAGER_H
