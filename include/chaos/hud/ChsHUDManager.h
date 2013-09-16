#ifndef _CHS_HUDMANAGER_H
#define _CHS_HUDMANAGER_H
//--------------------------------------------------------------------------------------------------
#include <string>
#include <map>
#include "ChsDefine.h"
#include "core/ChsSingleton.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
  class ChsHUD;
  class ChsCamera;
  
  //------------------------------------------------------------------------------------------------
  class ChsHUDManager final : public ChsSingleton<ChsHUDManager> {
  private:
    std::unique_ptr<ChsCamera> camera;
    std::map< std::string, ChsHUD * > hudRenderList;
    std::map< std::string, ChsHUD * > hudList;
  public:
    ChsHUDManager( void );
    ~ChsHUDManager( void );
    void init( const ChsRect<int> & viewport );
    void update( float dt );
    void render( void );
    
    void showHUD( const std::string & hudName );
    void hideHUD( const std::string & hudName );

    void loadHUD( const std::string & hudName );
    void unloadHUD( const std::string & shudName );
    void purge( void );
    
    inline ChsCamera * getCamera( void )const;
  };

  //------------------------------------------------------------------------------------------------
  inline ChsCamera * ChsHUDManager::getCamera( void )const{
    return this->camera.get();
  }
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_HUDMANAGER_H

