#ifndef _CHS_TOUCHLISTENER_H
#define _CHS_TOUCHLISTENER_H
//--------------------------------------------------------------------------------------------------
#include "ChsDefine.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  class ChsTouchListener{
   friend class ChsTouchEmitter;
  public:
    ChsTouchListener( void );

    inline bool isTouchable( void )const;
    inline void setTouchable( bool enable );

  private:
    bool touchable;
    typedef void (ChsTouchListener::*TouchHandleFunc) ( const ChsTouch & touch );
    TouchHandleFunc handlers[CHS_TOUCH_TYPE_MAX];
    void handleTouches( ChsTouchType type, const ChsTouch & touch );
  
  protected:
    //touch event access by ChsTouchEmitter as friend class
    //basic touch event
    virtual void onTouchesBegan( const ChsTouch & touch ){}
    virtual void onTouchesMove( const ChsTouch & touch ){}
    virtual void onTouchesCancelled( const ChsTouch & touch ){}
    virtual void onTouchesEnded( const ChsTouch & touch ){}
    
    //simple gesture
    virtual void onTap( const ChsTapTouch & touch ){}
    virtual void onSwipe( const ChsSwipeTouch & touch ){}
    virtual void onPinch( const ChsPinchTouch & touch ){}
    virtual void onLongPress( const ChsLongPressTouch & touch ){}
    
    virtual bool isAvaliable(void ){ return true; };

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

//--------------------------------------------------------------------------------------------------
#endif//_CHS_TOUCHLISTENER_H
