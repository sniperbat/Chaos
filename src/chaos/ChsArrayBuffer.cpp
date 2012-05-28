#include "ChsArrayBuffer.h"
#include "ChsUtility.h"

namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  ChsArrayBuffer::ChsArrayBuffer( void ) : vboHandle( 0 ), buffer( nullptr ), size( 0 ), capacity( 0 ), isNeedUpdate( false ){
   	glGenBuffers( 1, &this->vboHandle );
  }
  
  //------------------------------------------------------------------------------------------------
  ChsArrayBuffer::~ChsArrayBuffer( void ){
    safeDeleteArray( &this->buffer );
    if( this->vboHandle )
     	glDeleteBuffers( 1, &this->vboHandle );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsArrayBuffer::init( int size ){
    if( size > this->capacity ){
      safeDeleteArray( &this->buffer );
      this->buffer = new char[size];
      this->capacity = size;
    }
    this->size = size;
  }
  
  //------------------------------------------------------------------------------------------------
	void ChsArrayBuffer::setDataWithArray( const void * buffer, int size ) {
    this->init( size );
		memcpy( this->buffer, buffer, size );
		this->isNeedUpdate = true;
	}
  
  //------------------------------------------------------------------------------------------------
  
}
