#include "GameDemo.h"
#include "ChsEntity.h"
#include "ChsResourceManager.h"
#include "ChsRenderSystem.h"
#include "geometry/ChsPlane.h"
#include "ChsMaterial.h"
#include "ChsShaderProgram.h"
#include "camera/ChsCamera.h"
#include "math/ChsMath.h"
#include "ChsDaeLoader.h"
#include <boost/shared_ptr.hpp>
#include "ChsTexture2D.h"
#include "ChsModel.h"
#include "ChsHUDManager.h"
#include "ChsSceneManager.h"
//--------------------------------------------------------------------------------------------------
using namespace Chaos;
#include <math.h>

GameDemo game;
boost::scoped_ptr<ChsCamera> camera(new ChsCamera());
static float transY = 0.0f;
ChsMaterial * material;
ChsPlane * planeMesh1;
//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
	ChsRect viewport = this->getRender()->getViewPort();
	camera->perspective( degree2Radian(39.6), viewport.w/(float)viewport.h, 0.1f, 1000.0f  );
	
  this->getRender()->setCurrentCamera( camera.get() );
	this->getRender()->showDebugCoordinate( true );
	
	ChsModel * model = ChsResourceManager::sharedInstance()->getModel( "sofa.chsmodelx" ).get();
	ChsSceneManager::sharedInstance()->getRoot()->add( model );
  
  ChsHUDManager::sharedInstance()->loadHUD( "demo.chshud" );
  ChsHUDManager::sharedInstance()->showHUD( "demo.chshud" );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
	transY += 0.0075f;
	//float alpha = sin(transY);
	camera->moveTo( cos(transY)*5, 1, sin(transY)*5 );
	//alpha = alpha >=0 ? alpha : -alpha;
	//material = planeMesh1->getMaterial();
	//material->alpha(1.0f-alpha);
	
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}
