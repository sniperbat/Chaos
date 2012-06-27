#ifndef _CHS_SCENEMANAGER_H
#define _CHS_SCENEMANAGER_H
//--------------------------------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>
#include "core/ChsSingleton.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  class ChsScene;
  //------------------------------------------------------------------------------------------------
  class ChsSceneManager : public ChsSingleton<ChsSceneManager> {
  private:
    std::map< std::string, boost::shared_ptr<ChsScene> > scenes;
    boost::weak_ptr<ChsScene> currentScene;
  public:
    ChsSceneManager( void );
    ~ChsSceneManager( void );

    void update( float dt );
    void purge( void );
    
    inline boost::weak_ptr<ChsScene> getCurrentScene( void );
    
    boost::shared_ptr<ChsScene> getScene( const std::string & className );
    void gotoScene( const std::string & name );
  };

  //------------------------------------------------------------------------------------------------
  inline boost::weak_ptr<ChsScene> ChsSceneManager::getCurrentScene( void ){
    return this->currentScene;
  }
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SCENEMANAGER_H
