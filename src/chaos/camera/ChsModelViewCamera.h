#ifndef		__CHAOSMODELVIEWCAMERA_HPP
#define		__CHAOSMODELVIEWCAMERA_HPP
#pragma once
//----------------------------------------------------------------------------------------------------------
#include "ChsCamera.h"
#include "ChsCameraArcBall.h"
#include "ChsTouchListener.h"
//----------------------------------------------------------------------------------------------------------
namespace Chaos{
//----------------------------------------------------------------------------------------------------------
	enum MOUSE_BUTTON_MASK{
		MOUSE_NO_BUTTON = 0x00,
		MOUSE_LEFT_BUTTON = 0x01,
		MOUSE_MIDDLE_BUTTON = 0x02,
		MOUSE_RIGHT_BUTTON = 0x04,
		MOUSE_WHEEL = 0x08,
	};
//----------------------------------------------------------------------------------------------------------
	class ChsModelViewCamera : public ChsCamera , public ChsTouchListener{
	public:
		ChsModelViewCamera();
    void update();
    
    void onTouchesBegan( const ChsTouch & touch );
    void onTouchesMove( const ChsTouch & touch );
    void onTouchesCancelled( const ChsTouch & touch );
    void onTouchesEnded( const ChsTouch & touch );
    void onPinch( const ChsPinchTouch & touch );
    void onLongPress( const ChsLongPressTouch & touch );

	private:
		int mouseWheelDelta;
		ChsVector3 modelCenter;
		ChsCameraArcBall worldArcBall;
    
		ChsVector2 downPt;			// starting point of rotation arc
		ChsVector2 currentPt;		// current point of rotation arc

		ChsMatrix mtxModelLastRotate;
		ChsMatrix mxtModelRotate;	// Rotation matrix of model
		ChsMatrix mtxTranslationDelta; // ChsMatrix for arc ball's position

		bool isNeedUpdate;
    bool isRotating;
		float radius;
		float maxRadius;
		float minRadius;
	};
//----------------------------------------------------------------------------------------------------------
}
#endif		//__CHAOSMODELVIEWCAMERA_HPP
