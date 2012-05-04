#ifndef _CHS_GAMEBASE_H
#define _CHS_GAMEBASE_H

//--------------------------------------------------------------------------------------------------

namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsRenderSystem;
	class ChsEngine;
  
	//------------------------------------------------------------------------------------------------
	class ChsGameBase {
  protected:
    ChsRenderSystem * renderer;
    ChsEngine * engine;
	public:
		ChsGameBase( void );
		virtual void onInit( void ) = 0;
		virtual void onUpdate( void ) = 0;
		virtual void onShutdown( void ) = 0;
    ChsRenderSystem * getRender( void );
	};
}//namespace

//--------------------------------------------------------------------------------------------------

#endif//_CHS_GAMEBASE_H
