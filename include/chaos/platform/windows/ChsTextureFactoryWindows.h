#ifndef _CHS_TEXTUREFACTORYWINDOWS_H
#define _CHS_TEXTUREFACTORYWINDOWS_H

#include "ChsTextureFactory.h"
//--------------------------------------------------------------------------------------------------

namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	class ChsTextureFactoryWindows : public ChsTextureFactory {
	public:
		ChsTexture2D * createTexture2D( const char * filename );
	};
	
  //------------------------------------------------------------------------------------------------
}

#endif//_CHS_TEXTUREFACTORYWINDOWS_H
