#ifndef _CHS_TEXTUREFACTORYIOS_H
#define _CHS_TEXTUREFACTORYIOS_H
//--------------------------------------------------------------------------------------------------
#include "ChsTextureFactory.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	class ChsTextureFactoryIOS final : public ChsTextureFactory {
	public:
		ChsTexture2D * createTexture2D( const char * filename ) override;
	};
	
  //------------------------------------------------------------------------------------------------

}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_TEXTUREFACTORYIOS_H
