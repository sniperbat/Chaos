#ifndef _CHS_TOUCHEMITTER_H
#define _CHS_TOUCHEMITTER_H
//--------------------------------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "core/ChsSingleton.h"
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
    
    void addListener( boost::shared_ptr<ChsTouchListener> listener );
    void removeListener( boost::shared_ptr<ChsTouchListener> listener );
    
    void purge( void );
    
    void handleTouches( ChsTouchType type, const ChsTouch & touch )const;
  };
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_TOUCHEMITTER_H
