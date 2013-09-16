#ifndef _CHS_TOUCHEMITTER_H
#define _CHS_TOUCHEMITTER_H
//--------------------------------------------------------------------------------------------------
#include <memory>
#include "core/ChsSingleton.h"
#include "ChsDefine.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
  class ChsTouchListener;
  
  //------------------------------------------------------------------------------------------------
  class ChsTouchEmitter final : public ChsSingleton<ChsTouchEmitter> {
  public:
    ChsTouchEmitter( void );
    ~ChsTouchEmitter( void );
    
    void addListener( std::shared_ptr<ChsTouchListener> listener );
    void removeListener( std::shared_ptr<ChsTouchListener> listener );
    
    void purge( void );
    
    void handleTouches( ChsTouchType type, const ChsTouch & touch )const;
  };
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_TOUCHEMITTER_H
