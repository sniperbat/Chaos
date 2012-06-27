#include "ChsEngine.h"
#include "ChsRenderFactory.h"
#include "ChsRenderSystem.h"
#include "ChsResourceManager.h"

#include "hud/ChsHUDManager.h"

#include "framework/ChsGameBase.h"
#include "framework/ChsSceneManager.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsEngine::ChsEngine( void ) : renderSystem( nullptr ), game( nullptr ){
	}
	
	//------------------------------------------------------------------------------------------------
	ChsEngine::~ChsEngine( void ){
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsEngine::start( void ){
		//init rendersystem
		this->renderSystem = ChsRenderFactory::create();
		//init game
		assert( this->getGame() );
		this->getGame()->onInit();
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsEngine::run( void )const{
		this->getGame()->onUpdate();
    ChsSceneManager::sharedInstance()->update( 1.0f );
    ChsHUDManager::sharedInstance()->update();
 		this->getRenderSystem()->render();
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsEngine::shutdown( void ){
		this->getGame()->onShutdown();
		this->setGame( nullptr );
		ChsRenderFactory::shutdown();
    ChsSceneManager::sharedInstance()->purge();
    ChsHUDManager::sharedInstance()->purge();
		ChsResourceManager::sharedInstance()->purge();
	}
  
	//------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
