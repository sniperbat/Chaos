﻿#include "ChsVector3.h"
#include <assert.h>

namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsVector3::ChsVector3( float x, float y, float z){
    this->init( x, y, z );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector3::ChsVector3( void ){
    this->init( 0.0f, 0.0f, 0.0f );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector3::ChsVector3( const float vec[3] ){
    this->init( vec[0], vec[1], vec[2] );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector3::ChsVector3( const ChsVector3 & vec ){
    this->init( vec.x, vec.y, vec.z );
	}
	
  //------------------------------------------------------------------------------------------------
  void ChsVector3::init( float x, float y, float z ){
    this->x = x;
    this->y = y;
    this->z = z;
  }

  //------------------------------------------------------------------------------------------------
	ChsVector3 & ChsVector3::operator = ( const ChsVector3 & vec ){
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		return *this;
	}
	
  //------------------------------------------------------------------------------------------------
	bool ChsVector3::operator == (const ChsVector3& vec)const{
		return this->x == vec.x && this->y == vec.y && this->z == vec.z;
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector3 ChsVector3::operator - ( void )const{
		return ChsVector3( -this->x, -this->y, -this->z );
	}

  //------------------------------------------------------------------------------------------------
	ChsVector3 ChsVector3::operator * ( float scale )const{
		return ChsVector3( this->x * scale, this->y * scale, this->z * scale );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector3 ChsVector3::operator / ( float scale )const{
		assert( scale != 0 );
		return ChsVector3( this->x / scale, this->y / scale, this->z / scale );
	}

  //------------------------------------------------------------------------------------------------
	ChsVector3 & ChsVector3::operator += ( const ChsVector3 & vec ){
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}

  //------------------------------------------------------------------------------------------------
	ChsVector3 & ChsVector3::operator -= ( const ChsVector3 & vec ){
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		return *this;
	}
	
  //------------------------------------------------------------------------------------------------
	ChsVector3 & ChsVector3::operator *= ( float scale ){
		this->x *= scale;
		this->y *= scale;
		this->z *= scale;
		return *this;
	}

  //------------------------------------------------------------------------------------------------
	ChsVector3& ChsVector3::operator /= ( float scale ){
		//除0出错！！
		assert( scale != 0 );
		float oneOverScale = 1.0f/scale;
		this->x *= oneOverScale;
		this->y *= oneOverScale;
		this->z *= oneOverScale;
		return *this;
	}

  //------------------------------------------------------------------------------------------------
	void ChsVector3::normalize( void ){
		float magSq = this->x * this->x + this->y * this->y + this->z * this->z;
		if( magSq > 0.0f ){
			float oneOverMag = 1 / sqrt( magSq );
			this->x *= oneOverMag;
			this->y *= oneOverMag;
			this->z *= oneOverMag;
		}
	}

  //------------------------------------------------------------------------------------------------
	float ChsVector3::operator * ( const ChsVector3 & vec )const{
		return this->x * vec.x + this->y * vec.y + this->z * vec.z;
	}

  //------------------------------------------------------------------------------------------------
	float ChsVector3::length( void )const{
		return sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );
	}

  //------------------------------------------------------------------------------------------------
	float ChsVector3::lengthSq( void )const{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

  //------------------------------------------------------------------------------------------------
	ChsVector3 ChsVector3::cross( const ChsVector3 & vec1, const ChsVector3 & vec2 ){
		return ChsVector3( vec1.y * vec2.z - vec2.y * vec1.z,
						  vec1.z * vec2.x - vec2.z * vec1.x,
						  vec1.x * vec2.y - vec2.x * vec1.y );
	}

  //------------------------------------------------------------------------------------------------
	float ChsVector3::distance( const ChsVector3 & vec1, const ChsVector3 & vec2 ){
		float dx = vec1.x - vec2.x;
		float dy = vec1.y - vec2.y;
		float dz = vec1.z - vec2.z;
		return sqrt( dx * dx + dy * dy + dz * dz );
	}

  //------------------------------------------------------------------------------------------------
	const ChsVector3 ChsVector3::zeroVector( 0.0f, 0.0f, 0.0f );

  //------------------------------------------------------------------------------------------------
  void ChsVector3::debugPrint( const char * name ){
    printf( "%s:[%f,%f,%f]\n", name, this->x, this->y, this->z );
  }
  
}//namespace
