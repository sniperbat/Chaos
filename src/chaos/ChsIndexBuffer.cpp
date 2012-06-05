#include "ChsIndexBuffer.h"
#include "ChsUtility.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
	ChsIndexBuffer::ChsIndexBuffer( void ) : count( 0 ), type( 0 ), mode( 0 ){
	}

  //------------------------------------------------------------------------------------------------
	ChsIndexBuffer::~ChsIndexBuffer( void ){
	}

  //------------------------------------------------------------------------------------------------
  void ChsIndexBuffer::init( int count, int type ){
    this->type = type;
    this->count = count;
    int size = getGLDataTypeSize( this->type ) * this->count;
    ChsArrayBuffer::init( size );
  }
  //------------------------------------------------------------------------------------------------
	void ChsIndexBuffer::setDataWithArray( const void * triangles, int count, int type ){
    this->type = type;
  	this->count = count;
    ChsArrayBuffer::setDataWithArray( triangles, getGLDataTypeSize( type ) * count );
   	this->isNeedUpdate = true;
	}

	//------------------------------------------------------------------------------------------------
	void ChsIndexBuffer::draw( void ){
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->vboHandle );
		if( this->isNeedUpdate ){
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->size, this->buffer, GL_STATIC_DRAW ); 
			this->isNeedUpdate = false;
		}
    glDrawElements( this->mode, this->count, this->type, 0 );
	}

  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
