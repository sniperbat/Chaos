#ifndef _CHS_OPENGL_H
#define _CHS_OPENGL_H

#include "ChsDefine.h"

#if defined(CHS_PLATFORM_IOS)

	#include <OpenGLES/ES2/gl.h>
	#include <OpenGLES/ES2/glext.h>

  #define glBindVertexArray       glBindVertexArrayOES
  #define glDeleteVertexArrays    glDeleteVertexArraysOES
  #define glGenVertexArrays       glGenVertexArraysOES


#elif defined(CHS_PLATFORM_ANDROID)

	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
	#include <EGL/egl.h>

	extern PFNGLBINDVERTEXARRAYOESPROC		glBindVertexArray;
	extern PFNGLDELETEVERTEXARRAYSOESPROC	glDeleteVertexArrays;
	extern PFNGLGENVERTEXARRAYSOESPROC		glGenVertexArrays;

#endif


#endif//_CHS_OPENGL_H
