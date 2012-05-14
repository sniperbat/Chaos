#ifndef _CHS_VERTEXBUFFER_H
#define _CHS_VERTEXBUFFER_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	//------------------------------------------------------------------------------------------------
	class ChsShaderProgram;
	struct ChsAttribUnit;

  //------------------------------------------------------------------------------------------------
	class ChsVertexBuffer {
	public:
		ChsVertexBuffer( void );
		~ChsVertexBuffer( void );
		void bindAttribLocations( const ChsShaderProgram * program );
		void addAttrib( int count, int type, bool isNormalized, const std::string & name );
		void setData( const void * vertices, int size );
		inline void setData( const std::vector<float> & vertices );

		void bind( void );
		void unbind( void );
		
	private:
		void bindAttribArrays( void );
		void unbindAttribArrays( void );
    
		std::vector< boost::shared_ptr<ChsAttribUnit> > attribs;
		unsigned int vboHandle;
		unsigned int vaoHandle;
		char * vertices;
		int size;
		bool isNeedUpdate;
	};
  
	//------------------------------------------------------------------------------------------------
	inline void ChsVertexBuffer::setData( const std::vector<float> & vertices ){
		this->setData( vertices.data(), vertices.size() * sizeof(float) );
	}
  
  //------------------------------------------------------------------------------------------------
  
}//namespace

#endif //_CHS_VERTEXBUFFER_H
