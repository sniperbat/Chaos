#include "ChsEngine.h"
#include "ChsRenderFactory.h"
#include "ChsRenderSystem.h"
#include "ChsGameBase.h"
#include "ChsResourceManager.h"
#include "ChsHUDManager.h"
#include "ChsSceneManager.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsEngine::ChsEngine( void ) : renderSystem( NULL ), game( NULL ){
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
    ChsSceneManager::sharedInstance()->update();
    ChsHUDManager::sharedInstance()->update();
 		this->getRenderSystem()->render();
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsEngine::shutdown( void ){
		this->getGame()->onShutdown();
		this->setGame( NULL );
		ChsRenderFactory::shutdown();
    ChsSceneManager::sharedInstance()->purge();
    ChsHUDManager::sharedInstance()->purge();
		ChsResourceManager::sharedInstance()->purge();
	}
  
	//------------------------------------------------------------------------------------------------
  
}
