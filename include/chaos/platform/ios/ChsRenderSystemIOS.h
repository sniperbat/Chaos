#ifndef _CHS_RENDERSYSTEMIOS_H
#define _CHS_RENDERSYSTEMIOS_H
//--------------------------------------------------------------------------------------------------
#include "chaos/ChsRenderSystem.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsRenderSystemIOS final : public ChsRenderSystem {
	private:
		void present( void ) override;
		
		void initContext( void ) override;
		void releaseContext( void ) override;
		void attachContext( void ) override;
		
		void initRenderBuffer( void ) override;
	};

	//------------------------------------------------------------------------------------------------
	
}//namespace

//--------------------------------------------------------------------------------------------------
#endif//_CHSRENDERSYSTEMIOS_H
