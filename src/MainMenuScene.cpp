#include "camera/ChsModelViewCamera.h"
#include "io/ChsTouchEmitter.h"
#include "ChsResourceManager.h"
#include "hud/ChsHUDManager.h"
#include "ChsEngine.h"
#include "ChsModel.h"
#include "MainMenuScene.h"

using namespace Chaos;

//--------------------------------------------------------------------------------------------------
//must do this, any other solutions??
static bool isDynamic = MainMenuScene::registerAsDynamic( "MainMenuScene" ); 

//--------------------------------------------------------------------------------------------------
boost::shared_ptr<ChsModelViewCamera> camera( new ChsModelViewCamera() );

//--------------------------------------------------------------------------------------------------
MainMenuScene::MainMenuScene( void ){
}

//--------------------------------------------------------------------------------------------------
MainMenuScene::~MainMenuScene( void ){
}

//--------------------------------------------------------------------------------------------------
void MainMenuScene::onEnter( void ){
  ChsTouchEmitter::sharedInstance()->addListener( camera );
	ChsModel * model = ChsResourceManager::sharedInstance()->getModel( "test.chsmodel" ).get();
  this->add( model );
  ChsHUDManager::sharedInstance()->showHUD( "demo.chshud" );
}

//--------------------------------------------------------------------------------------------------
void MainMenuScene::onExit( void ){
  ChsTouchEmitter::sharedInstance()->removeListener( camera );
  this->remove( "test.chsmodel" );
  ChsHUDManager::sharedInstance()->hideHUD( "demo.chshud" );
}

//--------------------------------------------------------------------------------------------------
void MainMenuScene::onUpdate( double timeInterval ){
}

//--------------------------------------------------------------------------------------------------
void MainMenuScene::onInit( void ){
  ChsEngine * engine = ChsEngine::sharedInstance();
  ChsRect<int> viewport = engine->getRenderSystem()->getViewport();
  camera->perspective( degree2Radian(39.6f), viewport.w/(float)viewport.h, 0.1f, 1000.0f  );
  camera->setScreen( viewport.w, viewport.h );
  engine->getRenderSystem()->setCurrentCamera( camera.get() );
  
	engine->getRenderSystem()->toggleDebugCoordinate( true );
  ChsHUDManager::sharedInstance()->loadHUD( "demo.chshud" );
}

//--------------------------------------------------------------------------------------------------
void MainMenuScene::onRelease( void ){
  
}

//--------------------------------------------------------------------------------------------------
