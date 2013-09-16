#ifndef _CHS_SHADERPROGRAM_H
#define _CHS_SHADERPROGRAM_H
//--------------------------------------------------------------------------------------------------
#include <memory>
#include "ChsShader.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	class ChsShaderProgram : public ChsShader{
	public:
		ChsShaderProgram( void );
		~ChsShaderProgram( void );
    
		bool link( void )const;
		void use( void )const;
		bool validate( void )const;
		void attachShader( const std::shared_ptr<ChsShader> & shader )const;
		int getUniformLocation( const char * name );
		
	private:
		int getStatus( void )const;
		bool load( const char * source )const{ (void)source;return false; }
	};

  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHS_SHADERPROGRAM_H
