#include <string.h>
#include <fstream>
#include "ChsFileSystemWindows.h"

//--------------------------------------------------------------------------------------------------

namespace Chaos {

	//------------------------------------------------------------------------------------------------
	ChsFileSystemWindows gFileSystem;

  //------------------------------------------------------------------------------------------------
	int ChsFileSystemWindows::readFileAsUTF8( const char * path, char ** data ){
		//NSString * fullPathName = getFullPath( path );
		int length = 0;
    std::ifstream ifs( path, std::ios::in );
    if(!ifs.fail()){
      ifs.seekg( 0, std::ios::end );
      length = static_cast<int>( ifs.tellg() );
      ifs.seekg( 0, std::ios::beg );
      *data = new char [length+4];
      memset( *data, 0, sizeof( char ) * ( length + 4) );
      ifs.read( *data, length );
      ifs.close();
    }
   	return length;
	}
	
	//------------------------------------------------------------------------------------------------
	int ChsFileSystemWindows::readFileAsRaw( const char * path, char ** data ){
   	//NSString * fullPathName = getFullPath( path );
    int length = 0;
    std::ifstream ifs;
    ifs.open( path, std::ios::in | std::ios::binary );
    if(!ifs.fail()){
      ifs.seekg( 0, std::ios::end );
      length = static_cast<int>( ifs.tellg() );
      ifs.seekg( 0, std::ios::beg );
      *data = new char [length];
      ifs.read( *data, length );
      ifs.close();
    }
   	return length;
	}

	//------------------------------------------------------------------------------------------------
  
}//namespace
