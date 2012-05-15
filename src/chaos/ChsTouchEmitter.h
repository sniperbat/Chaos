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
    
    //basic touch event
    void onTouchesBegan();
    void onTouchesMove();
    void onTouchesCancelled();
    void onTouchesEnded();

    //simple gesture
    void onTap( int numberOfTaps, int numberOfTouches, const ChsPoint & position );
    void onSwipe( int direction, int numberOfTouches, const ChsPoint & position );
    void onPinch( int state, float scale, float velocity );
    void onLongPress( int state, int numberOfTouches, const ChsPoint & position );

    
  };
  
  //------------------------------------------------------------------------------------------------
}


#endif//_CHS_TOUCHEMITTER_H
