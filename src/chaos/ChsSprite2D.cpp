#include "ChsSprite2D.h"
#include "ChsMaterial.h"
#include "ChsTexture2D.h"
#include "ChsResourceManager.h"
#include "ChsIndexBuffer.h"
#include "ChsVertexBuffer.h"

namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  ChsSprite2D::ChsSprite2D( std::string name ) : ChsMesh( name ){
    this->anchor.x = 0.0f;
    this->anchor.y = 0.0f;

    this->position.x = 0.0f;
    this->position.y = 0.0f;

    this->zoom.w = 1.0f;
    this->zoom.h = 1.0f;

    this->size.w = 0.0f;
    this->size.h = 0.0f;
 
    this->depth = 1.0f;
    
    this->needUpdate = false;

    this->getVertexBuffer()->addAttrib( 3, GL_FLOAT, false, "position" );
		this->getVertexBuffer()->addAttrib( 4, GL_FLOAT, true, "vertexColor" );
		this->getIndexBuffer()->setMode( GL_TRIANGLE_STRIP );
  }

 	//------------------------------------------------------------------------------------------------ 
  ChsSprite2D::~ChsSprite2D( void ){
  }
  
  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( std::string imageName, float x, float y, float w, float h ){
    boost::shared_ptr<ChsTexture2D> texture = ChsResourceManager::sharedInstance()->getTexture2D( imageName );
    if( !texture )
      return;
    
    this->imageSize.w = texture->getWidth();
    this->imageSize.h = texture->getHeight();
    
    this->imageBound.x = x;
    this->imageBound.y = y;
    this->imageBound.w = w;
    this->imageBound.h = h;
    
    this->size.w = w;
    this->size.h = h;
    
    this->material->addTexture( texture );
    this->needUpdate = true;
  }
  
  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( std::string imageName ){
    
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsSprite2D::render( ChsRenderSystem * render ){
    
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsSprite2D::moveTo( float x, float y ){
    this->position.x = x;
    this->position.y = y;
    this->needUpdate = true;
  }
  
	//------------------------------------------------------------------------------------------------
  void ChsSprite2D::zoomAs( float zw, float zh ){
    this->zoom.w = zw;
    this->zoom.h = zh;
    this->needUpdate = true;
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsSprite2D::anchorAt( float x, float y ){
    this->anchor.x = x;
    this->anchor.y = y;
    this->needUpdate = true;
  }
  
  //------------------------------------------------------------------------------------------------  
  void ChsSprite2D::changeSizeTo( float w, float h ){
    this->size.w = w;
    this->size.h = h;
    this->needUpdate = true;
  }

}
