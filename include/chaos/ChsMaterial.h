#ifndef _CHSMATERIAL_H
#define _CHSMATERIAL_H
//--------------------------------------------------------------------------------------------------
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
    void setShader( std::shared_ptr<ChsShaderProgram> );
    
		void setRenderState( ChsRenderStateId id, ChsRenderState state );
		void addTexture( const std::shared_ptr<ChsTextureEntity> & texture );
    
    inline std::weak_ptr<ChsShaderProgram> getShaderProgram( void )const;
	private:
		std::map<ChsRenderStateId,ChsRenderState > renderStates;
		std::vector< std::shared_ptr<ChsTextureEntity> > textures;
		
		ChsShaderUniformSet shaderUniformSet;
    std::weak_ptr<ChsShaderProgram> shaderProgram;
	};

  //------------------------------------------------------------------------------------------------
	std::weak_ptr<ChsShaderProgram> ChsMaterial::getShaderProgram( void )const{
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
