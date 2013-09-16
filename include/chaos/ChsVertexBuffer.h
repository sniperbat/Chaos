#ifndef _CHS_VERTEXBUFFER_H
#define _CHS_VERTEXBUFFER_H
#include <string>
#include <vector>
#include "ChsArrayBuffer.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	struct ChsAttribUnit;

  //------------------------------------------------------------------------------------------------
	class ChsVertexBuffer final : public ChsArrayBuffer {
	public:
		ChsVertexBuffer( void );
		~ChsVertexBuffer( void );
		void addAttrib( int count, int type, bool isNormalized, const std::string & name );
    
		void bind( void );
		void unbind( void );

		inline void setDataWithVector( const std::vector<float> & vertices );

	private:
		void bindAttribArrays( void );
		void unbindAttribArrays( void );
		void attachAttributes( void );
    
		std::vector< std::shared_ptr<ChsAttribUnit> > attribs;
		unsigned int vaoHandle;
	};
  
	//------------------------------------------------------------------------------------------------
	inline void ChsVertexBuffer::setDataWithVector( const std::vector<float> & vertices ){
    ChsArrayBuffer::setDataWithArray( vertices.data(), vertices.size() * sizeof(float) );
	}
  
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHS_VERTEXBUFFER_H
