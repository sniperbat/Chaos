#ifndef _CHS_SCENEMANAGER_H
#define _CHS_SCENEMANAGER_H
//--------------------------------------------------------------------------------------------------
#include <map>
#include "core/ChsSingleton.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  class ChsScene;
  //------------------------------------------------------------------------------------------------
  class ChsSceneManager final : public ChsSingleton<ChsSceneManager> {
  private:
    std::map< std::string, std::shared_ptr<ChsScene> > scenes;
    std::weak_ptr<ChsScene> currentScene;
    std::weak_ptr<ChsScene> lastScene;
  public:
    ChsSceneManager( void );
    ~ChsSceneManager( void );

    void update( double timeInterval );
    void purge( void );
    
    inline std::weak_ptr<ChsScene> & getCurrentScene( void );
    inline std::weak_ptr<ChsScene> & getLastScene( void );
    
    std::shared_ptr<ChsScene> getScene( const std::string & className );
    void gotoScene( const std::string & name, bool isReleaseLashScene = false );
  };

  //------------------------------------------------------------------------------------------------
  inline std::weak_ptr<ChsScene> & ChsSceneManager::getCurrentScene( void ){
    return this->currentScene;
  }

  //------------------------------------------------------------------------------------------------
  inline std::weak_ptr<ChsScene> & ChsSceneManager::getLastScene( void ){
    return this->lastScene;
  }
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SCENEMANAGER_H
