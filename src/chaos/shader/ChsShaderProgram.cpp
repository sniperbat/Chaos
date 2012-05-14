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
	bool ChsShaderProgram::link( void )const{
    glLinkProgram( this->shaderHandle );
	  return this->getStatus() != 0;
	}

  //------------------------------------------------------------------------------------------------
	void ChsShaderProgram::use( void )const{
   	glUseProgram( this->shaderHandle );
	}

  //------------------------------------------------------------------------------------------------
	bool ChsShaderProgram::validate( void )const{
   	glValidateProgram( this->shaderHandle );
    return this->getStatus() != 0;
	}

  //------------------------------------------------------------------------------------------------
	int ChsShaderProgram::getStatus( void )const{
	#if defined(DEBUG)
   	GLint logLength;
    glGetProgramiv( this->shaderHandle, GL_INFO_LOG_LENGTH, &logLength );
   	if ( logLength > 1 ){
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
	void ChsShaderProgram::attachShader( const boost::shared_ptr<ChsShader> & shader )const{
   	glAttachShader( this->getHandle(), shader->getHandle() );
	}

  //------------------------------------------------------------------------------------------------
	int ChsShaderProgram::getUniformLocation( const char * name ){
		return glGetUniformLocation( this->shaderHandle, name );
	}

  //------------------------------------------------------------------------------------------------

}//namespace
