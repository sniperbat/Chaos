#ifndef _CHS_RENDERSYSTEM_H
#define _CHS_RENDERSYSTEM_H
#pragma once

#include "ChsMacro.h"
#include "platform/ChsOpenGL.h"

namespace Chaos {

	class ChsRenderNode;
	class ChsMaterial;
	class ChsIndexBuffer;
	class ChsVertexBuffer;
	
	struct ChsRenderUnit{
		ChsMaterial * material;
		ChsVertexBuffer * vertexBuffer;
		ChsIndexBuffer * indexBuffer;
	};
	
	//----------------------------------------------------------------------------------------------
	class ChsRenderSystem {
	protected:
		virtual void present( void ) = 0;
		
		virtual void initContext( void ) = 0;
		virtual void releaseContext( void ) = 0;
		virtual void attachContext( void ) = 0;
	
		virtual void initFrameAndRenderBuffers( void );

		// The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
	    GLuint framebuffer;
		GLuint renderbuffer;
		// The pixel dimensions of the CAEAGLLayer.
    	GLint renderbufferWidth;
	    GLint renderbufferHeight;

	private:
		ChsMaterial * currentMaterial;
		
		void preRender( void );
		void render( void );
	    void postRender( void );
		void deleteFrameAndRenderBuffers( void );

	public:
		ChsRenderSystem();
		virtual ~ChsRenderSystem();
		void init( void );
		void shutdown( void );
		void update( void );
	
		void sendToRender(ChsRenderUnit unit);
		
		void setClearColor(float r,float g,float b,float a);
		void setClearColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
		void setClearColor(unsigned int rgba);
		
		PROPERTY_READONLY( ChsRenderNode *, root );
	};
	
	SYNTHESIZE_READONLY( ChsRenderSystem, ChsRenderNode *, root );
	//----------------------------------------------------------------------------------------------
}//namespace
#endif //_CHS_RENDERSYSTEM_H
