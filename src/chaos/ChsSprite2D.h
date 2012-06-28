#ifndef _CHS_SPRITE2D_H
#define _CHS_SPRITE2D_H
//--------------------------------------------------------------------------------------------------
#include "ChsDefine.h"
#include "ChsMesh.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
  class ChsMaterial;
  class ChsTextureEntity;
  class ChsRenderSystem;
  
 	//------------------------------------------------------------------------------------------------
  class ChsSprite2D : public ChsMesh {
  private:
    std::string name;
    bool needUpdate;
    boost::shared_ptr<ChsTextureEntity> texture;
  protected:
    //anchor default at left top (0,0)
    ChsPoint anchor;
    //the anchor point position at parent space,default at (0, 0)
    ChsPoint position;
    //size of sprite
    ChsSize size;
    //zoom rate
    ChsSize zoom;
    //for UV calculate, position and size in the image
    ChsRect imageBound;
    //size of image
    ChsSize imageSize;
    ChsRect bound;
    float depth;
    
  public:
    ChsSprite2D( const std::string & name );
    ~ChsSprite2D( void );
    
    void update( float dt );
    
    void setImage( const boost::shared_ptr<ChsTextureEntity> & texture, float ox, float oy, float w, float h );
    //void setImage( std::string imageName, float ox, float oy, float w, float h );
    //void setImage( std::string imageName );

    void moveTo( float x, float y );
    void anchorAt( float x, float y );
    //change size of sprite,and children node
    void zoomAs( float w, float h );
    //just change size of sprite, children node do not change size
    void changeSizeTo( float w, float h );
    
    inline ChsPoint getAnchor( void )const;
    inline ChsPoint getPosition( void )const;
    inline ChsSize getSize( void )const;
    inline ChsSize getZoom( void )const;
    
    inline float getDepth( void )const;
    inline void setDepth( float depth );
    
    //get size of image, read only
    inline ChsSize getImageSize( void )const;
    //get bound of sprite,has no setter
    ChsRect getBound( void )const;
  };
  
 	//------------------------------------------------------------------------------------------------
  inline float ChsSprite2D::getDepth( void )const{
    return this->depth;
  }
  
  //------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::setDepth( float depth ){
    this->depth = depth;
  }
  
  //------------------------------------------------------------------------------------------------
  inline ChsPoint ChsSprite2D::getAnchor( void )const{
    return this->anchor;
  }
  
  //------------------------------------------------------------------------------------------------
  inline ChsPoint ChsSprite2D::getPosition( void )const{
    return this->position;
  }
  
  //------------------------------------------------------------------------------------------------
  inline ChsSize ChsSprite2D::getSize( void )const{
    return this->size;
  }
  
  //------------------------------------------------------------------------------------------------
  inline ChsSize ChsSprite2D::getZoom( void )const{
    return this->zoom;
  }
  
  //------------------------------------------------------------------------------------------------
  inline ChsSize ChsSprite2D::getImageSize( void )const{
    return this->imageSize;
  }
  
	//------------------------------------------------------------------------------------------------
 
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SPRITE2D_H
