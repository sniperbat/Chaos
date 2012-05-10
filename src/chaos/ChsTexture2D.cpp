#include <boost/scoped_array.hpp>

#include "ChsTexture2D.h"
#include "io/ChsFileSystem.h"
#include "ChsUtility.h"
#include "shader/ChsShaderProgram.h"

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
  static GLenum glTextureParams[] = {
    GL_TEXTURE_MAG_FILTER,
    GL_TEXTURE_MIN_FILTER,
    GL_TEXTURE_WRAP_S,
    GL_TEXTURE_WRAP_T,
  };

  //------------------------------------------------------------------------------------------------
  void ChsTexture2D::updateParameters( void ){
    for( int i = 0; i < CHS_TEXPARAM_MAX; i++ ){
      if( this->parameters[i].needUpdate ){
        this->parameters[i].needUpdate = false;
        glTexParameteri( GL_TEXTURE_2D, glTextureParams[i], this->parameters[i].value );
      }
    }
  }

	//------------------------------------------------------------------------------------------------
	static GLuint currentTextureHandle = 0;
	//------------------------------------------------------------------------------------------------
	void ChsTexture2D::bindToUnit( GLint unit ){
    this->updateParameters();
		if( currentTextureHandle == this->textureHandle )
			return;
		glBindTexture( GL_TEXTURE_2D, this->textureHandle );
		glActiveTexture( unit );
		currentTextureHandle = this->textureHandle;
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

    //获取并保存默认texture parameter
    for( int i = 0; i < CHS_TEXPARAM_MAX; i++ ){
      glGetTexParameteriv( GL_TEXTURE_2D, glTextureParams[i], &(this->parameters[i].value) );
      this->parameters[i].needUpdate = true;
    }

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Allocate and load image data into texture
		glTexImage2D( GL_TEXTURE_2D, 0, this->format, this->width, this->height, 0, this->format, this->type, data );
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	//------------------------------------------------------------------------------------------------
	
}
