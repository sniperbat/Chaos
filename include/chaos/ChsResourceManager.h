#ifndef _CHS_RESOURCEMANAGER_H
#define _CHS_RESOURCEMANAGER_H
//--------------------------------------------------------------------------------------------------
#include "core/ChsSingleton.h"
#include "ChsEntityManager.h"
#include "ChsTextureManager.h"
#include "ChsModelManager.h"
#include "shader/ChsShaderManager.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	class ChsResourceManager final :	public ChsSingleton< ChsResourceManager >,
                              public ChsShaderManager,
                              public ChsEntityManager,
                              public ChsTextureManager,
                              public ChsModelManager
	{
	public:
		void purge( void ) override;
	};
  
	//------------------------------------------------------------------------------------------------

}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_RESOURCEMANAGER_H
