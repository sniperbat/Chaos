#include "platform/ChsOpenGL.h"
#include "ChsShaderProgram.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsShaderProgram:: ChsShaderProgram( void ){
    this->shaderHandle = glCreateProgram();
    this->type = CHS_SHADER_PROGRAM;
	}

  //------------------------------------------------------------------------------------------------
	ChsShaderProgram:: ~ChsShaderProgram( void ){
    if( this->shaderHandle ){
      glDeleteProgram( this->shaderHandle );
      this->shaderHandle = CHS_INVALID_SHADER_HANDLE;
    }
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
      std::unique_ptr<GLchar[]> log( new GLchar[logLength] );
	    glGetProgramInfoLog( this->shaderHandle, logLength, &logLength, log.get() );
    	printf( "Program link log:\n%s", log.get() );
	  }
	#endif
    GLint status;
	  glGetProgramiv( this->shaderHandle, GL_LINK_STATUS, &status );
    return status;
	}

  //------------------------------------------------------------------------------------------------
	void ChsShaderProgram::attachShader( const std::shared_ptr<ChsShader> & shader )const{
   	glAttachShader( this->getHandle(), shader->getHandle() );
	}

  //------------------------------------------------------------------------------------------------
	int ChsShaderProgram::getUniformLocation( const char * name ){
		return glGetUniformLocation( this->shaderHandle, name );
	}

  //------------------------------------------------------------------------------------------------

}//namespace

//--------------------------------------------------------------------------------------------------
