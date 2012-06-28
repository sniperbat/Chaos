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
      this->currentScene.lock()->update( dt );
    }
  }
 
  //------------------------------------------------------------------------------------------------
  void ChsSceneManager::purge( void ){
    this->scenes.clear();
    //this currentScene is weak point, so dont worry about it
  }

  //------------------------------------------------------------------------------------------------
  static ChsClassFactory<ChsScene> * sceneClassFactory = 
    ChsClassFactory<ChsScene>::sharedInstance();
  //------------------------------------------------------------------------------------------------
  boost::shared_ptr<ChsScene> ChsSceneManager::getScene( const std::string & className ){
    auto iter = this->scenes.find( className );
    if( iter != this->scenes.end() ){
      return iter->second;
    }
    boost::shared_ptr<ChsScene> scene( sceneClassFactory->create( className ) );
    if( scene ){
      scene->onInit();
      this->scenes.insert( std::make_pair( className, scene ) );
    }
    return scene;
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsSceneManager::gotoScene( const std::string & name ){
    boost::shared_ptr<ChsScene> targetScene = this->getScene( name );
    if( targetScene ){//if target scene cannot be found, ignore it
      if( !this->currentScene.expired() ){
        const boost::shared_ptr<ChsScene> & lastScene = this->currentScene.lock();
        if( lastScene.get() == targetScene.get() ){
          //target scene was already running, dont exit and enter again.
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
