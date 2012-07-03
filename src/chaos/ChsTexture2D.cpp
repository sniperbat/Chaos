#include <boost/scoped_array.hpp>
#include "ChsTexture2D.h"
#include "io/ChsFileSystem.h"
#include "core/ChsUtility.h"
#include "shader/ChsShaderProgram.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsTexture2D::ChsTexture2D( void ) : type( GL_UNSIGNED_BYTE ),
										textureHandle( 0 ){
	}
	
	//------------------------------------------------------------------------------------------------
	ChsTexture2D::~ChsTexture2D( void ){
		if( this->textureHandle )
			glDeleteTextures( 1, &(this->textureHandle) );
	}
	
  //------------------------------------------------------------------------------------------------
  void ChsTexture2D::updateWrap( void ){
    if( this->wraps[CHS_TEXTURE_WRAP_S].needUpdate ){
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wraps[CHS_TEXTURE_WRAP_S].value );
      this->wraps[CHS_TEXTURE_WRAP_S].needUpdate = false;
    }
    if( this->wraps[CHS_TEXTURE_WRAP_T].needUpdate ){
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wraps[CHS_TEXTURE_WRAP_T].value );
      this->wraps[CHS_TEXTURE_WRAP_T].needUpdate = false;
    }
  }

	//------------------------------------------------------------------------------------------------
	static GLuint currentTextureHandle = 0;
  
	//------------------------------------------------------------------------------------------------
	void ChsTexture2D::bindToUnit( GLint unit ){
    this->updateWrap();
		if( currentTextureHandle != this->textureHandle ){
      glBindTexture( GL_TEXTURE_2D, this->textureHandle );
      glActiveTexture( unit );
      currentTextureHandle = this->textureHandle;
    }
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsTexture2D::build( GLuint width, GLuint height, GLenum format, GLubyte* data ){
		this->width = width;
		this->height = height;
		this->format = format;
		//this->_data = data;
		boost::scoped_array<GLubyte> dataPtr( data );
		glGenTextures( 1, &(this->textureHandle) );
		glBindTexture( GL_TEXTURE_2D, this->textureHandle );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &(this->wraps[CHS_TEXTURE_WRAP_S].value) );
    glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &(this->wraps[CHS_TEXTURE_WRAP_T].value) );
    this->wraps[CHS_TEXTURE_WRAP_S].needUpdate = false;
    this->wraps[CHS_TEXTURE_WRAP_T].needUpdate = false;

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Allocate and load image data into texture
		glTexImage2D( GL_TEXTURE_2D, 0, this->format, this->width, this->height, 0, this->format, this->type, data );
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	//------------------------------------------------------------------------------------------------
	
}

//--------------------------------------------------------------------------------------------------
