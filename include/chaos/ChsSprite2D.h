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
    ChsRect<float> imageBound;
    //size of image
    ChsSize imageSize;
    ChsRect<float> bound;
    float depth;
    float alpha;
  public:
    ChsSprite2D( const std::string & name );
    ~ChsSprite2D( void );
    
    void update( double timeInterval );
    
    //ox,oy,w,h is UVst
    void setImage( const boost::shared_ptr<ChsTextureEntity> & texture, float x, float y, float w, float h );
    //ox,oy,w,h is pixel
    void setImage( const boost::shared_ptr<ChsTextureEntity> & texture, int x, int y, int  w, int h );

    //in UVst
    void setImage( const std::string & imageName, float x, float y, float w, float h );
    //in pixel
    void setImage( const std::string & imageName, int x, int y, int w, int h );

    //set default uv to whole texture
    void setImage( const boost::shared_ptr<ChsTextureEntity> & texture );
    void setImage( const std::string & imageName );
    
    template <typename T> void setImage( const boost::shared_ptr<ChsTextureEntity> & texture, const ChsRect<T> & uvBound );
    template <typename T> void setImage( const std::string & imageName, const ChsRect<T> & uvBound );    
    
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
    
    inline float getAlpha( void )const;
    inline void setAlpha( float alpha );
    
    inline float getDepth( void )const;
    inline void setDepth( float depth );
    
    //get size of image, read only
    inline ChsSize getImageSize( void )const;
    //get bound of sprite,has no setter
    ChsRect<float> getBound( void )const;
  };
  
  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ChsSprite2D::setImage( const std::string & imageName, const ChsRect<T> & uvBound ){
    this->setImage( imageName, uvBound.left, uvBound.top, uvBound.right, uvBound.bottom );
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ChsSprite2D::setImage( const boost::shared_ptr<ChsTextureEntity> & texture,
                                    const ChsRect<T> & uvBound ){
    this->setImage( texture, uvBound.left, uvBound.top, uvBound.right, uvBound.bottom );
  }

 	//------------------------------------------------------------------------------------------------
  inline float ChsSprite2D::getAlpha( void )const{
    return this->alpha;
  }

 	//------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::setAlpha( float alpha ){
    this->alpha = alpha;
    this->needUpdate = true;
  }

 	//------------------------------------------------------------------------------------------------
  inline float ChsSprite2D::getDepth( void )const{
    return this->depth;
  }
  
  //------------------------------------------------------------------------------------------------
  inline void ChsSprite2D::setDepth( float depth ){
    this->depth = depth;
    this->needUpdate = true;
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
