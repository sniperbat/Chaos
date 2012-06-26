#include <string>
#include "io/ChsFileSystem.h"
#include "ChsTextureFactoryWindows.h"
#include "ChsTexture2D.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	ChsTextureFactoryWindows gTextureFactory;
	
  //------------------------------------------------------------------------------------------------
	ChsTexture2D * ChsTextureFactoryWindows::createTexture2D( const char * path ){
		std::string fileName = path;

    ChsTexture2D * texture = new ChsTexture2D();
//		texture->build( width, height, format, imgData );
		return texture;
	}
  
  //------------------------------------------------------------------------------------------------
}
