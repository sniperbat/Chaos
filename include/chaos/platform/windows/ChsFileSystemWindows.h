#ifndef _CHS_FILESYSTEMWINDOWS_H
#define _CHS_FILESYSTEMWINDOWS_H
#pragma once

//--------------------------------------------------------------------------------------------------
#include "io/ChsFileSystem.h"
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	class ChsFileSystemWindows final : public ChsFileSystem {
	public:
    int readFileAsUTF8( const char * path, char ** data ) override;
		int readFileAsRaw( const char *  path , char ** data ) override;
	};

	//------------------------------------------------------------------------------------------------
	
}//namespace

#endif //_CHS_FILESYSTEMWINDOWS_H
