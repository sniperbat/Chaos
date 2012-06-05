#ifndef _CHS_SHADERUNIFORM_H
#define _CHS_SHADERUNIFORM_H
//--------------------------------------------------------------------------------------------------
#include <string>
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
 		template<typename T> void set( T* value );
	private:
		std::string name;
		int type;
		unsigned int count;
		int location;
		void * linkedValuePtr;
    char * valuePtr;
	};
	
	//------------------------------------------------------------------------------------------------
	template<typename T> void ChsShaderUniform::set( T value ){
		if( this->valuePtr ){
      T * ptr = reinterpret_cast<T*>(this->valuePtr);
      *ptr = value;
    }
	}
  
	//------------------------------------------------------------------------------------------------
	template<typename T> void ChsShaderUniform::set( T* value ){
    if( this->valuePtr ){
      int size = this->count * ( this->type / 2 + 1 );
      memcpy( this->valuePtr, (void *)value, sizeof(char) * 4 * size );
    }
	}
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SHADERUNIFORM_H
