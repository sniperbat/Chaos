#ifndef _CHS_VERTEXBUFFER_H
#define _CHS_VERTEXBUFFER_H
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "ChsArrayBuffer.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsShaderProgram;
	struct ChsAttribUnit;

  //------------------------------------------------------------------------------------------------
	class ChsVertexBuffer : public ChsArrayBuffer {
	public:
		ChsVertexBuffer( void );
		~ChsVertexBuffer( void );
		void addAttrib( int index, int count, int type, bool isNormalized, const std::string & name );
		void bindAttribLocations( const ChsShaderProgram * program );

		void bind( void );
		void unbind( void );

		inline void setDataWithVector( const std::vector<float> & vertices );

	private:
		void bindAttribArrays( void );
		void unbindAttribArrays( void );
    
		std::vector< boost::shared_ptr<ChsAttribUnit> > attribs;
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
