#ifndef _CHS_RENDERSYSTEM_H
#define _CHS_RENDERSYSTEM_H
//--------------------------------------------------------------------------------------------------
#include <vector>
#include <vector>
#include "ChsDefine.h"
#include "platform/ChsOpenGL.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
	class ChsRenderNode;
	class ChsMaterial;
	class ChsIndexBuffer;
	class ChsVertexBuffer;
	class ChsCamera;
  class ChsRenderStates;
  class ChsMatrix;

  //------------------------------------------------------------------------------------------------
  struct ChsRenderUnit{
		ChsMaterial * material;
		ChsVertexBuffer * vertexBuffer;
		ChsIndexBuffer * indexBuffer;
    ChsMatrix * transform;
	};
  typedef std::vector<ChsRenderUnit> ChsRenderChain;

	//------------------------------------------------------------------------------------------------
	class ChsRenderSystem {
	protected:
		virtual void present( void ) = 0;
		
		virtual void initContext( void ) = 0;
		virtual void releaseContext( void ) = 0;
		virtual void attachContext( void ) = 0;
		virtual void initRenderBuffer( void ) = 0;
			
		// The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
	  GLuint framebuffer;
		GLuint renderbuffer;
		GLuint depthRenderbuffer;
		
		// The pixel dimensions of the CAEAGLLayer.
    GLint renderbufferWidth;
    GLint renderbufferHeight;
		
	private:
		//viewport
		ChsRect viewport;
    ChsRenderStates * renderStates;
		ChsCamera * currentCamera;
    
    bool isShowDebugCoordinate;
    
		void preRender( void );
	  void postRender( void );

    void updateCamera( void );
    
		void initAllBuffers( void );
		void initFrameBuffer( void );
		void initDepthBuffer( void );
		void initGL( void );
    void deleteAllBuffers( void );

    void renderByTag( ChsRenderTag tag );
    void renderOpacity( void );
    void renderTransparent( void );
    void renderHUD( void );
	public:
		ChsRenderSystem( void );
		virtual ~ChsRenderSystem( void );
		
		void init( void );
		void shutdown( void );
		void render( void );

		void setClearColor( float r, float g, float b, float a );
		void setClearColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a );
		void setClearColor( unsigned int rgba );
		
		void setViewPort( int x, int y, int w, int h );
		inline ChsRect getViewPort( void )const;
    
		inline void setCurrentCamera( ChsCamera * camera );
    inline ChsCamera * getCurrentCamera( void )const;
    
		void toggleDebugCoordinate( bool isShow );
    inline bool isDebugCoordinateShowing( void )const;
	};
	
	//------------------------------------------------------------------------------------------------
	inline ChsRect ChsRenderSystem::getViewPort( void )const{
		return this->viewport;
	}

  //------------------------------------------------------------------------------------------------
	inline void ChsRenderSystem::setCurrentCamera( Chaos::ChsCamera *camera ){
    this->currentCamera = camera;
  }
  
  //------------------------------------------------------------------------------------------------
  inline ChsCamera * ChsRenderSystem::getCurrentCamera( void )const{
    return this->currentCamera;
  }
  
  //------------------------------------------------------------------------------------------------
  inline bool ChsRenderSystem::isDebugCoordinateShowing( void )const{
    return this->isShowDebugCoordinate;
  }
  
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHS_RENDERSYSTEM_H
