#ifndef _CHS_INDEXBUFFER_H
#define _CHS_INDEXBUFFER_H
#pragma once

#include "ChsArrayBuffer.h"
//--------------------------------------------------------------------------------------------------

namespace Chaos {

  //------------------------------------------------------------------------------------------------
	class ChsIndexBuffer : public ChsArrayBuffer {
	public:
		ChsIndexBuffer( void );
		~ChsIndexBuffer( void );
    
    void init( int count, int type );
    
		void setDataWithArray( const void * triangles, int count, int type );
		
    inline void setDataWithVector( std::vector<unsigned short> & triangles );
    inline void setDataWithVector( std::vector<unsigned int> & triangles );
    
		void draw( void );
    inline void setMode( int mode );
    inline int getType( void )const;
    inline int getCount( void )const;
	private:
		int count;
		int type;
		int mode;
	};
  
  //------------------------------------------------------------------------------------------------
  inline int ChsIndexBuffer::getType( void )const{
    return this->type;
  }
  
  //------------------------------------------------------------------------------------------------
	inline void ChsIndexBuffer::setMode( int mode ){
    this->mode = mode;
  }
  
	//------------------------------------------------------------------------------------------------
  inline int ChsIndexBuffer::getCount( void )const{
    return this->count;
  }
  //------------------------------------------------------------------------------------------------
	inline void ChsIndexBuffer::setDataWithVector( std::vector<unsigned short> & triangles ){
		this->setDataWithArray( triangles.data(), triangles.size(), GL_UNSIGNED_SHORT );
	}
  
	//------------------------------------------------------------------------------------------------
	inline void ChsIndexBuffer::setDataWithVector( std::vector<unsigned int> & triangles ){
		this->setDataWithArray( triangles.data(), triangles.size(), GL_UNSIGNED_INT );
	}
  //------------------------------------------------------------------------------------------------
  
}//namespaces

#endif//_CHS_INDEXBUFFER_H
