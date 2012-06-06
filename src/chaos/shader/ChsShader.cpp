#include <stdio.h>
#include <boost/scoped_ptr.hpp>
#include "platform/ChsOpenGL.h"
#include "ChsShader.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	ChsShader::ChsShader( void ) : shaderHandle( CHS_INVALID_SHADER_HANDLE ){
	}

	//------------------------------------------------------------------------------------------------
	ChsShader::~ChsShader( void ){
		if( this->shaderHandle ){
	   	glDeleteShader( this->shaderHandle );
    	this->shaderHandle = CHS_INVALID_SHADER_HANDLE;
		}
	}

  //------------------------------------------------------------------------------------------------
	bool ChsShader::load( const char * source )const{
   	if ( !source ) {
     	printf("Failed to load vertex shader" );
      return false;
   	}
    const char * sources[]={
      "#ifndef GL_ES\n"
      "#define lowp\n"
      "#define highp\n"
      "#define mediump\n"
      "#endif\n",
      source,
    };
    glShaderSource( this->shaderHandle, 2, sources, nullptr );
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
  ChsVertexShader::ChsVertexShader( void ){
    this->shaderHandle = glCreateShader( GL_VERTEX_SHADER );
    this->type = CHS_SHADER_VERTEX;
  }

  //------------------------------------------------------------------------------------------------
  ChsFragmentShader::ChsFragmentShader( void ){
    this->shaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
    this->type = CHS_SHADER_FRAGMENT;
  }

  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
