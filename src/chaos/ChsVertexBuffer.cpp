#include "ChsVertexBuffer.h"
#include "shader/ChsShaderProgram.h"
#include "ChsUtility.h"
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;
//--------------------------------------------------------------------------------------------------
namespace Chaos {

  struct ChsAttribUnit{
		int size;
		int count;
		int type;
		bool isNormalized;
		int index;
		int stride;
		int offset;
		std::string  name;
		ChsAttribUnit( int count, int type, bool isNormalized, const std::string & name ){
			this->count = count;
			this->type = type;
			this->isNormalized = isNormalized;
			this->size = count * getGLDataTypeSize( type );
			this->name = name;
		}
		void bind( void ){
			glVertexAttribPointer( index, count, type, isNormalized, stride, (void *)offset );
			glEnableVertexAttribArray( index );
		}
		void unbind( void ){
			glDisableVertexAttribArray( index );
		}
	};
  
  //------------------------------------------------------------------------------------------------
	ChsVertexBuffer::ChsVertexBuffer( void ) :	vboHandle( 0 ) ,
												vaoHandle( 0 ),
												vertices( nullptr ),
												isNeedUpdate( false )
	{
   	glGenBuffers( 1, &this->vboHandle );
    glGenVertexArrays( 1, &this->vaoHandle);
	}

  //------------------------------------------------------------------------------------------------
	ChsVertexBuffer::~ChsVertexBuffer( void ){
  	if( this->vboHandle )
     	glDeleteBuffers( 1, &this->vboHandle );
    if( this->vaoHandle )
 	    glDeleteVertexArrays( 1, &this->vaoHandle);
		attribs.clear();
		safeDeleteArray( &this->vertices );
	}

  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bindAttribLocations( const ChsShaderProgram * program ) {
		BOOST_FOREACH( const boost::shared_ptr<ChsAttribUnit> & attrib, this->attribs ){
			glBindAttribLocation( program->getHandle(), attrib->index, attrib->name.c_str() );
    }
	}

  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::setData( const void * vertices, int size ) {
   	this->size = size;
		safeDeleteArray( &this->vertices );
		this->vertices = new char[size];
		memcpy( this->vertices, vertices, size );
		this->isNeedUpdate = true;
	}

  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::addAttrib( int count, int type, bool isNormalized, const std::string & name ) {
		boost::shared_ptr<ChsAttribUnit> attrib( new ChsAttribUnit( count, type, isNormalized, name ) );
   	int lastOne = this->attribs.size();
    attrib->index = lastOne;
    int stride = 0;
   	if( lastOne ) {
     	const boost::shared_ptr<ChsAttribUnit> & lastAttrib = this->attribs[lastOne-1];
      attrib->offset = lastAttrib->offset + lastAttrib->size;
 	    stride = lastAttrib->stride;
    }
   	else{
      attrib->offset = 0;
   	}
    this->attribs += attrib;
   	stride += attrib->size;
		BOOST_FOREACH( const boost::shared_ptr<ChsAttribUnit> & attrib, this->attribs ){
			attrib->stride = stride;
    }
	}

  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bindAttribArrays( void ){
   	glBindBuffer( GL_ARRAY_BUFFER, this->vboHandle );
		BOOST_FOREACH( const boost::shared_ptr<ChsAttribUnit> & attrib, this->attribs ){
			attrib->bind();
    }
	}

  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::unbindAttribArrays( void ){
    BOOST_FOREACH( const boost::shared_ptr<ChsAttribUnit> & attrib, this->attribs ){
			attrib->unbind();
    }
	}

	//------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bind( void ){
   	glBindVertexArray( this->vaoHandle );
    if( this->isNeedUpdate ){
      this->bindAttribArrays();
      glBindBuffer( GL_ARRAY_BUFFER, this->vboHandle );
      glBufferData( GL_ARRAY_BUFFER, this->size, this->vertices,  GL_STATIC_DRAW );
      this->isNeedUpdate = false;
    }
	}

	//------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::unbind( void ){
   	glBindVertexArray( 0 );
	}
	
  //------------------------------------------------------------------------------------------------
  
}//namespace
