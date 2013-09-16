#include "ChsSprite2D.h"
#include "ChsMaterial.h"
#include "ChsTexture2D.h"
#include "ChsResourceManager.h"
#include "ChsIndexBuffer.h"
#include "ChsVertexBuffer.h"
#include "ChsRenderStates.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  ChsSprite2D::ChsSprite2D( const std::string & name ) : ChsMesh( name ){
    this->setRenderTag( CHS_RENDER_TAG_2D );
    this->anchor.x = 0.0f;
    this->anchor.y = 0.0f;
    this->position.x = 0.0f;
    this->position.y = 0.0f;
    this->zoom.w = 1.0f;
    this->zoom.h = 1.0f;
    this->size.w = 0.0f;
    this->size.h = 0.0f;
    this->depth = 1.0f;
    this->alpha = 1.0f;
    this->needUpdate = true;
    this->vertexBuffer->addAttrib( 3, GL_FLOAT, false, "position" );
		this->vertexBuffer->addAttrib( 4, GL_FLOAT, true, "vertexColor" );
    this->vertexBuffer->addAttrib( 2, GL_FLOAT, true, "texcoord0" );
    const GLubyte index[]={0,1,2,3};
    this->indexBuffer->setDataWithArray( index, 4, GL_UNSIGNED_BYTE );
		this->indexBuffer->setMode( GL_TRIANGLE_STRIP );

    ChsMaterial * material = new ChsMaterial();
    material->setShader( "HUD.vsh", "HUD.fsh" );
    material->addProperty( "hasVertexColor", CHS_SHADER_UNIFORM_1_INT, 1 );
    material->addProperty( "hasTexture", CHS_SHADER_UNIFORM_1_INT, 1 );
    this->setMaterial( material );
  }

 	//------------------------------------------------------------------------------------------------ 
  ChsSprite2D::~ChsSprite2D( void ){
  }

  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( const std::shared_ptr<ChsTextureEntity> & texture,
                             int left, int top, int right, int bottom ){
    float width = static_cast<float>( texture->getWidth() );
    float height = static_cast<float>( texture->getHeight() );
    this->setImage( texture, left/width, top/height, right/width, bottom/width );
  }
  
  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( const std::shared_ptr<ChsTextureEntity> & texture,
                             float left, float top, float right, float bottom  ){
    this->texture = texture;
    this->imageSize.w = static_cast<float>( texture->getWidth() );
    this->imageSize.h = static_cast<float>( texture->getHeight() );
    this->size = this->imageSize;
    this->material->addTexture( texture );
    this->material->setProperty( "hasTexture", true );
    this->needUpdate = true;

    this->imageBound.left = left;
    this->imageBound.top = top;
    this->imageBound.right =right;
    this->imageBound.bottom = bottom;
  }
  
  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( const std::shared_ptr<ChsTextureEntity> & texture ){
    this->setImage( texture, 0.0f, 0.0f, 1.0f, 1.0f );
  }

  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( const std::string & imageName,
                             int left, int top, int right, int bottom ){
    std::shared_ptr<ChsTextureEntity> texture = ChsResourceManager::sharedInstance()->getTextureEntity( imageName );
    if( texture ){
      this->setImage( texture );
      texture->setSampleName( "diffuseTexture" );
      texture->setActiveUnit( 0 );
      
      float width = static_cast<float>( texture->getWidth() );
      float height = static_cast<float>( texture->getHeight() );
      this->imageBound.left = left/width;
      this->imageBound.top = top/height;
      this->imageBound.right = right/width;
      this->imageBound.bottom = bottom/width;
    }
  }

  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( const std::string & imageName,
                             float left, float top, float right, float bottom ){
    std::shared_ptr<ChsTextureEntity> texture = ChsResourceManager::sharedInstance()->getTextureEntity( imageName );
    if( texture ){
      this->setImage( texture );
      texture->setSampleName( "diffuseTexture" );
      texture->setActiveUnit( 0 );
      
      this->imageBound.left = left;
      this->imageBound.top = top;
      this->imageBound.right =right;
      this->imageBound.bottom = bottom;
    }
  }
  
  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( const std::string & imageName ){
    this->setImage( imageName, 0.0f, 0.0f, 1.0f, 1.0f );
  }

  //-----------------------------------------------------------------------------------------------
  void ChsSprite2D::update( double timeInterval ){
    if( this->needUpdate ){
      const GLfloat vertices[] = {
        this->position.x, this->position.y, this->depth,
        1.0f, 1.0f, 1.0f, this->alpha,
        this->imageBound.left, this->imageBound.bottom,
        
        this->position.x, this->position.y + this->size.h, this->depth,
        1.0f, 1.0f, 1.0f, this->alpha,
        this->imageBound.left, this->imageBound.top,
        
        this->position.x + this->size.w,  this->position.y, this->depth,
        1.0f, 1.0f, 1.0f, this->alpha,
        this->imageBound.right, this->imageBound.bottom ,
        
        this->position.x + this->size.w,  this->position.y + this->size.h, this->depth,
        1.0f, 1.0f, 1.0f, this->alpha,
        this->imageBound.right, this->imageBound.top,
      };
   		this->vertexBuffer->setDataWithArray( vertices, sizeof( vertices ) );
      this->needUpdate = false;
    }
    ChsRenderUnit unit;
    unit.material = this->material.get();
    unit.vertexBuffer = this->vertexBuffer.get();
    unit.indexBuffer = this->indexBuffer.get();
    this->sendToRender( unit );
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
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
