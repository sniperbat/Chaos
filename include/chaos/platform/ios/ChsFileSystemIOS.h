#ifndef _CHS_FILESYSTEMIO_H
#define _CHS_FILESYSTEMIO_H
//--------------------------------------------------------------------------------------------------
#include "ChsFileSystem.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	class ChsFileSystemIOS final : public ChsFileSystem {
	public:
    int readFileAsUTF8( const char * path, char ** data ) override;
		int readFileAsRaw( const char *  path , char ** data ) override;
		static NSString * getFullPath( const char * path );
	};

	//------------------------------------------------------------------------------------------------
	
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHS_FILESYSTEMIO_H
