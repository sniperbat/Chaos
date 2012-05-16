#ifndef _CHSDEFINE_H
#define _CHSDEFINE_H
#pragma once

namespace Chaos {

  //------------------------------------------------------------------------------------------------
#if defined(__APPLE__)
	#include <TargetConditionals.h>
	#if defined (TARGET_OS_IPHONE)
		#define CHS_PLATFORM_IOS
	#endif
#endif

	//------------------------------------------------------------------------------------------------
#if defined(ANDROID)
	#define CHS_PLATFORM_ANDROID
#endif

	//------------------------------------------------------------------------------------------------
	
#if defined(boolean)
#undef boolean
#endif
#define boolean unsigned int

	//------------------------------------------------------------------------------------------------
	enum ChsRenderType{
		CHS_RENDER_IOS,
		CHS_RENDER_ANDROID,
		//		CHS_RENDER_D3D
	};
	
	//------------------------------------------------------------------------------------------------
	enum ChsShaderUniformDataType {
		CHS_SHADER_UNIFORM_1_FLOAT,
		CHS_SHADER_UNIFORM_1_INT,
		CHS_SHADER_UNIFORM_VEC2_FLOAT,
		CHS_SHADER_UNIFORM_VEC2_INT,
		CHS_SHADER_UNIFORM_VEC3_FLOAT,
		CHS_SHADER_UNIFORM_VEC3_INT,
		CHS_SHADER_UNIFORM_VEC4_FLOAT,
		CHS_SHADER_UNIFORM_VEC4_INT,
		CHS_SHADER_UNIFORM_MAT2,
		CHS_SHADER_UNIFORM_MAT3,
		CHS_SHADER_UNIFORM_MAT4,
	};
	
	//------------------------------------------------------------------------------------------------
	enum CHsOrientation{
		CHS_LANDSCAPE,
		CHS_PORTRAIT,
	};
	
  //------------------------------------------------------------------------------------------------
  struct ChsPoint{
    float x;
    float y;
  };
  
  //------------------------------------------------------------------------------------------------
  struct ChsSize{
    float w;
    float h;
  };
	//------------------------------------------------------------------------------------------------
	struct ChsRect{
		float x;
		float y;
		float w;
		float h;
	};
	
	//------------------------------------------------------------------------------------------------
	enum ChsRenderState{
		CHS_RS_DISABLE,
		CHS_RS_ENABLE,
		
		CHS_RS_TEXTURE_2D = 0,
		CHS_RS_CULL_FACE,
		CHS_RS_BLEND,
		CHS_RS_DITHER,
		CHS_RS_STENCIL_TEST,
		CHS_RS_DEPTH_TEST,
		CHS_RS_SCISSOR_TEST,
		CHS_RS_POLYGON_OFFSET_FILL,
		CHS_RS_SAMPLE_ALPHA_TO_COVERAGE,
		CHS_RS_SAMPLE_COVERAGE,
		CHS_RS_ENABLECAP = CHS_RS_SAMPLE_COVERAGE,
		
		CHS_RS_MAX,
	};

  //------------------------------------------------------------------------------------------------
  enum ChsRenderTag{
    CHS_RENDER_TAG_OPACITY,
    CHS_RENDER_TAG_TRANSPARENT,
    CHS_RENDER_TAG_HUD,
    CHS_RENDER_TAG_MAX,
  };

  //------------------------------------------------------------------------------------------------
  enum ChsTexWrapType{
    CHS_TEXTURE_WRAP_S,
    CHS_TEXTURE_WRAP_T,
    CHS_TEXTURE_WRAP_MAX,
  };
  
  //------------------------------------------------------------------------------------------------
  enum ChsTouchState{
    CHS_TOUCH_STATE_POSSIBLE,
    CHS_TOUCH_STATE_BEGAN,
    CHS_TOUCH_STATE_CHANGED,
    CHS_TOUCH_STATE_ENDED,
    CHS_TOUCH_STATE_CANCELLED,
    CHS_TOUCH_STATE_FAILED,
  };
  
  //------------------------------------------------------------------------------------------------
  enum ChsTouchType{
    CHS_TOUCH_TYPE_INVALID = -1,

    CHS_TOUCH_TYPE_BEGAN,
    CHS_TOUCH_TYPE_CHANGED,
    CHS_TOUCH_TYPE_ENDED,
    CHS_TOUCH_TYPE_CANCELLED,

    CHS_TOUCH_TYPE_TAP,
    CHS_TOUCH_TYPE_SWIPE,
    CHS_TOUCH_TYPE_PINCH,
    CHS_TOUCH_TYPE_LONGPRESS,
    
    CHS_TOUCH_TYPE_MAX,
  };
  
  //------------------------------------------------------------------------------------------------
  struct ChsTouch{
    int state;
    int numberOfTouches;
    ChsPoint location;
    ChsPoint previousLocation;
  };
  //------------------------------------------------------------------------------------------------
  struct ChsTapTouch : ChsTouch{
    int numberOfTaps;
  };
  
  //------------------------------------------------------------------------------------------------
  struct ChsSwipeTouch : ChsTouch{
    int direction;
  };

  //------------------------------------------------------------------------------------------------
  struct ChsPinchTouch : ChsTouch{
    float scale;
    float velocity;
  };
  
  //------------------------------------------------------------------------------------------------
  struct ChsLongPressTouch : ChsTouch{
  };
  
}//namespace

#endif//_CHSDEFINE_H
