#import <QuartzCore/QuartzCore.h>
#include <vector>//use for ChsRenderSystem.h
#include "ChsRenderSystemIOS.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemIOSSetTargetGLLayer( CAEAGLLayer * layer );
	CAEAGLLayer * glLayer = nil;
	EAGLContext * glContext = nil;

	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemIOSSetTargetGLLayer( CAEAGLLayer * layer ){
		glLayer = layer;
	}

	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::initRenderBuffer( void ){
		glGenRenderbuffers( 1, &(this->renderbuffer) );
		glBindRenderbuffer( GL_RENDERBUFFER, this->renderbuffer );
		//connect with layer
		assert( glLayer );
		[glContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:glLayer];
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::initContext( void ) {
		EAGLContext * context = [[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES2];
		if( !context )
			NSLog( @"Failed to create ES context" );
		else if( ![EAGLContext setCurrentContext : context ] )
			NSLog( @"Failed to set ES context current" );
		glContext = context;
    CGRect rect = [glLayer bounds];
    this->renderbufferWidth = rect.size.width;
    this->renderbufferHeight = rect.size.height;
	}

	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::releaseContext( void ) {
		if( [EAGLContext currentContext] == glContext ){
			[EAGLContext setCurrentContext: nil];
    }
	}

	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::present( void ) {
		[glContext presentRenderbuffer:GL_RENDERBUFFER];
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemIOS::attachContext( void ){
		if( [EAGLContext currentContext] != glContext ){
			[EAGLContext setCurrentContext:glContext];
    }
	}

  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
