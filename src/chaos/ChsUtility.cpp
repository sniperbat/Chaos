#include "ChsUtility.h"
#include "platform/ChsOpenGL.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	size_t getGLDataTypeSize( int type ){
		switch( type ){
			case GL_BYTE:
			case GL_UNSIGNED_BYTE:
				return sizeof( char );
			case GL_INT:
			case GL_UNSIGNED_INT:
				return sizeof( int );
			case GL_SHORT:
			case GL_UNSIGNED_SHORT:
				return sizeof( short );
			case GL_FLOAT:
				return sizeof( float );
			default:
				return -1;//unsupported type
			}
	}
	
  //------------------------------------------------------------------------------------------------
  ChsTexParameterType getTexParamterType( const std::string & typeName ){
    if( !typeName.compare( "WRAP_S" ) )
      return CHS_TEXPARAM_WRAP_S;
    else if( !typeName.compare( "WRAP_T" ) )
      return CHS_TEXPARAM_WRAP_T;
    else if( !typeName.compare( "MAG_FILTER" ) )
      return CHS_TEXPARAM_MAG_FILTER;
    else if( !typeName.compare( "MIN_FILTER" ) )
      return CHS_TEXPARAM_MIN_FILTER;
    return CHS_TEXPARAM_MAX;
  }
  
  //------------------------------------------------------------------------------------------------
  int getTexParamterValue( const std::string & valueName ){
    if( !valueName.compare( "NEAREST" ) )
      return GL_NEAREST;
    else if( !valueName.compare( "LINEAR" ) )
      return GL_LINEAR;
    else if( !valueName.compare( "NEAREST_MIPMAP_NEAREST" ) )
      return GL_NEAREST_MIPMAP_NEAREST;
    else if( !valueName.compare( "LINEAR_MIPMAP_NEAREST" ) )
      return GL_LINEAR_MIPMAP_NEAREST;
    else if( !valueName.compare( "NEAREST_MIPMAP_LINEAR" ) )
      return GL_NEAREST_MIPMAP_LINEAR;
    else if( !valueName.compare( "LINEAR_MIPMAP_LINEAR" ) )
      return GL_LINEAR_MIPMAP_LINEAR;
    else if( !valueName.compare( "REPEAT" ) )
      return GL_REPEAT;
    else if( !valueName.compare( "CLAMP_TO_EDGE" ) )
      return GL_CLAMP_TO_EDGE;
    else if( !valueName.compare( "MIRRORED_REPEAT" ) )
      return GL_MIRRORED_REPEAT;
    return -1;
  }

  
}//namespace
