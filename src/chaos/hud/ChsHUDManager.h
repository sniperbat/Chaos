#ifndef _CHS_HUDMANAGER_H
#define _CHS_HUDMANAGER_H

#include <boost/scoped_ptr.hpp>
#include <map>
#include "ChsDefine.h"
#include "ChsSingleton.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
  class ChsHUD;
  class ChsCamera;
  
  //------------------------------------------------------------------------------------------------
  class ChsHUDManager : public ChsSingleton<ChsHUDManager> {
  private:
    boost::scoped_ptr<ChsCamera> camera;
    std::map< std::string, ChsHUD * > hudRenderList;
    std::map< std::string, ChsHUD * > hudList;
  public:
    ChsHUDManager( void );
    ~ChsHUDManager( void );
    void init( const ChsRect & viewport );
    void update( void );
    void render( void );
    
    void showHUD( std::string hudName );
    void hideHUD( std::string hudName );

    void loadHUD( std::string hudName );
    void unloadHUD( std::string hudName );
    void purge( void );
    
    inline const ChsCamera * getCamera( void )const;
  };

  //------------------------------------------------------------------------------------------------
  inline const ChsCamera * ChsHUDManager::getCamera( void )const{
    return this->camera.get();
  }
  
}


#endif//_CHS_HUDMANAGER_H

