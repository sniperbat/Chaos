#ifndef _CHS_HUDMANAGER_H
#define _CHS_HUDMANAGER_H

#include <boost/scoped_ptr.hpp>
#include <map>
#include "ChsDefine.h"
#include "ChsSingleton.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  class ChsRenderNode;
  class ChsCamera;
  class ChsHUD;
  //------------------------------------------------------------------------------------------------
  class ChsHUDManager : public ChsSingleton<ChsHUDManager> {
  private:
    boost::scoped_ptr<ChsCamera> hudCamera;
    boost::scoped_ptr<ChsRenderNode> root;
    std::map< std::string, ChsHUD * > hudRenderList;
    std::map< std::string, ChsHUD * > hudList;
  public:
    ChsHUDManager( void );
    ~ChsHUDManager( void );
    void init( const ChsRect & viewport );
    void render( void );
    
    void showHUD( std::string hudName );
    void hideHUD( std::string hudName );
    
    void createHUD( std::string hudName );
    void loadHUDFromFile( std::string hudName, std::string hudFileName );
    
  };
  
  //------------------------------------------------------------------------------------------------
  
}


#endif//_CHS_HUDMANAGER_H

