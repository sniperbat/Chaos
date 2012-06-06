#ifndef _CHS_SHADER_H
#define _CHS_SHADER_H
//--------------------------------------------------------------------------------------------------
#include "ChsDefine.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	class ChsShader{
	public :
		ChsShader( void );
		virtual ~ChsShader( void );
		bool load( const char * source )const;
    inline unsigned int getHandle( void )const;

	protected:
		ChsShaderType type;
    unsigned int shaderHandle;
  private:
		bool compile( void )const;
		int getStatus( void )const;

	};
  
  //------------------------------------------------------------------------------------------------
	inline unsigned int ChsShader::getHandle( void )const{
    return this->shaderHandle;
  }

	//------------------------------------------------------------------------------------------------
	class ChsVertexShader : public ChsShader{
	public:
		ChsVertexShader( void );
	};
	
  //------------------------------------------------------------------------------------------------
	class ChsFragmentShader : public ChsShader{
	public:
		ChsFragmentShader( void );
	};

  //------------------------------------------------------------------------------------------------

}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHSSHADER_H
