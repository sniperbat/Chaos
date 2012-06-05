#include <stdio.h>
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
	bool ChsShader::load( const char * source )const{
   	if ( !source ) {
     	printf("Failed to load vertex shader" );
      return false;
   	}
    glShaderSource( this->shaderHandle, 1, &source, nullptr );
   	return this->compile();
	}

  //------------------------------------------------------------------------------------------------
	bool ChsShader::compile( void )const{
   	glCompileShader( this->shaderHandle );
    return this->getStatus() != 0;
	}

  //------------------------------------------------------------------------------------------------
	int ChsShader::getStatus( void )const{
	#if defined( DEBUG )
   	GLint logLength;
    glGetShaderiv( this->shaderHandle, GL_INFO_LOG_LENGTH, &logLength );
   	if ( logLength > 1 ) {
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
