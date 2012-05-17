
#include "camera/ChsModelViewCamera.h"
#include <float.h>
#include <math.h>

//--------------------------------------------------------------------------------------------------
namespace Chaos{
  
  //------------------------------------------------------------------------------------------------
	ChsModelViewCamera::ChsModelViewCamera() :
					maxRadius(5),
					minRadius(0.01f),
					radius(1.0f),
          isRotating( false ),
					mouseWheelDelta(0)
	{
		this->mxtModelRotate.identity();
		this->mtxModelLastRotate.identity();
		this->mtxTranslationDelta.identity();
    this->worldArcBall.setWindow( 1024, 768 );
	}
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onTouchesBegan( const ChsTouch & touch ){
    this->worldArcBall.onRotateBegin( touch.location.x, touch.location.y );
    this->isNeedUpdate = true;
    this->isRotating = true;
  }

  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onTouchesMove( const ChsTouch & touch ){
    if( this->isRotating ){
      float x = touch.location.x;
      float y = touch.location.y;
      this->worldArcBall.onRotate( x, y );
      this->isNeedUpdate = true;
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onTouchesCancelled( const ChsTouch & touch ){
    this->worldArcBall.onRotateEnd();
    this->isNeedUpdate = true;
    this->isRotating = false;
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onTouchesEnded( const ChsTouch & touch ){
    this->worldArcBall.onRotateEnd();
    this->isNeedUpdate = true;
    this->isRotating = false;
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onPinch( const ChsPinchTouch & touch ){
    static float oldScale = touch.scale;
    if( touch.state == CHS_TOUCH_STATE_CHANGED ){
      int scale;
      scale = 100*(touch.scale - oldScale);
      this->mouseWheelDelta += scale;
      this->isNeedUpdate = true;
      this->isRotating = false;
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onLongPress( const ChsLongPressTouch & touch ){
    float x = touch.location.x;
    float y = touch.location.y;
    if( touch.state == CHS_TOUCH_STATE_BEGAN ){
      this->downPt = this->worldArcBall.boundXY( x, y );      
    }
    else if( touch.state == CHS_TOUCH_STATE_CHANGED ){
      this->currentPt = this->worldArcBall.boundXY( x, y );
      ChsVector2 transDelta = ( this->currentPt - this->downPt ) * this->radius * 32;
      this->modelCenter.x += transDelta.x;
      this->modelCenter.y -= transDelta.y;
      this->downPt = this->currentPt;
    }
    this->isRotating = false;
    this->isNeedUpdate = true;
  }
//----------------------------------------------------------------------------------------------------------
	void ChsModelViewCamera::update(){
		//if no mouse event,then do not update
		if( !this->isNeedUpdate )
			return;
		this->isNeedUpdate = false;

		// Change the radius from the camera to the model based on wheel scrolling
		if( this->mouseWheelDelta )
			this->radius -= this->mouseWheelDelta * this->radius * 0.001f;

		this->radius = this->maxRadius < this->radius ? this->maxRadius : this->radius;
		this->radius = this->minRadius > this->radius ? this->minRadius : this->radius;
		this->mouseWheelDelta = 0;

		// Transform vectors based on camera's rotation matrix
		ChsVector3 worldUp( 0.0f, 1.0f, 0.0f );
		ChsVector3 worldAhead( 0.0f, 0.0f, 150.0f );

		// Update the eye point based on a radius away from the lookAt position
		this->position = this->target - worldAhead * this->radius;
		
		// Update the view matrix
		this->mtxView.lookAt( this->position, this->target, worldUp );

		ChsMatrix mInvView = this->mtxView;
		mInvView.inverse();
		mInvView._m41 = mInvView._m42 = mInvView._m43 = 0.0f;
    
		ChsMatrix mModelLastRotInv = this->mtxModelLastRotate;
		mModelLastRotInv.inverse();

		ChsMatrix mModelRot = this->worldArcBall.getRotationMatrix();
		ChsMatrix temp = this->mtxView * mModelLastRotInv * mModelRot * mInvView;
		this->mxtModelRotate *= temp;

		this->mtxModelLastRotate = mModelRot;

		// Since we're accumulating delta rotations, we need to orthonormalize 
		// the matrix to prevent eventual matrix skew
		ChsVector3 xBasis(this->mxtModelRotate._m11, this->mxtModelRotate._m12, this->mxtModelRotate._m13 );
		ChsVector3 yBasis(this->mxtModelRotate._m21, this->mxtModelRotate._m22, this->mxtModelRotate._m23 );
		ChsVector3 zBasis(this->mxtModelRotate._m31, this->mxtModelRotate._m32, this->mxtModelRotate._m33 );
		
		xBasis.normalize();
		yBasis = ChsVector3::cross(zBasis, xBasis);
		yBasis.normalize();
		zBasis = ChsVector3::cross(xBasis, yBasis);
		
		this->mxtModelRotate._m11 = xBasis.x;
		this->mxtModelRotate._m12 = xBasis.y;
		this->mxtModelRotate._m13 = xBasis.z;

		this->mxtModelRotate._m21 = yBasis.x;
		this->mxtModelRotate._m22 = yBasis.y;
		this->mxtModelRotate._m23 = yBasis.z;

		this->mxtModelRotate._m31 = zBasis.x;
		this->mxtModelRotate._m32 = zBasis.y;
		this->mxtModelRotate._m33 = zBasis.z;
    
		// Translate the rotation matrix to the same position as the lookAt position

    this->mxtModelRotate._m41 = this->target.x;
		this->mxtModelRotate._m42 = this->target.y;
		this->mxtModelRotate._m43 = this->target.z;
		// Translate world matrix so its at the center of the model
        
		ChsMatrix mTrans;
		mTrans.translation(-this->modelCenter.x, -this->modelCenter.y, -this->modelCenter.z);
		this->mtxWorld = this->mxtModelRotate * mTrans;
    
    this->mtxWVP = this->mtxWorld * this->mtxView * this->mtxProjection;
    
	}
  
  //------------------------------------------------------------------------------------------------
  
}
