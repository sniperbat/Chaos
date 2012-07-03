#include <math.h>
#include "camera/ChsModelViewCamera.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{

  //------------------------------------------------------------------------------------------------
	class ChsCameraArcBall {
	public:
    //----------------------------------------------------------------------------------------------
		ChsCameraArcBall( void ) : isDrag( false ), radius( 1.0f ){
      this->mtxArcOrien.identity();
      this->quatBeforeDrag.identity();
      this->quatForCurrentDrag.identity();
    }

    //----------------------------------------------------------------------------------------------
		void onRotateBegin( float x, float y ){
      // Only enter the drag state if the click falls
      // inside the click rectangle.
      if( x >= 0 && x < this->screenWidth && y >= 0 && y < this->screenHeight ){
        this->isDrag = true;
        this->quatBeforeDrag = this->quatForCurrentDrag;
        this->startPointOfRotate = this->screenToVector( x, y );
      }
    }
    
    //----------------------------------------------------------------------------------------------
		void onRotating( float x, float y ){
      if( this->isDrag ){ 
        ChsQuaternion rotateQuat = ChsQuaternion::createByRotationVectors( this->startPointOfRotate, this->screenToVector( x, y ) );
        this->quatForCurrentDrag = this->quatBeforeDrag * rotateQuat;
      }
    }
    
    //----------------------------------------------------------------------------------------------
		void onRotateEnd( void ){
      this->isDrag = false;
    }
    
		//----------------------------------------------------------------------------------------------
    void setScreen( float width, float height, float radius = 0.9f ){
      this->screenWidth = width;
      this->screenHeight = height;
      this->halfScreenWidth = width / 2;
      this->halfScreenHeight = height / 2;
      this->radius = radius;
      this->centerOfArcBall.x = this->halfScreenWidth;
      this->centerOfArcBall.y = this->halfScreenHeight;
    }
    
    //----------------------------------------------------------------------------------------------
		ChsVector3 screenToVector( float scrX, float scrY )const{
      // Scale to screen
      float x   = (scrX - this->halfScreenWidth )  / (this->radius * this->halfScreenWidth );
      float y   = -(scrY -this->halfScreenHeight ) / (this->radius * this->halfScreenHeight );
      float z   = 0.0f;
      float mag = x * x + y * y;
      
      if( mag > 1.0f ) {
        float scale = 1.0f/sqrtf(mag);
        x *= scale;
        y *= scale;
      }
      else{
        z = sqrtf( 1.0f - mag );
      }
      // Return vector
      return ChsVector3( x, y, z );
    }
    
    //----------------------------------------------------------------------------------------------
		ChsVector2 boundXY( float scrX, float scrY )const{
      // Scale to screen
      float x  = ( scrX - this->halfScreenWidth ) / ( this->radius * this->halfScreenWidth );
      float y  = -( scrY - this->halfScreenHeight ) / ( this->radius * this->halfScreenHeight );
      return ChsVector2( x, y );
    }
 		
    //----------------------------------------------------------------------------------------------
    inline ChsMatrix& getRotationMatrix( void ){
      return changeQuaternionToMatrix( this->mtxArcOrien , this->quatForCurrentDrag );
    }

    //----------------------------------------------------------------------------------------------
	protected:
		ChsMatrix mtxArcOrien;
		
		float radius;
		float radiusTranslation;
		float screenWidth;
		float screenHeight;
		float halfScreenWidth;
		float halfScreenHeight;
    
		bool isDrag;
    
		ChsVector2 centerOfArcBall;
		ChsQuaternion quatBeforeDrag;
		ChsQuaternion quatForCurrentDrag;
		ChsVector3 startPointOfRotate;
	};
  
  //------------------------------------------------------------------------------------------------
  static ChsCameraArcBall worldArcBall;
  
  //------------------------------------------------------------------------------------------------
	ChsModelViewCamera::ChsModelViewCamera() : maxRadius(5), minRadius(0.01f), radius(1.0f),
                                             isRotating( false ), zoomDelta(0)
	{
		this->mxtModelRotate.identity();
		this->mtxModelLastRotate.identity();
		this->mtxTranslationDelta.identity();
	}
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onTouchesBegan( const ChsTouch & touch ){
    worldArcBall.onRotateBegin( touch.location.x, touch.location.y );
    this->isNeedUpdate = true;
    this->isRotating = true;
  }

  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onTouchesMove( const ChsTouch & touch ){
    if( this->isRotating ){
      worldArcBall.onRotating( touch.location.x, touch.location.y );
      this->isNeedUpdate = true;
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onTouchesCancelled( const ChsTouch & touch ){
    worldArcBall.onRotateEnd();
    this->isNeedUpdate = true;
    this->isRotating = false;
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onTouchesEnded( const ChsTouch & touch ){
    worldArcBall.onRotateEnd();
    this->isNeedUpdate = true;
    this->isRotating = false;
  }
  
  static float oldScale;
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onPinch( const ChsPinchTouch & touch ){
   if( touch.state == CHS_TOUCH_STATE_CHANGED ){
      int scale = static_cast<int>( 500*(touch.scale - oldScale) );
      this->zoomDelta += scale;
    }
    oldScale = touch.scale;
    this->isNeedUpdate = true;
    this->isRotating = false;
  }
  
  static ChsVector2 startPointForTranslation;
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::onLongPress( const ChsLongPressTouch & touch ){
    ChsVector2 currentPointForTranslation = worldArcBall.boundXY( touch.location.x, touch.location.y );
    if( touch.state == CHS_TOUCH_STATE_CHANGED ){
      ChsVector2 transDelta = currentPointForTranslation - startPointForTranslation;
      transDelta *= this->radius * 32;
      this->modelCenter.x += transDelta.x;
      this->modelCenter.y -= transDelta.y;
    }
    startPointForTranslation = currentPointForTranslation;
    this->isRotating = false;
    this->isNeedUpdate = true;
  }
  
  static ChsVector3 worldAhead( 0.0f, 0.0f, 150.0f );
  static ChsVector3 worldUp( 0.0f, 1.0f, 0.0f );
  //------------------------------------------------------------------------------------------------
	void ChsModelViewCamera::update(){
		if( !this->isNeedUpdate ){
			return;
    }
		this->isNeedUpdate = false;

		// Change the radius from the camera to the model based on wheel scrolling
		if( this->zoomDelta ){
			this->radius -= this->zoomDelta * this->radius * 0.001f;
    }

		this->radius = this->maxRadius < this->radius ? this->maxRadius : this->radius;
		this->radius = this->minRadius > this->radius ? this->minRadius : this->radius;
		this->zoomDelta = 0;

		// Transform vectors based on camera's rotation matrix
    // Update the eye point based on a radius away from the lookAt position
		this->position = this->target - worldAhead * this->radius;
		
		// Update the view matrix
		this->mtxView.lookAt( this->position, this->target, worldUp );

		ChsMatrix mInvView = this->mtxView;
		mInvView.inverse();
		mInvView._m41 = mInvView._m42 = mInvView._m43 = 0.0f;
    
		ChsMatrix mModelLastRotInv = this->mtxModelLastRotate;
		mModelLastRotInv.inverse();

		ChsMatrix mModelRot = worldArcBall.getRotationMatrix();
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
    mTrans.translation( - this->modelCenter );
		this->mtxWorld = this->mxtModelRotate * mTrans;
    this->mtxWVP = this->mtxWorld * this->mtxView * this->mtxProjection;
	}
  
  //------------------------------------------------------------------------------------------------
  void ChsModelViewCamera::setScreen( float width, float height, float radius ){
    worldArcBall.setScreen( width, height, radius );
    this->isNeedUpdate = true;
  }

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
