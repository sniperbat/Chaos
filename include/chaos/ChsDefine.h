#ifndef _CHSDEFINE_H
#define _CHSDEFINE_H
//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
#if defined( __APPLE__ )
	#include <TargetConditionals.h>
	#if defined ( TARGET_OS_IPHONE )
		#define CHS_PLATFORM_IOS
	#endif
#endif

	//------------------------------------------------------------------------------------------------
#if defined( ANDROID )
	#define CHS_PLATFORM_ANDROID
#endif

  //------------------------------------------------------------------------------------------------
#if defined(__WINDOWS__)
  #define CHS_PLATFORM_WINDOWS
#endif

	//------------------------------------------------------------------------------------------------
	
#if defined( boolean )
#undef boolean
#endif
#define boolean unsigned int

  //------------------------------------------------------------------------------------------------
  enum ChsShaderType{
    CHS_SHADER_UNKNOWN,
    CHS_SHADER_PROGRAM,
    CHS_SHADER_VERTEX,
    CHS_SHADER_FRAGMENT,
  };
  
  #define CHS_INVALID_SHADER_HANDLE 0
  #define CHS_SHADER_UNIFORM_UNLOCATED -1
  #define CHS_SHADER_ATTRIBUTE_UNLOCATED -1
	//------------------------------------------------------------------------------------------------
	enum ChsRenderType{
		CHS_RENDER_IOS,
		CHS_RENDER_ANDROID,
		CHS_RENDER_WINDOWS,
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
	enum ChsOrientation{
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
  template <typename T> union ChsRect{
    struct{
      T x;
      T y;
      T w;
      T h;
    };
    struct{
      T left;
      T top;
      T right;
      T bottom;
    };
	};
	
  const boolean CHS_RS_DISABLE = 0;
  const boolean CHS_RS_ENABLE = 1;
	//------------------------------------------------------------------------------------------------
	enum ChsRenderStateId{
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

    CHS_RS_BLEND_FUNC,
    
		CHS_RS_MAX,
	};

  //------------------------------------------------------------------------------------------------
  enum ChsBlendFactor{
    CHS_BF_ZERO,
    CHS_BF_FIX_ONE,
    CHS_BF_SRC_COLOR,
    CHS_BF_ONE_MINUS_SRC_COLOR,
    CHS_BF_SRC_ALPHA,
    CHS_BF_ONE_MINUS_SRC_ALPHA,
    CHS_BF_DST_ALPHA,
    CHS_BF_ONE_MINUS_DST_ALPHA,
    CHS_BF_DST_COLOR,
    CHS_BF_ONE_MINUS_DST_COLOR,
    CHS_BF_SRC_ALPHA_SATURATE,
  };
 
  union ChsRenderState{
    unsigned int value;
    struct {
      unsigned int v1;
      unsigned int v2;
    }value2;
    ChsRenderState(){};
    ChsRenderState( unsigned int value  ){
      this->value = value;
    };
    ChsRenderState( unsigned int value1, unsigned int value2 ){
      this->value2.v1 = value1;
      this->value2.v2 = value2;
    };
  };
  //------------------------------------------------------------------------------------------------
  enum ChsRenderTag{
    CHS_RENDER_TAG_OPACITY,
    CHS_RENDER_TAG_TRANSPARENT,
    CHS_RENDER_TAG_2D,
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

//--------------------------------------------------------------------------------------------------
#endif//_CHSDEFINE_H
