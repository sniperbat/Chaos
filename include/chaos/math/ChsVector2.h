#ifndef _CHS_VECTOR2_H
#define _CHS_VECTOR2_H
//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	class ChsVector2 final {
  private:
    void init( float x, float y );
	public:
		float x;
		float y;

		ChsVector2( void );
		ChsVector2( const ChsVector2 & vec2 );
		ChsVector2( float x, float y );
		~ChsVector2( void ){};

		//casting
	//	operator float* ();
	//	operator CONST float* () const;

		ChsVector2 & operator += ( const ChsVector2 & vec2 );
		ChsVector2 & operator -= ( const ChsVector2 & vec2 );
		ChsVector2 & operator *= ( float scale );
		ChsVector2 & operator /= ( float scale );

		ChsVector2 operator + ( const ChsVector2 & vec2 )const;
		ChsVector2 operator - ( const ChsVector2 & vec2 )const;
		ChsVector2 operator * ( float scale )const;
		ChsVector2 operator / ( float scale )const;

		ChsVector2 & operator = ( const ChsVector2 & vec2 );

		bool operator == ( const ChsVector2 & vec2 )const;
		bool operator != ( const ChsVector2 & vec2 )const;
	};

  //------------------------------------------------------------------------------------------------
	
}//namespace

//--------------------------------------------------------------------------------------------------
#endif		//_CHS_VECTOR2_H
