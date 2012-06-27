#include "GameDemo.h"
#include "ChsEntity.h"
#include "ChsRenderSystem.h"
#include "ChsMaterial.h"
#include "ChsTexture2D.h"
#include "ChsModel.h"
#include "chaos/framework/ChsSceneManager.h"

//--------------------------------------------------------------------------------------------------
using namespace Chaos;
GameDemo game;

//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
  ChsSceneManager::sharedInstance()->gotoScene( "MainMenuScene" );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}

//--------------------------------------------------------------------------------------------------
