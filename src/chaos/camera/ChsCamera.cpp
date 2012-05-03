#include "ChsCamera.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsCamera::ChsCamera( void ) : up( 0.0f, 1.0f, 0.0f ) {
		this->mtxView.identity();
		this->mtxProjection.identity();
		this->isNeedUpdateViewMatrix = false;
	}

	//------------------------------------------------------------------------------------------------
	ChsCamera::~ChsCamera( void ){
	}

	//------------------------------------------------------------------------------------------------
	void ChsCamera::update( void ){
		if( this->isNeedUpdateViewMatrix ){
			this->isNeedUpdateViewMatrix = false;
			this->mtxView.lookAt( this->position , this->target , this->up );
		}
		this->mtxViewProj = this->mtxView * this->mtxProjection;
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsCamera::lookAt(const ChsVector3 & position , const ChsVector3 & target){
		this->moveTo( position );
		this->targetTo( target );
	}

	//------------------------------------------------------------------------------------------------
	void ChsCamera::lookAt( float posX, float posY, float posZ, float targetX, float targetY, float targetZ ){
		this->moveTo( posX, posY, posZ );
		this->targetTo( targetX, targetY, targetZ );
	}

	//------------------------------------------------------------------------------------------------
	void ChsCamera::perspective(float fovy, float aspect, float near, float far ){
		this->prjFovy = fovy;
		this->prjAspect = aspect;
		this->prjNear = near;
		this->prjFar = far;
		this->mtxProjection.perspective( fovy, aspect, near, far );
	}

	//------------------------------------------------------------------------------------------------
	void ChsCamera::frustum( float left, float right, float bottom, float top, float znear, float zfar ){
		this->prjLeft = left;
		this->prjRight = right;
		this->prjTop = top;
		this->prjBottom = bottom;
		this->prjFar = zfar;
		this->prjNear = znear;
		this->mtxProjection.frustum( left, right, bottom, top, znear, zfar );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsCamera::ortho( float left , float right , float bottom, float top, float near , float far ){
		this->prjLeft = left;
		this->prjRight = right;
		this->prjTop = top;
		this->prjBottom = bottom;
		this->prjFar = far;
		this->prjNear = near;
		this->mtxProjection.ortho( left, right, bottom, top, near, far );
	}

	//------------------------------------------------------------------------------------------------
	void ChsCamera::moveTo( float x, float y, float z ){
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
		this->isNeedUpdateViewMatrix = true;
	}

	//------------------------------------------------------------------------------------------------
	void ChsCamera::moveTo( const ChsVector3 & position ){
		this->position = position;
		this->isNeedUpdateViewMatrix = true;
	}

	//------------------------------------------------------------------------------------------------
	void ChsCamera::targetTo( float x, float y, float z ){
		this->target.x = x;
		this->target.y = y;
		this->target.z = z;
		this->isNeedUpdateViewMatrix = true;
	}

	//------------------------------------------------------------------------------------------------
	void ChsCamera::targetTo( const ChsVector3 & target ){
		this->target = target;
		this->isNeedUpdateViewMatrix = true;
	}
  
}
