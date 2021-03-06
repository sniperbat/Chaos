﻿#ifndef _CHS_CAMERAE_H
#define _CHS_CAMERAE_H
//--------------------------------------------------------------------------------------------------
#include "math/ChsVector3.h"
#include "math/ChsMatrix.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsCamera {
	public:
		ChsCamera( void );
		virtual ~ChsCamera( void );

    //call by renderSystem automatically
		virtual	void update( void );
		
		void lookAt( const ChsVector3 & position , const ChsVector3 & target );
		void lookAt( float posX, float posY, float posZ, float targetX, float targetY, float targetZ );
		void perspective( float fovy , float aspect , float near , float far );
		void frustum( float left, float right, float bottom, float top, float znear, float zfar );
		void ortho( float left , float right , float bottom, float top, float near , float far );

		void moveTo( float x, float y, float z );
		void moveTo( const ChsVector3 & position );
		
		void targetTo( float x, float y, float z );
		void targetTo( const ChsVector3 & target );

		inline const ChsMatrix & getViewProjectionMatrix( void )const;
    inline const ChsMatrix & getWorldMatrix( void )const;
		inline const ChsMatrix & getViewMatrix( void )const;
		inline const ChsMatrix & getProjectionMatrix( void )const;
    inline const ChsMatrix & getMatrix( void )const;
    
	protected:
		bool isNeedUpdate;
		
    ChsMatrix mtxWorld;
		ChsMatrix mtxView;
		ChsMatrix mtxProjection;
		ChsMatrix mtxViewProj;
    ChsMatrix mtxWVP;
		
		ChsVector3 position;
		ChsVector3 target;
		ChsVector3 up;
		
		float prjFovy;
		float prjAspect;
		float prjNear;
		float prjFar;
		float prjLeft;
		float prjRight;
		float prjBottom;
		float prjTop;
	};

	//------------------------------------------------------------------------------------------------
	inline const ChsMatrix & ChsCamera::getViewProjectionMatrix( void )const{
		return this->mtxViewProj;
	}
  
  //--------------------------------------------------------------------------------------------------
	inline const ChsMatrix & ChsCamera::getViewMatrix( void )const{
		return this->mtxView;
	}
  
  //--------------------------------------------------------------------------------------------------
	inline const ChsMatrix & ChsCamera::getProjectionMatrix( void )const{
		return this->mtxProjection;
	}
  
  //--------------------------------------------------------------------------------------------------
  inline const ChsMatrix & ChsCamera::getWorldMatrix( void )const{
    return this->mtxWorld;
  }
  
  //--------------------------------------------------------------------------------------------------
  inline const ChsMatrix & ChsCamera::getMatrix( void )const{
    return this->mtxWVP;
  }
  
  //--------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif	//_CHS_CAMERA_H
