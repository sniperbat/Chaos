#include <string.h>
#include "ChsMatrix.h"
#include "ChsVector3.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsMatrix::ChsMatrix( void ){
		this->identity();
	}

	//------------------------------------------------------------------------------------------------
	ChsMatrix::ChsMatrix( const float m[16] ){
		memcpy( &(this->m),  m, sizeof( float ) * 16 );
	}
	
	//------------------------------------------------------------------------------------------------
	ChsMatrix::ChsMatrix( const ChsMatrix & matrix ){
		memcpy( &(this->m), &(matrix.m), sizeof( float ) * 16 );
	}
	
	//------------------------------------------------------------------------------------------------
	ChsMatrix & ChsMatrix::operator = ( const ChsMatrix & matrix ){
		memcpy( &(this->m), &(matrix.m), sizeof( float ) * 16 );
		return *this;
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::identity( void ){
		memset( &(this->m), 0, sizeof( float ) * 16 );
		this->_m11 = 1.0f;
		this->_m22 = 1.0f;
		this->_m33 = 1.0f;
		this->_m44 = 1.0f;
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::lookAt( const ChsVector3 & eye, const ChsVector3 & at, const ChsVector3 & up ){
		ChsVector3 zaxis = at - eye;
		zaxis.normalize();
		ChsVector3 xaxis = ChsVector3::cross( zaxis, up );
		xaxis.normalize();
		ChsVector3 yaxis = ChsVector3::cross( xaxis, zaxis );
		yaxis.normalize();
		
		this->m4x4[0][0] = xaxis.x;	this->m4x4[0][1] = yaxis.x;	this->m4x4[0][2] = -zaxis.x;	this->m4x4[0][3] = 0.0f;
		this->m4x4[1][0] = xaxis.y;	this->m4x4[1][1] = yaxis.y;	this->m4x4[1][2] = -zaxis.y;	this->m4x4[1][3] = 0.0f;
		this->m4x4[2][0] = xaxis.z;	this->m4x4[2][1] = yaxis.z;	this->m4x4[2][2] = -zaxis.z;	this->m4x4[2][3] = 0.0f;
		this->m4x4[3][0] = 0.0f;	this->m4x4[3][1] = 0.0f;	this->m4x4[3][2] = 0.0f;	this->m4x4[3][3] = 1.0f;
		
		this->translateTo( -eye.x, -eye.y, -eye.z );
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::ortho( float left, float right, float bottom, float top, float znear, float zfar ){
		float width, height, depth;
		width=right-left;
		height=top-bottom;
		depth=zfar-znear;
		this->m[0]=2.0f/width;		this->m[1]=0.0f;           this->m[2]=0.0f;           this->m[3]=0.0f;
		this->m[4]=0.0f;         this->m[5]=2.0f/height;		this->m[6]=0.0f;           this->m[7]=0.0f;
		this->m[8]=0.0f;         this->m[9]=0.0f;           this->m[10]=-2.0f/depth;		this->m[11]=0.0f;
		this->m[12]=(-right-left)/width;		this->m[13]=(-top-bottom)/height;		this->m[14]=(-zfar-znear)/depth;		this->m[15]=1.0f;
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::frustum( float left, float right, float bottom, float top, float znear, float zfar ){
		float temp, width, height, depth;
		temp=2.0f*znear;
		width=right-left;
		height=top-bottom;
		depth=zfar-znear;
		this->m[0]=temp/width;		this->m[1]=0.0f;           this->m[2]=0.0f;		this->m[3]=0.0f;
		this->m[4]=0.0f;           this->m[5]=temp/height;		this->m[6]=0.0f;		this->m[7]=0.0f;
		this->m[8]=(right+left)/width;		this->m[9]=(top+bottom)/width;      this->m[10]=(-zfar-znear)/depth;		this->m[11]=-1.0f;
		this->m[12]=0.0f;          this->m[13]=0.0f;          this->m[14]=(-temp*zfar)/depth;		this->m[15]=0.0f;
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::perspective( float fovy, float aspect, float znear, float zfar ){
		float ymax, xmax;
		ymax = znear*tanf( fovy/2 );
		xmax = ymax*aspect;
		this->frustum( -xmax, xmax, -ymax, ymax, znear, zfar );
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::inverse( void ){
		int is[4];
		int js[4];
		float fDet = 1.0f;
		float swapTemp;
		int f = 1;
		for( int k=0; k<4; ++k ){
			//step 1
			float fMax = 0.0f;
			for( int i = k; i < 4; ++i ){
				for( int j = k; j < 4; ++j ){
					const float f = fabs( this->m4x4[i][j] );
					if( f > fMax ){
						fMax = f;
						is[k] = i;
						js[k] = j;
					}
				}
			}
			float a = fabs( fMax );
			if( a < 0.0001f )
				return ;
			if( is[k] != k ){
				f = -f;
				swapTemp = this->m4x4[k][0];
				this->m4x4[k][0] = this->m4x4[is[k]][0];
				this->m4x4[is[k]][0] = swapTemp;

				swapTemp = this->m4x4[k][1];
				this->m4x4[k][1] = this->m4x4[is[k]][1];
				this->m4x4[is[k]][1] = swapTemp;

				swapTemp = this->m4x4[k][2];
				this->m4x4[k][2] = this->m4x4[is[k]][2];
				this->m4x4[is[k]][2] = swapTemp;

				swapTemp = this->m4x4[k][3];
				this->m4x4[k][3] = this->m4x4[is[k]][3];
				this->m4x4[is[k]][3] = swapTemp;

			}
			if( js[k] != k ){
				f = -f;

				swapTemp = this->m4x4[0][k];
				this->m4x4[0][k] = this->m4x4[0][js[k]];
				this->m4x4[0][js[k]] = swapTemp;

				swapTemp = this->m4x4[1][k];
				this->m4x4[1][k] = this->m4x4[1][js[k]];
				this->m4x4[1][js[k]] = swapTemp;

				swapTemp = this->m4x4[2][k];
				this->m4x4[2][k] = this->m4x4[2][js[k]];
				this->m4x4[2][js[k]] = swapTemp;

				swapTemp = this->m4x4[3][k];
				this->m4x4[3][k] = this->m4x4[3][js[k]];
				this->m4x4[3][js[k]] = swapTemp;
			}
			// calculate determinant
			fDet *= this->m4x4[k][k];
			// calculate Inverse matrix
			// step 2
			this->m4x4[k][k] = 1.0f / this->m4x4[k][k];
			// step 3
			for( int j = 0; j < 4; ++j ){
				if( j != k )
					this->m4x4[k][j] *= this->m4x4[k][k];
			}
			// step 4
			for( int i = 0; i < 4; ++i ){
				if( i != k ){
					for( int j = 0; j < 4; ++j ){
						if( j != k )
							this->m4x4[i][j] = this->m4x4[i][j] - this->m4x4[i][k] * this->m4x4[k][j];
					}
				}
			}
			// step 5
			for( int i = 0; i < 4; ++i ){
				if( i != k )
					this->m4x4[i][k] *= -this->m4x4[k][k];
			}
		}//for(int k=0; k<4; ++k)

		for( int k = 3; k >= 0; --k ){
			if( js[k] != k ){
				swapTemp = this->m4x4[k][0];
				this->m4x4[k][0] = this->m4x4[js[k]][0];
				this->m4x4[js[k]][0] = swapTemp;

				swapTemp = this->m4x4[k][1];
				this->m4x4[k][1] = this->m4x4[js[k]][1];
				this->m4x4[js[k]][1] = swapTemp;

				swapTemp = this->m4x4[k][2];
				this->m4x4[k][2] = this->m4x4[js[k]][2];
				this->m4x4[js[k]][2] = swapTemp;

				swapTemp = this->m4x4[k][3];
				this->m4x4[k][3] = this->m4x4[js[k]][3];
				this->m4x4[js[k]][3] = swapTemp;
			}
			if( is[k] != k ){
				swapTemp = this->m4x4[0][k];
				this->m4x4[0][k] = this->m4x4[0][is[k]];
				this->m4x4[0][is[k]] = swapTemp;

				swapTemp = this->m4x4[1][k];
				this->m4x4[1][k] = this->m4x4[1][is[k]];
				this->m4x4[1][is[k]] = swapTemp;

				swapTemp = this->m4x4[2][k];
				this->m4x4[2][k] = this->m4x4[2][is[k]];
				this->m4x4[2][is[k]] = swapTemp;

				swapTemp = this->m4x4[3][k];
				this->m4x4[3][k] = this->m4x4[3][is[k]];
				this->m4x4[3][is[k]] = swapTemp;
			}
		}//for	(k = 3; k >= 0; k --)
	}//void ChsMatrix::Inverse()

	//------------------------------------------------------------------------------------------------
	ChsVector3 * ChsMatrix::transformCoord( ChsVector3 * destinaion, const ChsVector3 * origin ){
		destinaion->x = origin->x * this->_m11 + origin->y * this->_m12 + origin->z * this->_m13 + this->_m14;
		destinaion->y = origin->x * this->_m21 + origin->y * this->_m22 + origin->z * this->_m23 + this->_m24;
		destinaion->z = origin->x * this->_m31 + origin->y * this->_m32 + origin->z * this->_m33 + this->_m34;
		return destinaion;
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::translateTo( float x, float y, float z ){
		this->_m41=this->m[0]*x+this->m[4]*y+this->m[8]*z+this->m[12];
		this->_m42=this->m[1]*x+this->m[5]*y+this->m[9]*z+this->m[13];
		this->_m43=this->m[2]*x+this->m[6]*y+this->m[10]*z+this->m[14];
		this->_m44=this->m[3]*x+this->m[7]*y+this->m[11]*z+this->m[15];
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::translation( float x, float y, float z ){
    this->identity();
		this->_m41=x;		this->_m42=y;		this->_m43=z;
	}

	//------------------------------------------------------------------------------------------------
	ChsMatrix * multiply( ChsMatrix * pOut, const ChsMatrix & matrix1, const ChsMatrix & matrix2 ){
		ChsMatrix temp;
		temp._m11 = matrix1._m11 * matrix2._m11 + matrix1._m12 * matrix2._m21 + matrix1._m13 * matrix2._m31 + matrix1._m14 * matrix2._m41;
		temp._m12 = matrix1._m11 * matrix2._m12 + matrix1._m12 * matrix2._m22 + matrix1._m13 * matrix2._m32 + matrix1._m14 * matrix2._m42;
		temp._m13 = matrix1._m11 * matrix2._m13 + matrix1._m12 * matrix2._m23 + matrix1._m13 * matrix2._m33 + matrix1._m14 * matrix2._m43;
		temp._m14 = matrix1._m11 * matrix2._m14 + matrix1._m12 * matrix2._m24 + matrix1._m13 * matrix2._m34 + matrix1._m14 * matrix2._m44;

		temp._m21 = matrix1._m21 * matrix2._m11 + matrix1._m22 * matrix2._m21 + matrix1._m23 * matrix2._m31 + matrix1._m24 * matrix2._m41;
		temp._m22 = matrix1._m21 * matrix2._m12 + matrix1._m22 * matrix2._m22 + matrix1._m23 * matrix2._m32 + matrix1._m24 * matrix2._m42;
		temp._m23 = matrix1._m21 * matrix2._m13 + matrix1._m22 * matrix2._m23 + matrix1._m23 * matrix2._m33 + matrix1._m24 * matrix2._m43;
		temp._m24 = matrix1._m21 * matrix2._m14 + matrix1._m22 * matrix2._m24 + matrix1._m23 * matrix2._m34 + matrix1._m24 * matrix2._m44;

		temp._m31 = matrix1._m31 * matrix2._m11 + matrix1._m32 * matrix2._m21 + matrix1._m33 * matrix2._m31 + matrix1._m34 * matrix2._m41;
		temp._m32 = matrix1._m31 * matrix2._m12 + matrix1._m32 * matrix2._m22 + matrix1._m33 * matrix2._m32 + matrix1._m34 * matrix2._m42;
		temp._m33 = matrix1._m31 * matrix2._m13 + matrix1._m32 * matrix2._m23 + matrix1._m33 * matrix2._m33 + matrix1._m34 * matrix2._m43;
		temp._m34 = matrix1._m31 * matrix2._m14 + matrix1._m32 * matrix2._m24 + matrix1._m33 * matrix2._m34 + matrix1._m34 * matrix2._m44;

		temp._m41 = matrix1._m41 * matrix2._m11 + matrix1._m42 * matrix2._m21 + matrix1._m43 * matrix2._m31 + matrix1._m44 * matrix2._m41;
		temp._m42 = matrix1._m41 * matrix2._m12 + matrix1._m42 * matrix2._m22 + matrix1._m43 * matrix2._m32 + matrix1._m44 * matrix2._m42;
		temp._m43 = matrix1._m41 * matrix2._m13 + matrix1._m42 * matrix2._m23 + matrix1._m43 * matrix2._m33 + matrix1._m44 * matrix2._m43;
		temp._m44 = matrix1._m41 * matrix2._m14 + matrix1._m42 * matrix2._m24 + matrix1._m43 * matrix2._m34 + matrix1._m44 * matrix2._m44;

		*pOut = temp;
		return pOut;
	}

	//------------------------------------------------------------------------------------------------
	ChsMatrix ChsMatrix::operator * ( const ChsMatrix & m ){
		ChsMatrix r;
		multiply( &r, * this, m );
		return r;
	}

	//------------------------------------------------------------------------------------------------
	ChsMatrix & operator *= ( ChsMatrix & a, ChsMatrix & b ){
		a = a * b;
		return a;
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::rotateX( float theta ){
		float s = sin( theta );
		float c = cos( theta );
		ChsMatrix rotateMatrix;
		rotateMatrix.identity();
		rotateMatrix._m11 = 1.0f;
		rotateMatrix._m22 = c;
		rotateMatrix._m23 = s;
		rotateMatrix._m32 = -s;
		multiply( this, *this, rotateMatrix );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMatrix::rotateXTo( float theta ){
		float s = sin( theta );
		float c = cos( theta );
		this->_m11 = 1.0f;
		this->_m22 = c;
		this->_m23 = s;
		this->_m32 = -s;
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMatrix::rotateY( float theta ){
		float s = sin( theta );
		float c = cos( theta );
		ChsMatrix rotateMatrix;
		rotateMatrix.identity();
		rotateMatrix._m11 = c;
		rotateMatrix._m22 = 1.0f;
		rotateMatrix._m13 = -s;
		rotateMatrix._m31 = s;
		rotateMatrix._m33 = c;
		multiply( this, *this, rotateMatrix );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMatrix::rotateYTo( float theta ){
		float s = sin( theta );
		float c = cos( theta );
		this->_m11 = c;		this->_m13 = -s;		this->_m22 = 1.0f;		this->_m31 = s;		this->_m33 = c;
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMatrix::rotateZ( float theta ){
		float s = sin( theta );
		float c = cos( theta );
		ChsMatrix rotateMatrix;
		rotateMatrix.identity();
		rotateMatrix._m11 = c;
		rotateMatrix._m12 = s;
		rotateMatrix._m21 = -s;
		rotateMatrix._m22 = c;
		rotateMatrix._m33 = 1.0f;
		multiply( this, *this, rotateMatrix );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMatrix::rotateZTo( float theta ){
		float s = sin( theta );
		float c = cos( theta );
		this->_m11 = c;		this->_m12 = s;		this->_m21 = -s;		this->_m22 = c;		this->_m33 = 1.0f;
	}

	//------------------------------------------------------------------------------------------------
	void ChsMatrix::transpose( void ){
		float swap;
		swap = this->_m12; this->_m12 = this->_m21; this->_m21 = swap;
		swap = this->_m13; this->_m13 = this->_m31; this->_m31 = swap;
		swap = this->_m14; this->_m14 = this->_m41; this->_m41 = swap;
		
		swap = this->_m23; this->_m23 = this->_m32; this->_m32 = swap;
		swap = this->_m24; this->_m24 = this->_m42; this->_m42 = swap;
		
		swap = this->_m34; this->_m34 = this->_m43; this->_m43 = swap;
	}

 //------------------------------------------------------------------------------------------------
  void ChsMatrix::debugPrint( const char * name ){
    printf("%s:\n[%f,%f,%f,%f\n %f,%f,%f,%f\n %f,%f,%f,%f\n %f,%f,%f,%f]\n",
           name,
           this->m[0],this->m[1],this->m[2],this->m[3],
           this->m[4],this->m[5],this->m[6],this->m[7],
           this->m[8],this->m[9],this->m[10],this->m[11],
           this->m[12],this->m[13],this->m[14],this->m[15] );
  }
  
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
