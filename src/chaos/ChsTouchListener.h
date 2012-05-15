#ifndef _CHS_TOUCHLISTENER_H
#define _CHS_TOUCHLISTENER_H
//--------------------------------------------------------------------------------------------------
#include "ChsDefine.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  //------------------------------------------------------------------------------------------------
  class ChsTouchListener{
  public:
    ChsTouchListener( void ){ this->touchable = true; }

    //basic touch event
    virtual void onTouchesBegan(){}
    virtual void onTouchesMove(){}
    virtual void onTouchesCancelled(){}
    virtual void onTouchesEnded(){}
    
    //simple gesture
    virtual void onTap( int numberOfTaps, int numberOfTouches, const ChsPoint & position ){}
    virtual void onSwipe( int direction, int numberOfTouches, const ChsPoint & position ){}
    virtual void onPinch( ChsGestureState state, float scale, float velocity ){}
    virtual void onLongPress( int state, int numberOfTouches, const ChsPoint & position ){}
    
    inline bool isTouchable( void )const;
    inline void setTouchable( bool enable );
    
    virtual bool isAvaliable(void ){ return true; };
    
  private:
    bool touchable;
  };
  
  //------------------------------------------------------------------------------------------------
  inline bool ChsTouchListener::isTouchable( void )const{
    return this->touchable;
  }
  
  //------------------------------------------------------------------------------------------------
  inline void ChsTouchListener::setTouchable( bool enable ){
    this->touchable = enable;
  }
  
  //------------------------------------------------------------------------------------------------
}

#endif//_CHS_TOUCHLISTENER_H
