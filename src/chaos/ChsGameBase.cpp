#include "ChsGameBase.h"
#include "ChsRenderNode.h"
#include "ChsEngine.h"
#include "ChsRenderSystem.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	ChsGameBase::ChsGameBase( void ) : renderer( nullptr ){
		this->engine = ChsEngine::sharedInstance();
		this->engine->setGame( this );
	}

	//------------------------------------------------------------------------------------------------
	ChsRenderSystem * ChsGameBase::getRender( void ){
		return this->renderer ? this->renderer : this->renderer = this->engine->getRenderSystem();
	}
	
  //------------------------------------------------------------------------------------------------

}
