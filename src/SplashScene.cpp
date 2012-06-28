#include "chaos/framework/ChsSceneManager.h"
#include "SplashScene.h"

//--------------------------------------------------------------------------------------------------
//must do this, any other solutions??
static bool isDynamic = SplashScene::registerAsDynamic( "SplashScene" );

SplashScene::SplashScene( void ){
}

SplashScene::~SplashScene( void ){
}

void SplashScene::onInit( void ){
  //load splash image
}

void SplashScene::onEnter( void ){
  //start fade out
}

void SplashScene::onUpdate( float dt ){
  //process fade in and out
  Chaos::ChsSceneManager::sharedInstance()->gotoScene( "MainMenuScene" );
}

void SplashScene::onExit( void ){
  
}

void SplashScene::onRelease( void ){
  //release splash image
}

