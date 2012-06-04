#include "ChsOpenGL.h"

//--------------------------------------------------------------------------------------------------
//ogl extension

#if defined(CHS_PLATFORM_ANDROID)

PFNGLGENVERTEXARRAYSOESPROC  glGenVertexArrays;
PFNGLBINDVERTEXARRAYOESPROC  glBindVertexArray;
PFNGLDELETEVERTEXARRAYSOESPROC  glDeleteVertexArrays;

#endif

//--------------------------------------------------------------------------------------------------
