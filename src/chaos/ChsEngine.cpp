#include "ChsEngine.h"
#include "ChsRenderFactory.h"
#include "ChsRenderSystem.h"
#include "ChsGameBase.h"
#include "ChsResourceManager.h"
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
    assert( this->getGame() );
		this->getGame()->onUpdate();
		this->getRenderSystem()->update();
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsEngine::shutdown( void ){
    assert( this->getGame() );
		this->getGame()->onShutdown();
		this->setGame( NULL );
		ChsRenderFactory::shutdown();
		ChsResourceManager::sharedInstance()->purge();
	}
  
	//------------------------------------------------------------------------------------------------
  
}
