#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsResourceManager.h"
#include "ChsTextureEntity.h"
#include "ChsRenderStates.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsMaterial::ChsMaterial( void ) {
		this->shaderUniformSet.reset();
		this->textures.clear();
	}
  
	//------------------------------------------------------------------------------------------------
	ChsMaterial::~ChsMaterial( void ) {
		this->textures.clear();
		this->shaderUniformSet.reset();
	}

	//------------------------------------------------------------------------------------------------
	void ChsMaterial::addProperty( const std::string & name, ChsShaderUniformDataType type, int count ){
		this->shaderUniformSet.add( name, type, count );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMaterial::addTexture( const boost::shared_ptr<ChsTextureEntity> & texture ){
		if( texture ){
      ChsTextureEntity * texturePtr = texture.get();
      const std::string & sampleName = texturePtr->getSampleName();
      this->addProperty( sampleName, CHS_SHADER_UNIFORM_1_INT, 1);
      this->setProperty( sampleName, texturePtr->getActiveUnit() );
      this->textures.push_back( texture );
    }
	}
	
  //------------------------------------------------------------------------------------------------
  void ChsMaterial::apply( void ){
    ChsShaderProgram * activeProgram = ChsShaderManager::getActiveShaderProgram();
    ChsShaderProgram * program = activeProgram;
    if( !this->shaderProgram.expired() )
      program = this->shaderProgram.lock().get();
    if( program != nullptr ){
      if( program != activeProgram ){
        program->use();
        ChsShaderManager::setActiveShaderProgram( program );
      }

      for( const auto & p : this->renderStates ){
        ChsRenderStates::sharedInstance()->set( p.first,p.second );
      }
      this->shaderUniformSet.bind();
      for( boost::shared_ptr<ChsTextureEntity> & texture : this->textures ){
        texture->apply();
      }
      
		}
	}

	//------------------------------------------------------------------------------------------------
	#if 0
	void ChsMaterial::validate( void ) {
	// Validate program before drawing. This is a good check, but only really necessary in a debug build.
	// DEBUG macro must be defined in your debug configurations if that's not already the case.
    	if ( this->shaderProgram && !this->shaderProgram->validate() ) 
           printf("Failed to validate program: %d", this->shaderProgram->handle() );
	}
	#endif

  //------------------------------------------------------------------------------------------------
  void ChsMaterial::setShader( boost::shared_ptr<ChsShaderProgram> shader ){
    this->shaderProgram = shader;
  }
  
	//------------------------------------------------------------------------------------------------
	void ChsMaterial::setShader( const std::string & vshName, const std::string & fshName ){
		this->setShader( ChsResourceManager::sharedInstance()->getShaderProgram( vshName, fshName ) );
	}

	//------------------------------------------------------------------------------------------------
	void ChsMaterial::setRenderState( ChsRenderState state, unsigned int value ){
		auto iter = this->renderStates.find( state );
		if( iter != this->renderStates.end() ){
			this->renderStates[state] = value;
    }
		else{
      this->renderStates.insert( std::make_pair( state, value ) );
    }
	}
  
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
