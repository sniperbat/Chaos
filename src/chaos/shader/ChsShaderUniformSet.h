#ifndef _CHS_SHADERUNIFORMSET_H
#define _CHS_SHADERUNIFORMSET_H
//--------------------------------------------------------------------------------------------------
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <map>
#include <boost/shared_ptr.hpp>
#include "ChsShaderUniform.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	class ChsShaderUniformSet{
	public:
		ChsShaderUniformSet( void );
		~ChsShaderUniformSet( void );
		void reset( void );
		void bindToShader( ChsShaderProgram * program );
		void add( const std::string & name, ChsShaderUniformDataType type, unsigned int count, void * varAddr = nullptr ); 
		template<typename T> void set( const std::string & name, T values );
	private:
		inline bool isExist( const std::string & name )const;
		ChsShaderProgram * program;
		std::map< std::string, boost::shared_ptr<ChsShaderUniform> > uniforms;
	};
  
	//------------------------------------------------------------------------------------------------
	inline bool ChsShaderUniformSet::isExist( const std::string & name )const{
		return uniforms.find( name ) != uniforms.end();
	}

  //------------------------------------------------------------------------------------------------
	template<typename T>
	void ChsShaderUniformSet::set( const std::string & name, T values ){
		auto iter = this->uniforms.find( name );
		if( iter == this->uniforms.end() )
			return;
		iter->second->set( values );
	}
	
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SHADERUNIFORMSET_H
