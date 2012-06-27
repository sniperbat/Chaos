#include "ChsSceneManager.h"
#include "core/ChsClassFactory.h"
#include "ChsScene.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos{
 
  //------------------------------------------------------------------------------------------------
  ChsSceneManager::ChsSceneManager( void ){
  }
  
  //------------------------------------------------------------------------------------------------
  ChsSceneManager::~ChsSceneManager( void ){
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsSceneManager::update( float dt ){
    if( !this->currentScene.expired() ){
      boost::shared_ptr<ChsScene> & scene = this->currentScene.lock();
      scene->onUpdate( dt );
      ((ChsRenderNode*)scene->getRoot())->updateTree();
    }
  }
 
  //------------------------------------------------------------------------------------------------
  void ChsSceneManager::purge( void ){
  }

  //------------------------------------------------------------------------------------------------
  static ChsClassFactory<ChsScene> * sceneClassFactory = 
    ChsClassFactory<ChsScene>::sharedInstance();
  //------------------------------------------------------------------------------------------------
  boost::shared_ptr<ChsScene> ChsSceneManager::getScene( const std::string & className ){
    auto iter = this->scenes.find( className );
    if( iter == this->scenes.end() ){
      boost::shared_ptr<ChsScene> scene( sceneClassFactory->create( className ) );
      if( scene ){
        scene->onInit();
        this->scenes.insert( std::make_pair( className, scene ) );
      }
      return scene;
    }
    else{
      return iter->second;
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsSceneManager::gotoScene( const std::string & name ){
    boost::shared_ptr<ChsScene> targetScene = this->getScene( name );
    if( targetScene ){
      if( !this->currentScene.expired() ){
        boost::shared_ptr<ChsScene> lastScene = this->currentScene.lock();
        if( lastScene.get() == targetScene.get() ){
          return;
        }
        lastScene->onExit();
      }
      targetScene->onEnter();
      this->currentScene = targetScene;
    }
  }
  //------------------------------------------------------------------------------------------------
}

//--------------------------------------------------------------------------------------------------
