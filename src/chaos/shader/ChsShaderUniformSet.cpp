#include <boost/foreach.hpp>
#include "ChsShaderUniformSet.h"
#include "ChsShaderManager.h"

//------------------------------------------------------------------------------------------------
namespace Chaos{
  
  //------------------------------------------------------------------------------------------------
	ChsShaderUniformSet::ChsShaderUniformSet( void ){
		this->reset();
	}
	
	//------------------------------------------------------------------------------------------------
	ChsShaderUniformSet::~ChsShaderUniformSet( void ){
		this->reset();
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsShaderUniformSet::reset( void ){
		this->uniforms.clear();
		this->program = nullptr;
	}	
  
  //------------------------------------------------------------------------------------------------
	void ChsShaderUniformSet::bind( void ){
    ChsShaderProgram * program = ChsShaderManager::getActiveShaderProgram();
		if( program == nullptr )
			return;
		bool needUpdateLocation = false;
		if( this->program != program ){
			needUpdateLocation = true;
			this->program = program;
		}
		std::pair<std::string, boost::shared_ptr<ChsShaderUniform> > p;
		BOOST_FOREACH( p, this->uniforms )
			p.second->bindToShader( program, needUpdateLocation );
	}

  //------------------------------------------------------------------------------------------------
	void ChsShaderUniformSet::add( const std::string & name, ChsShaderUniformDataType type, unsigned int count, void * varAddr ){
		if( this->isExist( name ) )
			return;
		boost::shared_ptr<ChsShaderUniform> uniform( new ChsShaderUniform() );
		uniform->init( name, type, count, varAddr );
    this->uniforms.insert( std::make_pair( name, uniform ) );
	}
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
