#ifndef _CHSMATERIAL_H
#define _CHSMATERIAL_H
#pragma once

#include <boost/weak_ptr.hpp>
#include "shader/ChsShaderUniformSet.h"
#include "ChsTextureEntity.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
  class ChsShaderProgram;
	class ChsTextureEntity;
	
  //------------------------------------------------------------------------------------------------
	class ChsMaterial {
	public:
    ChsMaterial( void );
	  virtual ~ChsMaterial( void );
    
    ChsShaderProgram * apply( ChsShaderProgram * program );
		
    void addProperty( std::string name, ChsShaderUniformDataType type, int count );
		template<typename T> void setProperty( std::string name, T value );
		template<typename T> T getProperty( std::string name );
	  
    void setShader( std::string vshName, std::string fshName );
		void setRenderState( ChsRenderState state, unsigned int value );
		void addTexture( boost::shared_ptr<ChsTextureEntity> & texture );
		void linkShader( void );
    
    inline boost::weak_ptr<ChsShaderProgram> getShaderProgram( void )const;
	private:
		std::map<ChsRenderState,unsigned int> renderStates;
		std::vector< boost::shared_ptr<ChsTextureEntity> > textures;
		
		ChsShaderUniformSet shaderUniformSet;
    boost::weak_ptr<ChsShaderProgram> shaderProgram;
	};

  //------------------------------------------------------------------------------------------------
	boost::weak_ptr<ChsShaderProgram> ChsMaterial::getShaderProgram( void )const{
    return this->shaderProgram;
  }

  //------------------------------------------------------------------------------------------------
	template<typename T> void ChsMaterial::setProperty( std::string name, T value ){
		this->shaderUniformSet.set( name, value );
	}
	
	//------------------------------------------------------------------------------------------------
	template<typename T> T ChsMaterial::getProperty( std::string name ){
		return this->shaderUniformSet.get<T>( name );
	}
  
  //------------------------------------------------------------------------------------------------
  
}//namespace

#endif //_CHSMATERIAL_H
