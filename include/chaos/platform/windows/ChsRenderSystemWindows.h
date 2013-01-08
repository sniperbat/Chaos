#ifndef _CHS_RENDERSYSTEMWINDOWS_H
#define _CHS_RENDERSYSTEMWINDOWS_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "chaos/ChsRenderSystem.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsRenderSystemWindows final : public ChsRenderSystem {
	private:
		void present( void ) override;
		
		void initContext( void ) override;
		void releaseContext( void ) override;
		void attachContext( void ) override;
		
		void initRenderBuffer( void ) override;
	};

}//namespace

#endif//_CHSRENDERSYSTEMWINDOWS_H
