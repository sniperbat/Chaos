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
    //锚点，Sprite的中心点。默认左上角(0, 0)
    ChsPoint anchor;
    //Sprite中心点在父节点空间中的位置,默认(0, 0)
    ChsPoint position;
    //Sprite的大小。
    ChsSize size;
    //缩放比率，
    ChsSize zoom;
    //在Image内的位置，用于计算UV
    ChsRect imageBound;
    //图像的大小，
    ChsSize imageSize;
    ChsRect bound;
    float depth;
    
  public:
    ChsSprite2D( const std::string & name );
    ~ChsSprite2D( void );
    
    void update( void );
    
    void setImage( const boost::shared_ptr<ChsTextureEntity> & texture, float ox, float oy, float w, float h );
    //void setImage( std::string imageName, float ox, float oy, float w, float h );
    //void setImage( std::string imageName );

    void moveTo( float x, float y );
    void anchorAt( float x, float y );
    //改变Sprite缩放比率的时候，子节点跟随做相应的缩放
    void zoomAs( float w, float h );
    //改变Sprite的大小的时候，子节点Sprite保持不变
    void changeSizeTo( float w, float h );
    
    inline ChsPoint getAnchor( void )const;
    inline ChsPoint getPosition( void )const;
    inline ChsSize getSize( void )const;
    inline ChsSize getZoom( void )const;
    
    inline float getDepth( void )const;
    inline void setDepth( float depth );
    
    //图像的大小，不能修改。只读
    inline ChsSize getImageSize( void )const;
    //这个Sprite2D的Bound范围，没有Setter，由内部计算获得，
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
