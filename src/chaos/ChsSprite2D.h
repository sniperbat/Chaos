#ifndef _CHS_SPRITE2D_H
#define _CHS_SPRITE2D_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "ChsMacro.h"
#include "ChsRenderNode.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
  class ChsTexture2D;

 	//------------------------------------------------------------------------------------------------
  class ChsSprite2D : public ChsRenderNode {
  private:
    std::string name;
    boost::shared_ptr<ChsTexture2D> imageTexture;
    bool needUpdate;
  public:
    ChsSprite2D( std::string name );
    ~ChsSprite2D( void );
    
    void setImage( std::string imageName, float ox, float oy, float w, float h );
    void setImage( std::string imageName );
    
    inline void moveTo( float x, float y );
    inline void moveToX( float x );
    inline void moveToY( float y );
    
    inline void zoom( float xZoomRatio, float yZoomRatio );
    inline void zoomWithX( float xZoomRatio );
    inline void zoomWithY( float yZoomRatio );
    
    PROPERTY_READONLY( float, x );
    PROPERTY_READONLY( float, y );
    
    PROPERTY( float, depth );
    PROPERTY( float, width );
    PROPERTY( float, height );
    PROPERTY( float, xZoomRatio );
    PROPERTY( float, yZoomRatio );
    
  };
  
 	//------------------------------------------------------------------------------------------------
  SYNTHESIZE_GETTER( ChsSprite2D, float, x );
  SYNTHESIZE_GETTER( ChsSprite2D, float, y );
  
  SYNTHESIZE_GETTER( ChsSprite2D, float, depth );
  SYNTHESIZE_GETTER( ChsSprite2D, float, width );
  SYNTHESIZE_GETTER( ChsSprite2D, float, height );
  SYNTHESIZE_GETTER( ChsSprite2D, float, xZoomRatio );
  SYNTHESIZE_GETTER( ChsSprite2D, float, yZoomRatio );
  
	//------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::moveTo( float x, float y ){
    this->_x = x;
    this->_y = y;
    this->needUpdate = true;
  }
  
 	//------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::moveToX( float x ){
    this->_x = x;
    this->needUpdate = true;
  }
  
 	//------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::moveToY( float y ){
    this->_y = y;
    this->needUpdate = true;
  }
  
	//------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::zoom( float xZoomRatio, float yZoomRatio ){
    this->_xZoomRatio = xZoomRatio;
    this->_yZoomRatio = yZoomRatio;
    this->needUpdate = true;
  }
  
	//------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::zoomWithX( float xZoomRatio ){
    this->_xZoomRatio = xZoomRatio;
    this->needUpdate = true;
  }
  
  //------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::zoomWithY( float yZoomRatio ){
    this->_yZoomRatio = yZoomRatio;
    this->needUpdate = true;
  }
  
	//------------------------------------------------------------------------------------------------
}


#endif//_CHS_SPRITE2D_H
