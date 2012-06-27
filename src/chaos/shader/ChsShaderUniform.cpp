#include "platform/ChsOpenGL.h"
#include "ChsShaderUniform.h"
#include "ChsShaderProgram.h"
#include "core/ChsUtility.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	ChsShaderUniform::ChsShaderUniform( void ) : valuePtr( nullptr ),linkedValuePtr( nullptr ){
	}
  
	//------------------------------------------------------------------------------------------------
	ChsShaderUniform::~ChsShaderUniform( void ){
		safeDeleteArray( &this->valuePtr );
	}
  
	//------------------------------------------------------------------------------------------------
	void ChsShaderUniform::bindToShader( ChsShaderProgram * program, bool needUpdateLocation ){
		if( this->location == CHS_SHADER_UNIFORM_UNLOCATED || needUpdateLocation ) {
			//looking for uniform in program
			GLint location = program->getUniformLocation( this->name.c_str() );
			if( location < 0 )
				return;//no uniform named that in program, process next
			this->location = location;//save location, because it is a reference
		}

		void * ptr = this->linkedValuePtr;
		if( !ptr )
			ptr = this->valuePtr;
		switch ( this->type ){
			case CHS_SHADER_UNIFORM_MAT2:
				glUniformMatrix2fv( this->location, this->count, false, (const GLfloat*)ptr );
				break;
			case CHS_SHADER_UNIFORM_MAT3:
				glUniformMatrix3fv( this->location, this->count, false, (const GLfloat*)ptr );
				break;
			case CHS_SHADER_UNIFORM_MAT4:
				glUniformMatrix4fv( this->location, this->count, false, (const GLfloat*)ptr );
				break;
      case CHS_SHADER_UNIFORM_VEC4_FLOAT:
        glUniform4fv( this->location, this->count, (const GLfloat*)ptr );
        break;
      case CHS_SHADER_UNIFORM_VEC3_FLOAT:
        glUniform3fv( this->location, this->count, (const GLfloat*)ptr );
        break;
      case CHS_SHADER_UNIFORM_VEC2_FLOAT:
        glUniform2fv( this->location, this->count, (const GLfloat*)ptr );
        break;
      case CHS_SHADER_UNIFORM_1_FLOAT:
        glUniform1fv( this->location, this->count, (const GLfloat*)ptr );
        break;
      case CHS_SHADER_UNIFORM_VEC4_INT:
        glUniform4iv( this->location, this->count, (const GLint*)ptr );
        break;
      case CHS_SHADER_UNIFORM_VEC3_INT:
        glUniform3iv( this->location, this->count, (const GLint*)ptr );
        break;
      case CHS_SHADER_UNIFORM_VEC2_INT:
        glUniform2iv( this->location, this->count, (const GLint*)ptr );
        break;
      case CHS_SHADER_UNIFORM_1_INT:
        glUniform1iv( this->location, this->count, (const GLint*)ptr );
        break;
			default:
				break;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsShaderUniform::init( const std::string & name, ChsShaderUniformDataType type, int count, void * varAddr ){
		this->location = CHS_SHADER_UNIFORM_UNLOCATED;
		this->name = name;
		this->type = type;
		this->count = count;
		if( varAddr ){
			this->linkedValuePtr = varAddr;
		}
		else{
			switch ( this->type ){
				case CHS_SHADER_UNIFORM_MAT2:
					this->valuePtr = new char[ this->count * 4 * sizeof(float) ];
					break;
				case CHS_SHADER_UNIFORM_MAT3:
					this->valuePtr = new char[ this->count * 9 * sizeof(float) ];
					break;
				case CHS_SHADER_UNIFORM_MAT4:
					this->valuePtr = new char[ this->count * 16 * sizeof(float) ];
					break;
				default:
					GLsizei size = this->count * ( this->type / 2 + 1 );
          this->valuePtr = new char[ size * sizeof(int) ];
					break;
			}
		}
	}
  
	//------------------------------------------------------------------------------------------------

}

//--------------------------------------------------------------------------------------------------
