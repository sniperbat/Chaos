#include "ChsSprite2D.h"

namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  ChsSprite2D::ChsSprite2D( std::string name ) : ChsRenderNode( name ) {
    this->_x = 0;
    this->_y = 0;
    this->_width = 0;
    this->_height = 0;
    
    this->_depth = 1.0f;
    this->_xZoomRatio = 1.0f;
    this->_yZoomRatio = 1.0f;
    
    this->needUpdate = false;
  }

 	//------------------------------------------------------------------------------------------------ 
  ChsSprite2D::~ChsSprite2D( void ){
  }
  
  //------------------------------------------------------------------------------------------------ 
  
}