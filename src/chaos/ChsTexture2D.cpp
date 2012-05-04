#include <boost/scoped_array.hpp>

#include "ChsTexture2D.h"
#include "ChsFileSystem.h"
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
	GLuint currentTextureHandle = -1;
	//------------------------------------------------------------------------------------------------
	void ChsTexture2D::bind( void )const{
		if( currentTextureHandle == this->textureHandle )
			return;
		glBindTexture( GL_TEXTURE_2D, this->textureHandle );
		glActiveTexture( this->activeUnit );
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

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Allocate and load image data into texture
		glTexImage2D( GL_TEXTURE_2D, 0, this->format, this->width, this->height, 0, this->format, this->type, data );
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	//------------------------------------------------------------------------------------------------
	
}
