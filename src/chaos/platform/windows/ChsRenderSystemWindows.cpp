#ifdef WIN32 
#include <WTypes.h> // Include this first on Win (bug #35683) 
#endif
#include "ChsRenderSystemWindows.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos {
  HWND ghwnd;
  HDC ghdc;
  HGLRC grc;
  void ChsRenderSystemWindowsSetHandle( HWND hWnd ){
    ghwnd = hWnd;
  }
	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemWindows::initRenderBuffer( void ){
		glGenRenderbuffers( 1, &(this->renderbuffer) );
		glBindRenderbuffer( GL_RENDERBUFFER, this->renderbuffer );
		glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, this->renderbufferWidth, this->renderbufferHeight );
		//glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &(this->renderbufferWidth) );
    //glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &(this->renderbufferHeight) );
    glBindRenderbuffer( GL_RENDERBUFFER, 0 );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemWindows::initContext( void ) {
    ghdc = GetDC( ghwnd );
    PIXELFORMATDESCRIPTOR pfd = { 
      sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
      1,                     // version number  
      PFD_DRAW_TO_WINDOW |   // support window  
      PFD_SUPPORT_OPENGL |   // support OpenGL  
      PFD_DOUBLEBUFFER,      // double buffered  
      PFD_TYPE_RGBA,         // RGBA type  
      32,                    // 32-bit color depth  
      0, 0, 0, 0, 0, 0,      // color bits ignored  
      0,                     // no alpha buffer  
      0,                     // shift bit ignored  
      0,                     // no accumulation buffer  
      0, 0, 0, 0,            // accum bits ignored  
      16,                    // 16-bit z-buffer  
      0,                     // 8-bit stencil  
      0,                     // no auxiliary buffer  
      PFD_MAIN_PLANE,        // main layer  
      0,                     // reserved  
      0, 0, 0                // layer masks ignored  
    }; 
    int  pixelFormat = ChoosePixelFormat( ghdc, &pfd );
    SetPixelFormat( ghdc, pixelFormat, &pfd );
    grc = wglCreateContext( ghdc );
    wglMakeCurrent( ghdc, grc );
    GLenum err = glewInit();
    RECT rect;
    ::GetClientRect( ghwnd, &rect );
    this->renderbufferWidth = rect.right - rect.left;
    this->renderbufferHeight = rect.bottom - rect.top;
	}

	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemWindows::releaseContext( void ) {
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( grc );
    ReleaseDC( ghwnd, ghdc );
	}

	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemWindows::present( void ){
		//glBindRenderbuffer( GL_RENDERBUFFER, this->renderbuffer );
    SwapBuffers( ghdc );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsRenderSystemWindows::attachContext( void ){
    wglMakeCurrent( ghdc, grc );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	}

  //------------------------------------------------------------------------------------------------
}//namespace
