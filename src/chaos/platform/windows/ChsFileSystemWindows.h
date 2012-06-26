#ifndef _CHS_FILESYSTEMWINDOWS_H
#define _CHS_FILESYSTEMWINDOWS_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "io/ChsFileSystem.h"
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	class ChsFileSystemWindows: public ChsFileSystem {
	public:
    int readFileAsUTF8( const char * path, char ** data );
		int readFileAsRaw( const char *  path , char ** data );
	};

	//------------------------------------------------------------------------------------------------
	
}//namespace

#endif //_CHS_FILESYSTEMWINDOWS_H
