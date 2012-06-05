#ifndef _CHS_VECTOR4_H
#define _CHS_VECTOR4_H
//--------------------------------------------------------------------------------------------------
#include <boost/operators.hpp>

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsVector4 : boost::additive<ChsVector4>, boost::equality_comparable<ChsVector4> {
  private:
    void init( float x, float y, float z, float w );
	public:
		union{
			float value[4];
			struct{ float x;  float y;  float z;  float w;  };
			struct{ float r;  float g;  float b;  float a;  };
		};

		ChsVector4( void );
		//do not check the length of vec,not safe,be attention to use it.
		ChsVector4( const float vec[4] );
		ChsVector4( const ChsVector4& vec );
		ChsVector4( float x, float y, float z, float w );

		//!= be implemented by boost::equality_comparable
		bool operator == ( const ChsVector4 & vec )const;
		//+,- be implemented by boost::additive
		ChsVector4 & operator += ( const ChsVector4& vec );
		ChsVector4 & operator -= ( const ChsVector4& vec );

		ChsVector4 & operator *= ( const ChsVector4& vec );

		ChsVector4 & operator *= ( float scale );
		ChsVector4 & operator /= ( float scale );
		ChsVector4 operator * ( float scale )const;
		ChsVector4 operator / ( float scale )const;

		ChsVector4& operator = ( const ChsVector4& vec );

		//void				Add(ChsVector4 &vec);
		//void				Sub(ChsVector4 &vec);
		//static float		Dot(const ChsVector4 &vec1,const ChsVector4 &vec2);
		//static ChsVector4			Cross(const ChsVector4 &vec1,const ChsVector4 &vec2);
		//void				Normalize();
		//void				Scale(float s);
		//void				Zero();
		float length( void )const;
		float lengthSQ( void )const ;

		//void				Transform(ChsMatrix &mtx);
	};

	//------------------------------------------------------------------------------------------------
	typedef ChsVector4 ChsColor4;

}//namespace

//--------------------------------------------------------------------------------------------------
#endif		//_CHS_VECTOR4_H
