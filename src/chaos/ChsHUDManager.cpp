#include <boost/foreach.hpp>

#include "ChsHUDManager.h"
#include "ChsCamera.h"
#include "ChsRenderNode.h"
#include "shader/ChsShaderUniformSet.h"
#include "Math/ChsMatrix.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
  ChsHUDManager::ChsHUDManager( void ) : hudCamera( new ChsCamera() ),
                                         hudUniformSet( new ChsShaderUniformSet() )
  {
  }
  
  //------------------------------------------------------------------------------------------------
  ChsHUDManager::~ChsHUDManager( void ){
  }

  static ChsMatrix hudWVP;
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::init( const ChsRect & viewport ){
    this->hudCamera->ortho( viewport.x, viewport.w, viewport.h, viewport.y, 0.1f, 1000.0f);
    this->hudCamera->lookAt( 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );

    hudWVP = this->hudCamera->getViewProjectionMatrix();
    
    this->hudUniformSet->reset();
    this->hudUniformSet->add( "wvp", CHS_SHADER_UNIFORM_MAT4, 1, &hudWVP);
   
  }

  static ChsShaderProgram * hudShaderProgram;
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::render( void ){
    std::pair< std::string, ChsHUD * > p;
    BOOST_FOREACH( p, this->hudRenderList ){
      
      this->hudUniformSet->apply( hudShaderProgram );
      
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::showHUD( std::string hudName ){
    auto iter = this->hudRenderList.find( hudName );
    if( iter != this->hudRenderList.end() )
      return;//already on showing
    iter = this->hudList.find( hudName );
    if( iter == this->hudList.end() )
      return;//this hud does not exsit
    this->hudRenderList.insert( std::make_pair( hudName, iter->second ));
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::hideHUD( std::string hudName ){
    auto iter = this->hudRenderList.find( hudName );
    if( iter != this->hudRenderList.end() ){
      this->hudRenderList.erase( hudName );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  
}
