#ifndef _CHS_SHADERUNIFORM_H
#define _CHS_SHADERUNIFORM_H

#include "ChsDefine.h"
//--------------------------------------------------------------------------------------------------

namespace Chaos {

  //------------------------------------------------------------------------------------------------
	class ChsShaderProgram;
	#define UNLOCATED -1

  //------------------------------------------------------------------------------------------------
	class ChsShaderUniform {
	public:
		ChsShaderUniform( void );
		~ChsShaderUniform( void );
		void init( const std::string & name, ChsShaderUniformDataType type, int count, void * varAddr = nullptr );
		void apply( ChsShaderProgram * program, bool needUpdateLocation );
		template<typename T> void set( T value );
		template<typename T> T get( void )const;
	private:
		std::string name;
		int type;
		unsigned int count;
		int location;
		void * linkedValuePtr;
		union{
			float * fValuePtr;
			int * iValuePtr;
		};
	};
	
	//------------------------------------------------------------------------------------------------
	template<typename T>
	void ChsShaderUniform::set( T value ){
		if( this->fValuePtr ){
			if( this->type == CHS_SHADER_UNIFORM_1_INT )
				*( this->iValuePtr ) = value;
			else if( this->type == CHS_SHADER_UNIFORM_1_FLOAT )
				*( this->fValuePtr ) = value;
		}
	}
  
	//------------------------------------------------------------------------------------------------
	template<typename T>
	T ChsShaderUniform::get( void )const{
		if( this->type == CHS_SHADER_UNIFORM_1_INT )
			return *( this->iValuePtr );
		else if( this->type == CHS_SHADER_UNIFORM_1_FLOAT )
			return *( this->fValuePtr );
		else
			return 0;
	}

}

//------------------------------------------------------------------------------------------------

#endif//_CHS_SHADERUNIFORM_H
