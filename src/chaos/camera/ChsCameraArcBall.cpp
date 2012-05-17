#include "camera/ChsCameraArcBall.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos{

  //------------------------------------------------------------------------------------------------
  ChsCameraArcBall::ChsCameraArcBall() : isDrag( false ), radius( 1.0f ){
		this->mtxArcOrien.identity();
		this->quatBeforeBtnDown.identity();
		this->quatForCurrentDrag.identity();
	}

  //------------------------------------------------------------------------------------------------
  void ChsCameraArcBall::onRotateBegin( int x, int y ){
		// Only enter the drag state if the click falls
		// inside the click rectangle.
		if( x >= this->wndOffset.x &&
			x < this->wndOffset.x + this->wndWidth &&
			y >= this->wndOffset.y &&
			y < this->wndOffset.y + this->wndHeight ){
			this->isDrag = true;
			this->quatBeforeBtnDown = this->quatForCurrentDrag;
			this->startPtOfRotArc = this->screenToVector( x, y );
		}
	}

  //------------------------------------------------------------------------------------------------
  void ChsCameraArcBall::onRotate( int x, int y ){
		if( this->isDrag ){ 
			this->curPtOfRotArc = this->screenToVector( x, y );
			this->quatForCurrentDrag = this->quatBeforeBtnDown * ChsQuaternion::rotationVector( this->startPtOfRotArc, this->curPtOfRotArc );
		}
	}

  //------------------------------------------------------------------------------------------------
  void ChsCameraArcBall::onRotateEnd( void ){
		this->isDrag = false;
	}

  //------------------------------------------------------------------------------------------------
  void ChsCameraArcBall::setWindow( int width, int height, float radius ){
		this->wndWidth = width;
		this->wndHeight = height;
		this->radius = radius;
		this->centerOfArcBall = ChsVector2( this->wndWidth/2.0f, this->wndHeight/2.0f );
	}

  //------------------------------------------------------------------------------------------------
  ChsVector2 ChsCameraArcBall::boundXY( int scrX, int scrY )const{
		// Scale to screen
		float x  = ( scrX - this->wndOffset.x - this->wndWidth / 2.0f ) / ( this->radius * this->wndWidth / 2.0f );
		float y  = -( scrY - this->wndOffset.y - this->wndHeight / 2.0f ) / ( this->radius * this->wndHeight / 2.0f );
		return ChsVector2( x, y );
	}

  //------------------------------------------------------------------------------------------------
	ChsVector3 ChsCameraArcBall::screenToVector( int scrX, int scrY )const{
		// Scale to screen
		float x   = (scrX - this->wndOffset.x - this->wndWidth/2)  / (this->radius * this->wndWidth/2);
		float y   = -(scrY - this->wndOffset.y - this->wndHeight/2) / (this->radius * this->wndHeight/2);
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
  
  //------------------------------------------------------------------------------------------------
}
