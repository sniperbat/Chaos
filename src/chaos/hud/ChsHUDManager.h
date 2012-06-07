#ifndef _CHS_HUDMANAGER_H
#define _CHS_HUDMANAGER_H
//--------------------------------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <map>
#include <string>
#include <map>
#include <boost/scoped_ptr.hpp>
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

