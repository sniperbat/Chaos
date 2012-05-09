#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsResourceManager.h"
#include "ChsTexture2D.h"
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
	void ChsMaterial::addProperty( std::string name, ChsShaderUniformDataType type, int count ){
		this->shaderUniformSet.add( name, type, count );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMaterial::addTexture( boost::shared_ptr<ChsTexture2D> texture ){
		if( !texture )
			return;
		this->addProperty( texture->getSampleName(), CHS_SHADER_UNIFORM_1_INT, 1);
		this->setProperty( texture->getSampleName(), texture->getActiveUnit() );
		this->textures += texture;
	}
	
	//------------------------------------------------------------------------------------------------
	ChsShaderProgram * ChsMaterial::apply( ChsShaderProgram * sysProgram ) {
		ChsShaderProgram * currentProgram = sysProgram;
    if( !this->shaderProgram.expired() )
				currentProgram = this->shaderProgram.lock().get();      
		if( currentProgram ){
      if( currentProgram != sysProgram )
        currentProgram->use();
			std::pair<ChsRenderState,unsigned int> p;
			BOOST_FOREACH( p, this->renderStates )
				ChsRenderStates::sharedInstance()->set( p.first,p.second );
			this->shaderUniformSet.apply( currentProgram );
			BOOST_FOREACH( boost::shared_ptr<ChsTexture2D> & texture, this->textures )
				texture->bind();
		}
		return currentProgram;
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
	void ChsMaterial::setShader( std::string vshName, std::string fshName ){
		this->shaderProgram = ChsResourceManager::sharedInstance()->getShaderProgram( vshName, fshName );
	}

	//------------------------------------------------------------------------------------------------
	void ChsMaterial::linkShader( void ){
		if( !this->shaderProgram.expired() ){
			boost::shared_ptr<ChsShaderProgram> shaderProgram = this->shaderProgram.lock();
			shaderProgram->link();
		}
	}

	//------------------------------------------------------------------------------------------------
	void ChsMaterial::setRenderState( ChsRenderState state, unsigned int value ){
		auto iter = this->renderStates.find( state );
		if( iter != this->renderStates.end() ){
			this->renderStates[state] = value;
		}
		else{
			insert( this->renderStates )( state, value );
		}
	}
  
  //------------------------------------------------------------------------------------------------
  
}//namespace
