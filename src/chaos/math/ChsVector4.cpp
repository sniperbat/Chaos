#include "ChsVector4.h"
#include <math.h>
#include <assert.h>

namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	ChsVector4::ChsVector4( float x, float y, float z, float w ){
    this->init( x, y, z, w );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4::ChsVector4( void ){
    this->init( 0.0f, 0.0f, 0.0f, 0.0f );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4::ChsVector4( const float vec[4] ){
    this->init( vec[0], vec[1], vec[2], vec[3] );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4::ChsVector4( const ChsVector4 & vec ){
    this->init( vec.x, vec.y, vec.z, vec.w );
	}

  //------------------------------------------------------------------------------------------------
  void ChsVector4::init( float x, float y, float z, float w ){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
  //------------------------------------------------------------------------------------------------
	ChsVector4 & ChsVector4::operator += ( const ChsVector4 & vec ){
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		this->w += vec.w;
		return *this;
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4 & ChsVector4::operator -= ( const ChsVector4 & vec ){
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		this->w -= vec.w;
		return *this;
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4 & ChsVector4::operator *= ( const ChsVector4 & vec ){
		this->x *= vec.x;
		this->y *= vec.y;
		this->z *= vec.z;
		this->w *= vec.w;
		return *this;
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4 & ChsVector4::operator *= ( float scale ){
		this->x *= scale;
		this->y *= scale;
		this->z *= scale;
		this->w *= scale;
		return *this;
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4 & ChsVector4::operator /= ( float scale ){
		this->x /= scale;
		this->y /= scale;
		this->z /= scale;
		this->w /= scale;
		return *this;
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4 ChsVector4::operator * ( float scale )const{
		return ChsVector4( this->x * scale, this->y * scale, this->z * scale, this->w * scale );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4 ChsVector4::operator / ( float scale )const{
		assert( scale != 0 );
		return ChsVector4( this->x / scale, this->y / scale, this->z / scale, this->w / scale );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector4&	ChsVector4::operator = ( const ChsVector4 & vec ){
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		this->w = vec.w;
		return *this;
	}

  //------------------------------------------------------------------------------------------------
	float ChsVector4::length( void )const{
		return sqrtf( lengthSQ() );
	}
	
  //------------------------------------------------------------------------------------------------
	float ChsVector4::lengthSQ( void )const{
		return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
	}

  //------------------------------------------------------------------------------------------------

}//namespace
