#ifndef _CHS_SHADERMANAGER_H
#define _CHS_SHADERMANAGER_H
//--------------------------------------------------------------------------------------------------
#include "ChsManagerWithCache.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
	class ChsShader;
	class ChsVertexShader;
	class ChsFragmentShader;
	class ChsShaderProgram;

  //------------------------------------------------------------------------------------------------
	class ChsShaderManager : public ChsManagerWithCache< ChsShader >{
	public:
    std::shared_ptr<ChsShaderProgram> getShaderProgram( const std::string & vertexShaderName, const std::string & fragmentShaderName );
    inline static ChsShaderProgram * getActiveShaderProgram( void );
    inline static void setActiveShaderProgram( ChsShaderProgram * );
  private:
    static ChsShaderProgram * activeShader;
    template < typename ShaderType >
    std::shared_ptr<ShaderType> getShader( const std::string & name );
    std::shared_ptr<ChsVertexShader> getVertexShader( const std::string & name );
    std::shared_ptr<ChsFragmentShader> getFragmentShader( const std::string & name );
	};

	//------------------------------------------------------------------------------------------------
  inline ChsShaderProgram * ChsShaderManager::getActiveShaderProgram( void ){
    return ChsShaderManager::activeShader;
  }
  
  //------------------------------------------------------------------------------------------------
  inline void ChsShaderManager::setActiveShaderProgram( ChsShaderProgram * shaderProgram ){
    ChsShaderManager::activeShader = shaderProgram;
  }

  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SHADERMANAGER_H
