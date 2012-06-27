#include "camera/ChsModelViewCamera.h"
#include "io/ChsTouchEmitter.h"
#include "ChsResourceManager.h"
#include "hud/ChsHUDManager.h"
#include "ChsEngine.h"
#include "ChsModel.h"
#include "MainMenuScene.h"

using namespace Chaos;

//must do this, any other solutions??
static bool isDynamic = MainMenuScene::registerAsDynamic( "MainMenuScene" ); 

boost::scoped_ptr<ChsModelViewCamera> camera( new ChsModelViewCamera() );

MainMenuScene::MainMenuScene( void ){
  
}

MainMenuScene::~MainMenuScene( void ){
  
}

void MainMenuScene::onEnter( void ){
  
}

void MainMenuScene::onExit( void ){
  
}

void MainMenuScene::onUpdate( float dt ){
  
}

void MainMenuScene::onInit( void ){
  ChsEngine * engine = ChsEngine::sharedInstance();
  ChsRect viewport = engine->getRenderSystem()->getViewPort();
	camera->perspective( degree2Radian(39.6f), viewport.w/(float)viewport.h, 0.1f, 1000.0f  );
  camera->setScreen( viewport.w, viewport.h );
  ChsTouchEmitter::sharedInstance()->addListener( camera.get() );
  
  engine->getRenderSystem()->setCurrentCamera( camera.get() );
	engine->getRenderSystem()->toggleDebugCoordinate( true );
	
	ChsModel * model = ChsResourceManager::sharedInstance()->getModel( "test.chsmodel" ).get();
  ChsNode *root = this->getRoot();
	root->add( model );
  
  ChsHUDManager::sharedInstance()->loadHUD( "demo.chshud" );
  ChsHUDManager::sharedInstance()->showHUD( "demo.chshud" );
}

void MainMenuScene::onRelease( void ){
  
}
