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
  void ChsSceneManager::update( double timeInterval ){
    if( !this->currentScene.expired() ){
      this->currentScene.lock()->updateTree( timeInterval );
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
      scene->setName( className );
      this->scenes.insert( std::make_pair( className, scene ) );
      scene->onInit();
    }
    return scene;
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsSceneManager::gotoScene( const std::string & name, bool isReleaseLastScene ){
    if( !this->lastScene.expired() ){
      if( this->lastScene.lock()->getName() == name ){
        //if has last scene and goto last scene, then just swap
        const boost::shared_ptr<ChsScene> & lastScene = this->lastScene.lock();
        this->lastScene = this->currentScene;
        this->currentScene = lastScene;
        return;
      }
    }
    
    boost::shared_ptr<ChsScene> targetScene = this->getScene( name );
    if( targetScene ){//if target scene cannot be found, ignore it
      if( !this->currentScene.expired() ){
        const boost::shared_ptr<ChsScene> & currentScene = this->currentScene.lock();
        if( currentScene.get() == targetScene.get() ){
          //target scene was already running, dont exit and enter again.
          return;
        }
        currentScene->onExit();
        this->lastScene = currentScene;
        if( isReleaseLastScene ){
          const std::string & lastSceneName = currentScene->getName();
          auto iter = this->scenes.find( lastSceneName );
          if( iter != this->scenes.end() )
            this->scenes.erase( iter );
          currentScene->onRelease();
        }
      }
      this->currentScene = targetScene;
      targetScene->onEnter();
    }
  }
  
  //------------------------------------------------------------------------------------------------

}

//--------------------------------------------------------------------------------------------------
