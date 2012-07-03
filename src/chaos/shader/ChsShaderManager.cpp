#include <boost/scoped_array.hpp>
#include "ChsShaderManager.h"
#include "ChsShader.h"
#include "ChsShaderProgram.h"
#include "io/ChsFileSystem.h"
#include "core/ChsUtility.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{

  //------------------------------------------------------------------------------------------------
  ChsShaderProgram * ChsShaderManager::activeShader = nullptr;
  
	//------------------------------------------------------------------------------------------------
	template < typename ShaderType >
	boost::shared_ptr<ShaderType> ChsShaderManager::getShader( const std::string & name ) {
		boost::shared_ptr<ShaderType> shader = boost::dynamic_pointer_cast<ShaderType>( this->getFromCache( name ) );
		if( !shader ){
			//not in cache, so load source from file
			char * source = nullptr ;
      std::string fullpath = "shaders/" + name;
			ChsFileSystem::sharedInstance()->readFileAsUTF8( fullpath.c_str(), &source );
			if( source ){
				boost::scoped_array<char> sourcePtr( source );
        ShaderType * shaderInstance = new ShaderType();
				if( shaderInstance->load( source ) ){
					printf( "生成Shader:%s\n", fullpath.c_str() );
          shader = boost::shared_ptr<ShaderType>( shaderInstance );
					this->cache.insert( std::make_pair( name, shader ) );
				}
				else{
					safeDelete( &shaderInstance );
				}
			}
		}
	  return shader;
	}

  //------------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsVertexShader> ChsShaderManager::getVertexShader( const std::string & name ){
    return this->getShader< ChsVertexShader >( name );
	}

  //------------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsFragmentShader> ChsShaderManager::getFragmentShader( const std::string & name ){
    return this->getShader< ChsFragmentShader >( name );
	}

  //------------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsShaderProgram> ChsShaderManager::getShaderProgram( const std::string & vsName, const std::string & fsName ){
		std::string name  = vsName + "+" + fsName;
		boost::shared_ptr<ChsShaderProgram> program = boost::dynamic_pointer_cast<ChsShaderProgram>( this->getFromCache( name ) );
		if( !program ){
			program.reset( new ChsShaderProgram() );
			boost::shared_ptr<ChsVertexShader> vs = this->getShader<ChsVertexShader>( vsName );
			assert( vs );
			boost::shared_ptr<ChsFragmentShader> fs = this->getShader<ChsFragmentShader>( fsName );
			assert( fs );
			program->attachShader( vs );
			program->attachShader( fs );
      assert( program->link() );
 			printf( "生成ShaderProgram:%s\n", name.c_str() );
      this->cache.insert( std::make_pair( name, program ) );
		}
		return program;
	}

  //------------------------------------------------------------------------------------------------

}//namespace

//--------------------------------------------------------------------------------------------------
