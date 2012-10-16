#ifndef _CHSMATERIAL_H
#define _CHSMATERIAL_H
//--------------------------------------------------------------------------------------------------
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
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
    
    void apply( void );
		
    void addProperty( const std::string & name, ChsShaderUniformDataType type, int count );
		template<typename T> void setProperty( const std::string & name, T value );
	  
    void setShader( const std::string & vshName, const std::string & fshName );
    void setShader( boost::shared_ptr<ChsShaderProgram> );
    
		void setRenderState( ChsRenderState state, unsigned int value );
		void addTexture( const boost::shared_ptr<ChsTextureEntity> & texture );
    
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
	template<typename T> void ChsMaterial::setProperty( const std::string & name, T value ){
		this->shaderUniformSet.set( name, value );
	}
	
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHSMATERIAL_H