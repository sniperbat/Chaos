#ifndef _CHS_SHADER_H
#define _CHS_SHADER_H
#pragma once

#include "platform/ChsOpenGL.h"
//------------------------------------------------------------------------------------------------

namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	class ChsShader{
	public :
		ChsShader( int type );
		virtual ~ChsShader( void );
		bool load( const char * source );
    inline unsigned int getHandle( void )const;

	protected:
		int type;
    unsigned int shaderHandle;	
  private:
		bool compile( void );
		int getStatus( void );

	};
  
  //------------------------------------------------------------------------------------------------
	inline unsigned int ChsShader::getHandle( void )const{
    return this->shaderHandle;
  }
	
  //------------------------------------------------------------------------------------------------
	class ChsFragmentShader : public ChsShader{
	public:
		ChsFragmentShader( void ) : ChsShader( GL_FRAGMENT_SHADER ){}
	};

	//------------------------------------------------------------------------------------------------
	class ChsVertexShader : public ChsShader{
	public:
		ChsVertexShader( void ) : ChsShader( GL_VERTEX_SHADER ){}
	};

  //------------------------------------------------------------------------------------------------

}//namespace
#endif //_CHSSHADER_H
