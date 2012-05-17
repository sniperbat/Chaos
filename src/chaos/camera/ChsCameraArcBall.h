#ifndef		_CHS_CAMERAARCBALL_H
#define		_CHS_CAMERAARCBALL_H
#pragma once

#include "math/ChsMath.h"
#include "math/ChsVector2.h"
#include "math/ChsVector3.h"
#include "math/ChsMatrix.h"
#include "math/ChsQuaternion.h"
//----------------------------------------------------------------------------------------------------------
namespace Chaos {
//----------------------------------------------------------------------------------------------------------
	//sub class Orb
	class ChsCameraArcBall {
	public:
		ChsCameraArcBall( void );
		// Call these from client and use GetRotationMatrix() to read new rotation matrix
		 // start the rotation (pass current mouse position)
		void onRotateBegin( int x, int y );
		// continue the rotation (pass current mouse position)
		void onRotate( int x, int y );
		// end the rotation 
		void onRotateEnd( void );
		void setWindow( int width, int height, float radius = 0.9f );
		// Functions to get/set state
		inline ChsMatrix& getRotationMatrix( void );
		inline bool isBeingDragged( void )const;
		ChsVector3 screenToVector( int scrX, int scrY )const;
		ChsVector2 boundXY( int scrX, int scrY )const;
	protected:
		// ChsMatrix for arc ball's orientation
		ChsMatrix mtxArcOrien;
		// window offset, or upper-left corner of window
		ChsVector2 wndOffset;
		
		float radius;
		float radiusTranslation;
		int wndWidth;
		int wndHeight;

		bool isDrag;

		ChsVector2 centerOfArcBall;
		ChsQuaternion quatBeforeBtnDown;
		ChsQuaternion quatForCurrentDrag;

		ChsVector3 startPtOfRotArc;
		ChsVector3 curPtOfRotArc;
	};
//----------------------------------------------------------------------------------------------------------
	inline ChsMatrix & ChsCameraArcBall::getRotationMatrix( void ){
		return matrixRotationQuaternion( this->mtxArcOrien , this->quatForCurrentDrag );
	}
//----------------------------------------------------------------------------------------------------------
	inline bool ChsCameraArcBall::isBeingDragged()const{
		return this->isDrag;
	}
//----------------------------------------------------------------------------------------------------------
}
#endif	//_CHS_CAMERAARCBALL_H
