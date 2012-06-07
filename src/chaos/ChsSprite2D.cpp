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
    this->anchor.x = 0.0f;
    this->anchor.y = 0.0f;
    this->position.x = 0.0f;
    this->position.y = 0.0f;
    this->zoom.w = 1.0f;
    this->zoom.h = 1.0f;
    this->size.w = 0.0f;
    this->size.h = 0.0f;
    this->depth = 1.0f;
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
  void ChsSprite2D::setImage( const boost::shared_ptr<ChsTextureEntity> & texture, float ox, float oy, float w, float h ){
    this->texture = texture;
    this->imageSize.w = static_cast<float>( texture->getWidth() );
    this->imageSize.h = static_cast<float>( texture->getHeight() );
    this->imageBound.x = ox;
    this->imageBound.y = oy;
    this->imageBound.w = w;
    this->imageBound.h = h;
    this->material->addTexture( texture );
		this->material->setProperty( "hasTexture", true );
    this->needUpdate = true;
  }
  /*
  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( std::string imageName, float x, float y, float w, float h ){
    boost::shared_ptr<ChsTexture2D> texture = ChsResourceManager::sharedInstance()->getTexture2D( imageName );
    if( texture )
      this->setImage( texture, x, y, w, h );
  }
  
  //------------------------------------------------------------------------------------------------ 
  void ChsSprite2D::setImage( std::string imageName ){
    boost::shared_ptr<ChsTexture2D> texture = ChsResourceManager::sharedInstance()->getTexture2D( imageName );
    if( texture )
      this->setImage( texture, 0, 0, texture->getWidth(), texture->getHandle() );
  }
  */
  //-----------------------------------------------------------------------------------------------
  void ChsSprite2D::update( void ){
    if( this->needUpdate ){
      const GLfloat vertices[] = {
        this->position.x, this->position.y, this->depth,
        1.0f, 1.0f, 1.0f, 1.0f,
        this->imageBound.x, this->imageBound.h,
        
        this->position.x, this->position.y + this->size.h, this->depth,
        1.0f, 1.0f, 1.0f, 1.0f,
        this->imageBound.x, this->imageBound.y,
        
        this->position.x + this->size.w,  this->position.y, this->depth,
        1.0f, 1.0f, 1.0f, 1.0f,
        this->imageBound.w, this->imageBound.h ,
        
        this->position.x + this->size.w,  this->position.y + this->size.h, this->depth,
        1.0f, 1.0f, 1.0f, 1.0f,
        this->imageBound.w, this->imageBound.y,
      };
   		this->vertexBuffer->setDataWithArray( vertices, sizeof( vertices ) );
      this->needUpdate = false;
    }
    ChsRenderUnit unit;
    unit.material = this->material.get();
    unit.vertexBuffer = this->vertexBuffer.get();
    unit.indexBuffer = this->indexBuffer.get();
    this->sendToRender( CHS_RENDER_TAG_HUD, unit );
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
