#include "core/ChsUtility.h"
#include "shader/ChsShaderProgram.h"
#include "shader/ChsShaderManager.h"
#include "ChsVertexBuffer.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
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
      this->index = CHS_SHADER_ATTRIBUTE_UNLOCATED;
		}
    
    void attachToShader( unsigned int programHandle ){
      if( this->index == CHS_SHADER_ATTRIBUTE_UNLOCATED )
        this->index = glGetAttribLocation( programHandle, this->name.c_str() );
      if( CHS_SHADER_ATTRIBUTE_UNLOCATED == this->index )
        printf( "can not found attribute:%s in program:%d\n", this->name.c_str(), programHandle );
    }
    
		void bind( void ){
      if( CHS_SHADER_ATTRIBUTE_UNLOCATED != this->index ){
        glVertexAttribPointer( index, count, type, isNormalized, stride, (void *)offset );
        glEnableVertexAttribArray( index );
      }
		}
    
		void unbind( void ){
      if( 0 <= this->index ){
        glDisableVertexAttribArray( index );
      }
		}
	};
  
  //------------------------------------------------------------------------------------------------
	ChsVertexBuffer::ChsVertexBuffer( void ) :	vaoHandle( 0 ){
    glGenVertexArrays( 1, &this->vaoHandle);
	}

  //------------------------------------------------------------------------------------------------
	ChsVertexBuffer::~ChsVertexBuffer( void ){
    if( this->vaoHandle ){
 	    glDeleteVertexArrays( 1, &this->vaoHandle);
    }
		attribs.clear();
	}
  
  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::addAttrib( int count, int type, bool isNormalized, const std::string & name ) {
		boost::shared_ptr<ChsAttribUnit> attrib( new ChsAttribUnit( count, type, isNormalized, name ) );
   	size_t lastOne = this->attribs.size();
    int stride = 0;
   	if( lastOne ) {
     	const auto & lastAttrib = this->attribs[lastOne-1];
      attrib->offset = lastAttrib->offset + lastAttrib->size;
 	    stride = lastAttrib->stride;
    }
   	else{
      attrib->offset = 0;
   	}
    this->attribs.push_back( attrib );
   	stride += attrib->size;
		for( const auto & attrib : this->attribs ){
			attrib->stride = stride;
    }
	}

  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bindAttribArrays( void ){
		for( const auto & attrib : this->attribs ){
			attrib->bind();
    }
	}

  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::unbindAttribArrays( void ){
    for( const auto & attrib : this->attribs ){
			attrib->unbind();
    }
	}

  //------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::attachAttributes( void ){
    unsigned int programHandle = ChsShaderManager::getActiveShaderProgram()->getHandle();
    for( const auto & attrib : this->attribs ){
      attrib->attachToShader( programHandle );
    }
	}

  
	//------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::bind( void ){
   	glBindVertexArray( this->vaoHandle );
    if( this->isNeedUpdate ){
      glBindBuffer( GL_ARRAY_BUFFER, this->vboHandle );
      glBufferData( GL_ARRAY_BUFFER, this->size, this->buffer,  GL_STATIC_DRAW );
      this->attachAttributes();
      this->bindAttribArrays();
      glBindBuffer( GL_ARRAY_BUFFER, 0 );
      this->isNeedUpdate = false;
    }
	}

	//------------------------------------------------------------------------------------------------
	void ChsVertexBuffer::unbind( void ){
//    this->unbindAttribArrays();
//    glBindBuffer( GL_ARRAY_BUFFER, 0 );
   	glBindVertexArray( 0 );
	}
	
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
