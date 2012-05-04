#include <stdio.h>
#include <boost/scoped_ptr.hpp>

#include "ChsShaderProgram.h"
//--------------------------------------------------------------------------------------------------

namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsShaderProgram:: ChsShaderProgram( void ) : ChsShader( 0 ) {
    this->shaderHandle = glCreateProgram();
	}

  //------------------------------------------------------------------------------------------------
	ChsShaderProgram:: ~ChsShaderProgram( void ){
	  glDeleteProgram( this->shaderHandle );
    this->shaderHandle = 0;
	}

  //------------------------------------------------------------------------------------------------
	bool ChsShaderProgram::link( void ){
    glLinkProgram( this->shaderHandle );
	  return this->getStatus();
	}

  //------------------------------------------------------------------------------------------------
	void ChsShaderProgram::use( void ){
   	glUseProgram( this->shaderHandle );
	}

  //------------------------------------------------------------------------------------------------
	bool ChsShaderProgram::validate( void ){
   	glValidateProgram( this->shaderHandle );
    return this->getStatus();
	}

  //------------------------------------------------------------------------------------------------
	int ChsShaderProgram::getStatus( void ) {
	#if defined(DEBUG)
   	GLint logLength;
    glGetProgramiv( this->shaderHandle, GL_INFO_LOG_LENGTH, &logLength );
   	if ( logLength > 0 ){
      boost::scoped_ptr<GLchar> log( new GLchar[logLength] );
	    glGetProgramInfoLog( this->shaderHandle, logLength, &logLength, log.get() );
    	printf( "Program link log:\n%s", log.get() );
	  }
	#endif
    GLint status;
	  glGetProgramiv( this->shaderHandle, GL_LINK_STATUS, &status );
    return status;
	}

  //------------------------------------------------------------------------------------------------
	void ChsShaderProgram::attachShader( const boost::shared_ptr<ChsShader> & shader ) {
   	glAttachShader( this->getHandle(), shader->getHandle() );
	}

  //------------------------------------------------------------------------------------------------
	int ChsShaderProgram::getUniformLocation( const char * name ){
		return glGetUniformLocation( this->shaderHandle, name );
	}

  //------------------------------------------------------------------------------------------------

}//namespace
