#ifndef _CHS_TOUCHEMITTER_H
#define _CHS_TOUCHEMITTER_H
//--------------------------------------------------------------------------------------------------
#include "ChsSingleton.h"
#include "ChsDefine.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
  class ChsTouchListener;
  
  //------------------------------------------------------------------------------------------------
  class ChsTouchEmitter : public ChsSingleton<ChsTouchEmitter> {
  public:
    ChsTouchEmitter( void );
    ~ChsTouchEmitter( void );
    
    void addListener( ChsTouchListener * listener );
    void removeListener( ChsTouchListener * listener );
    
    void purge( void );
    
    void handleTouches( ChsTouchType type, const ChsTouch & touch );
  };
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_TOUCHEMITTER_H
