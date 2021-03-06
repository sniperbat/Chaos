﻿#ifndef		_CHS_MODELVIEWCAMERA_H
#define		_CHS_MODELVIEWCAMERA_H
//--------------------------------------------------------------------------------------------------
#include "math/ChsVector2.h"
#include "math/ChsVector3.h"
#include "math/ChsMatrix.h"
#include "math/ChsQuaternion.h"
#include "math/Chsmath.h"
#include "ChsCamera.h"
#include "io/ChsTouchListener.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{

  //------------------------------------------------------------------------------------------------
  class ChsCameraArcBall;
  
  //------------------------------------------------------------------------------------------------
	class ChsModelViewCamera : public ChsCamera , public ChsTouchListener{
	public:
		ChsModelViewCamera( void );

    void update( void ) override;
    void setScreen( float width, float height, float radius = 1.0f );

	private:
		int zoomDelta;
		ChsVector3 modelCenter;
		ChsMatrix mtxModelLastRotate;
		ChsMatrix mxtModelRotate;
		ChsMatrix mtxTranslationDelta;

		bool isNeedUpdate;
    bool isRotating;
		float radius;
		float maxRadius;
		float minRadius;

    //ChsTouchListener
    void onTouchesBegan( const ChsTouch & touch );
    void onTouchesMove( const ChsTouch & touch );
    void onTouchesCancelled( const ChsTouch & touch );
    void onTouchesEnded( const ChsTouch & touch );
    void onPinch( const ChsPinchTouch & touch );
    void onLongPress( const ChsLongPressTouch & touch );
	};

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_MODELVIEWCAMERA_H
