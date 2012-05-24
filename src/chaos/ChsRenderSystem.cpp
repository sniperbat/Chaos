#include <map>
#include <vector>
#include <boost/foreach.hpp>

#include "ChsRenderSystem.h"
#include "ChsRenderStates.h"
#include "ChsRenderNode.h"
#include "ChsUtility.h"
#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "shader/ChsShaderUniformSet.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"
#include "camera/ChsCamera.h"
#include "math/ChsMath.h"
#include "geometry/ChsCoordinatePlane.h"
#include "ChsHUDManager.h"
#include "ChsSceneManager.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  ChsRenderChain renderChains[CHS_RENDER_TAG_MAX];
  
	static ChsShaderUniformSet globalUniformSet;
	static ChsMatrix wvp;
	static ChsMatrix wvit;
	static ChsMatrix mtxWorld;
  static ChsShaderProgram * currentShaderProgram;
	static ChsCoordinatePlane * debugCoordinatePlane;

  //------------------------------------------------------------------------------------------------
  void renderByTag( ChsRenderTag tag );
  void renderByTag( ChsRenderTag tag ){
    BOOST_FOREACH( const ChsRenderUnit & unit, renderChains[tag] ){
      currentShaderProgram = unit.material->apply( currentShaderProgram );
      globalUniformSet.apply( currentShaderProgram );
      unit.vertexBuffer->bind();
      unit.indexBuffer->draw();
      unit.vertexBuffer->unbind();
    }
  }
  //------------------------------------------------------------------------------------------------
	ChsRenderSystem::ChsRenderSystem( void ) :
												framebuffer( 0 ),
												renderbuffer( 0 ),
                        depthRenderbuffer( 0 ),
												renderbufferWidth( 0 ),
												renderbufferHeight( 0 ),
												currentCamera( nullptr ),
                        renderStates( nullptr )
	{
	}

  //------------------------------------------------------------------------------------------------
	ChsRenderSystem::~ChsRenderSystem( void ){
		safeDelete( &debugCoordinatePlane );
	}

  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::init( void ){
		this->initContext();
		this->initAllBuffers();
		this->initGL();
    ChsHUDManager::sharedInstance()->init( this->viewport );
    
		globalUniformSet.reset();
		globalUniformSet.add( "wvp", CHS_SHADER_UNIFORM_MAT4, 1, &wvp);
		globalUniformSet.add( "wvit", CHS_SHADER_UNIFORM_MAT4, 1, &wvit );
		
		//add debug coordinate plane
		debugCoordinatePlane = new ChsCoordinatePlane( 50, 50 );
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::initGL( void ){
		this->setClearColor( 0.3f, 0.3f, 0.7f, 1.0f );
		this->setViewPort( 0, 0, this->renderbufferWidth, this->renderbufferHeight );

		glHint( GL_GENERATE_MIPMAP_HINT, GL_NICEST );

    this->renderStates = ChsRenderStates::sharedInstance();
    this->renderStates->queryCurrentStates();
		
    //以下内容在渲染过程中可能会被更改，如何更改，
		//depth
    this->renderStates->set( CHS_RS_DEPTH_TEST, CHS_RS_ENABLE );
		glDepthFunc( GL_LESS );
		glClearDepthf( 1.0f );
		
		//cull
 		this->renderStates->set( CHS_RS_CULL_FACE, CHS_RS_ENABLE );
		glCullFace( GL_BACK );
		glFrontFace( GL_CCW );
		
		//blend
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
  
	//------------------------------------------------------------------------------------------------
	void ChsRenderSystem::shutdown( void ){
		this->deleteAllBuffers();
		this->releaseContext();
	}

  //------------------------------------------------------------------------------------------------
  void ChsRenderSystem::updateCamera( void ){
    if( this->currentCamera ){
			this->currentCamera->update();
			wvp = mtxWorld * this->currentCamera->getMatrix();
			wvit = mtxWorld * this->currentCamera->getViewMatrix();
			wvit.inverse();
			wvit.transpose();
		}
  }
	//------------------------------------------------------------------------------------------------
	void ChsRenderSystem::preRender( void ){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}
  
  //------------------------------------------------------------------------------------------------
  void ChsRenderSystem::renderOpacity( void ){
    //先从前往后渲染不透明物体
 		this->renderStates->set( CHS_RS_BLEND, CHS_RS_DISABLE );
    renderByTag( CHS_RENDER_TAG_OPACITY );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsRenderSystem::renderTransparent( void ){
    //再从后往前渲染透明物体
 		this->renderStates->set( CHS_RS_BLEND, CHS_RS_ENABLE );
    renderByTag( CHS_RENDER_TAG_TRANSPARENT );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsRenderSystem::renderHUD( void ){
    //render hud
    this->renderStates->save();
    glClear( GL_DEPTH_BUFFER_BIT );
//    this->renderStates->set( CHS_RS_DEPTH_TEST, CHS_RS_DISABLE );
		wvp = ChsHUDManager::sharedInstance()->getCamera()->getViewProjectionMatrix();
    renderByTag( CHS_RENDER_TAG_HUD );
    this->renderStates->restore();
  }

  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::render( void ){
    this->updateCamera();
    this->attachContext();
		this->preRender();
    this->renderOpacity();
    this->renderTransparent();
    this->renderHUD();
    this->postRender();
    this->present();
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsRenderSystem::postRender( void ) {
    for( int i=CHS_RENDER_TAG_OPACITY; i<CHS_RENDER_TAG_MAX;i++)
      renderChains[i].clear();
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::initAllBuffers( void ){
		this->deleteAllBuffers();
		this->initDepthBuffer();
		this->initRenderBuffer();
		this->initFrameBuffer();
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::initFrameBuffer( void ){
		glGenFramebuffers( 1, &(this->framebuffer) );
		glBindFramebuffer( GL_FRAMEBUFFER, this->framebuffer );
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->renderbuffer );
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthRenderbuffer );
    if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
      printf( "Failed to make complete framebuffer object %x\n", glCheckFramebufferStatus( GL_FRAMEBUFFER ) );
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::initDepthBuffer( void ){
		glGenRenderbuffers( 1, &(this->depthRenderbuffer) );
		glBindRenderbuffer(GL_RENDERBUFFER, this->depthRenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, this->renderbufferWidth, this->renderbufferHeight );
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::deleteAllBuffers( void ){
		if( this->framebuffer ){
      glDeleteFramebuffers( 1, &(this->framebuffer) );
      this->framebuffer = 0;
    }
		if( this->renderbuffer ){
      glDeleteRenderbuffers( 1, &(this->renderbuffer) );
      this->renderbuffer = 0;
    }
		if( this->depthRenderbuffer ){
      glDeleteRenderbuffers( 1, &(this->depthRenderbuffer) );
      this->depthRenderbuffer = 0;
    }
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor( float r, float g, float b, float a ){
		glClearColor( r, g, b, a );
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a ){
		this->setClearColor( r/255.f, g/255.f, b/255.f, a/255.f );
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::setClearColor( unsigned int rgba ){
		this->setClearColor( static_cast<unsigned char>( ( rgba & 0xff0000 ) >> 16 ),
                         static_cast<unsigned char>( ( rgba & 0xff00 ) >> 8 ),
                         static_cast<unsigned char>( ( rgba & 0xff ) ),
                         static_cast<unsigned char>( ( rgba & 0xff000000 ) >> 24 ) );
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::setViewPort( int x, int y, int w, int h ){
		this->viewport.x = static_cast<float>( x );
		this->viewport.y = static_cast<float>( y );
		this->viewport.w = static_cast<float>( w );
		this->viewport.h = static_cast<float>( h );
		glViewport( x, y, w, h );
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderSystem::showDebugCoordinate( bool isShow ){
		if( this->isShowDebugCoordinate != isShow ){
      ChsNode * sceneRoot = ChsSceneManager::sharedInstance()->getRoot();
			if( isShow )
				sceneRoot->add( debugCoordinatePlane->getName(), debugCoordinatePlane );
			else
				sceneRoot->remove( debugCoordinatePlane->getName() );
			this->isShowDebugCoordinate = isShow;
		}
	}
	
  //------------------------------------------------------------------------------------------------
  
}//namespace
