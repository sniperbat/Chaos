#ifndef _CHS_RENDERSYSTEMWINDOWS_H
#define _CHS_RENDERSYSTEMWINDOWS_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "chaos/ChsRenderSystem.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsRenderSystemWindows : public ChsRenderSystem {
	private:
		void present( void );
		
		void initContext( void );
		void releaseContext( void );
		void attachContext( void );
		
		void initRenderBuffer( void );
	};

}//namespace

#endif//_CHSRENDERSYSTEMWINDOWS_H
