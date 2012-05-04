#include <boost/scoped_ptr.hpp>

#include "ChsShader.h"

namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsShader::ChsShader( int type ) : shaderHandle( 0 ){
		if( type ){
    	this->type = type;
	    this->shaderHandle = glCreateShader( type );
		}
	}

	//------------------------------------------------------------------------------------------------
	ChsShader::~ChsShader( void ){
		if( this->shaderHandle ){
	   	glDeleteShader( this->shaderHandle );
    	this->shaderHandle = 0;
		}
	}

  //------------------------------------------------------------------------------------------------
	bool ChsShader::load( const char * source ) {
   	if ( !source ) {
     	printf("Failed to load vertex shader" );
      return false;
   	}
    glShaderSource( this->shaderHandle, 1, &source, NULL );
   	return this->compile();
	}

  //------------------------------------------------------------------------------------------------
	bool ChsShader::compile( void ) {
   	glCompileShader( this->shaderHandle );
    return this->getStatus();
	}

  //------------------------------------------------------------------------------------------------
	int ChsShader::getStatus( void ) {
	#if defined( DEBUG )
   	GLint logLength;
    glGetShaderiv( this->shaderHandle, GL_INFO_LOG_LENGTH, &logLength );
   	if ( logLength > 0 ) {
      boost::scoped_ptr<GLchar> log( new GLchar[logLength] );
      glGetShaderInfoLog( this->shaderHandle, logLength, &logLength, log.get() );
    	printf( "Shader compile log:\n%s", log.get() );
	  }
	#endif
    GLint status;
	  glGetShaderiv( this->shaderHandle, GL_COMPILE_STATUS, &status );
    return status;
	}

  //------------------------------------------------------------------------------------------------
  
}//namespace
