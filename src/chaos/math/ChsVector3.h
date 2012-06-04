﻿#ifndef _CHS_VECTOR3_H
#define	_CHS_VECTOR3_H
//--------------------------------------------------------------------------------------------------
#include <math.h>
#include <boost/operators.hpp>

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	class ChsVector3 : boost::additive<ChsVector3>, boost::equality_comparable<ChsVector3> {
  private:
    void init( float x, float y, float z );
	public:
		union{
			float value[3];
			struct{ float x;  float y;  float z;  };
			struct{ float r;  float g;  float b;  };
		};
		
		ChsVector3( void );
		//这个构造函数是不安全的，不检查数组长度，尽量不要使用
		ChsVector3( const float vec[3] );
		ChsVector3( const ChsVector3& vec );
		ChsVector3( float, float, float );

		//重载赋值运算符，返回引用，实现左值
		ChsVector3 & operator = ( const ChsVector3 & vec );

		//由boost::equality_comparable实现【!=】操作
		bool operator == ( const ChsVector3 & vec )const;
		//由boost::additive实现【+，-】操作
		ChsVector3 & operator += ( const ChsVector3 & vec );
		ChsVector3 & operator -= ( const ChsVector3 & vec );
			
		//取负值
		ChsVector3 operator - ( void ) const;

		//标量乘除
		ChsVector3 operator * ( float scale )const;
		ChsVector3 & operator *= ( float scale );
		ChsVector3 operator / ( float scale )const;
		ChsVector3 & operator /= ( float scale );

		//向量点乘
		float operator * ( const ChsVector3 & vec )const;

		void normalize( void );
		float length( void )const;
		float lengthSq( void )const;
		inline void zero( void );

    void debugPrint( const char * name );
    
		//求模
		static inline float mag( const ChsVector3 & vec );
		//差乘
		static ChsVector3 cross( const ChsVector3 & vec1, const ChsVector3 & vec2 );
		static float distance( const ChsVector3 & vec1, const ChsVector3 & vec2 );
		static const ChsVector3 zeroVector;
	};

  //------------------------------------------------------------------------------------------------
	inline void ChsVector3::zero( void ){
		this->x = this->y = this->z = 0.0f;
	}

  //------------------------------------------------------------------------------------------------
	inline float ChsVector3::mag( const ChsVector3 & vec ){
		return sqrt( vec.x * vec.x + vec.y * vec.y + vec.z * vec.z );
	}

  //------------------------------------------------------------------------------------------------
	//标量左乘，非成员函数
	inline	ChsVector3 operator * ( float k, const ChsVector3 & vec ){
		return ChsVector3( k * vec.x, k * vec.y, k * vec.z );
	}

  //------------------------------------------------------------------------------------------------

}//namespace

//--------------------------------------------------------------------------------------------------
#endif		//_CHS_VECTOR3_H
