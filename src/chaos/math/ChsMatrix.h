#ifndef	_CHS_MATRIX_H
#define	_CHS_MATRIX_H

#include "ChsVector3.h"

namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsMatrix {
	public:
		union{
			float m4x4[4][4];
			float m[16];
			struct{
				float _m11,_m12,_m13,_m14;
				float _m21,_m22,_m23,_m24;
				float _m31,_m32,_m33,_m34;
				float _m41,_m42,_m43,_m44;
			};
		};

		ChsMatrix( void );
		ChsMatrix( const float [16] );
		ChsMatrix( const ChsMatrix & m );

		// binary operators
		//ChsMatrix			operator * ( ChsMatrix & a,ChsMatrix &b);
		//ChsMatrix&		operator *= ( ChsMatrix& );
		ChsMatrix & operator = ( const ChsMatrix & matrix );
		inline float * getArrary( void );

		void lookAt( const ChsVector3 & eye, const ChsVector3 & at, const ChsVector3 & up );
		void ortho( float left, float right, float bottom, float top, float znear, float zfar );
		void perspective( float fovy, float aspect, float zn, float zf );
		void frustum( float left, float right, float bottom, float top, float znear, float zfar );

		void identity( void );
		void inverse( void );
		void transpose( void );
		ChsVector3 * transformCoord( ChsVector3 * destinaion, const ChsVector3 * origin );
		void translateTo( float x, float y, float z );
    void translation( float x, float y, float z );
		inline void translateTo( const ChsVector3 & vec );
    inline void translation( const ChsVector3 & vec );
    
    void debugPrint( const char * name );

		void rotateX( float theta );
		void rotateY( float theta );
		void rotateZ( float theta );

		void rotateXTo( float theta );
		void rotateYTo( float theta );
		void rotateZTo( float theta );
			
		ChsMatrix operator * ( const ChsMatrix & m );
	};

	//------------------------------------------------------------------------------------------------
	ChsMatrix * multiply( ChsMatrix * out, const ChsMatrix & matrix1, const ChsMatrix & matrix2 );
	ChsMatrix & operator *= ( ChsMatrix & a, ChsMatrix & b );
  
	//------------------------------------------------------------------------------------------------
	inline float * ChsMatrix::getArrary( void ){
		return this->m;
	};

  inline void ChsMatrix::translateTo( const ChsVector3 & vec ){
    this->translateTo( vec.x, vec.y, vec.z );
  }
  
  inline void ChsMatrix::translation( const ChsVector3 & vec ){
    this->translation( vec.x, vec.y, vec.z );
  }

	//------------------------------------------------------------------------------------------------

}//namespace

#endif //_CHS_MATRIX_H
