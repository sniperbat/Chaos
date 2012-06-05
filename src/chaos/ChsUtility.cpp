#include <boost/scoped_ptr.hpp>
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
  int getTexWrapValue( const std::string & valueName ){
    if( !valueName.compare( "REPEAT" ) )
      return GL_REPEAT;
    else if( !valueName.compare( "CLAMP_TO_EDGE" ) )
      return GL_CLAMP_TO_EDGE;
    else if( !valueName.compare( "MIRRORED_REPEAT" ) )
      return GL_MIRRORED_REPEAT;
    return -1;
  }
  
  //------------------------------------------------------------------------------------------------
  std::string readString( char * & data ){
		int strCount = readData<int>( data );
		boost::scoped_ptr<char> p( new char[strCount+1] );
		memset( p.get(), 0, strCount+1 );
		memcpy( p.get(), data, strCount );
		std::string str = p.get();
		skipData( data, strCount );
		return str;
	}
  
}//namespace
