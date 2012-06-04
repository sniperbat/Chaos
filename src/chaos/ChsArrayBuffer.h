#ifndef CHS_ARRAYBUFFER_H
#define CHS_ARRAYBUFFER_H
//--------------------------------------------------------------------------------------------------
#include "platform/ChsOpenGL.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  class ChsArrayBuffer{
  protected:
    char * buffer;
		int size;
    int capacity;
		bool isNeedUpdate;
 		unsigned int vboHandle;
    
  public:
    ChsArrayBuffer( void );
    virtual ~ChsArrayBuffer( void );
    
    void init( int size );
    void setDataWithArray( const void * buffer, int size );
  };
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//CHS_ARRAYBUFFER_H
