#ifndef _CHS_CHAOS_H
#define _CHS_CHAOS_H
//--------------------------------------------------------------------------------------------------
#include "ChsEngine.h"
#include "io/ChsTouchEmitter.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------	
#ifdef __OBJC__
	//set layer before engine start
	void ChsRenderSystemIOSSetTargetGLLayer( CAEAGLLayer * layer );
#elif defined( CHS_PLATFORM_WINDOWS )
  void ChsRenderSystemWindowsSetHandle( HWND hwnd );
#endif
	
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif//_CHS_CHAOS_H
