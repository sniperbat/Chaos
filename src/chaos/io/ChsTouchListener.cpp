#include "ChsTouchListener.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  ChsTouchListener::ChsTouchListener( void ){ 
    this->touchable = true;
    
    this->handlers[CHS_TOUCH_TYPE_BEGAN] = &ChsTouchListener::onTouchesBegan;
    this->handlers[CHS_TOUCH_TYPE_CHANGED] = &ChsTouchListener::onTouchesMove;
    this->handlers[CHS_TOUCH_TYPE_ENDED] = &ChsTouchListener::onTouchesEnded;
    this->handlers[CHS_TOUCH_TYPE_CANCELLED] = &ChsTouchListener::onTouchesCancelled;
    
    this->handlers[CHS_TOUCH_TYPE_TAP] = (TouchHandleFunc)&ChsTouchListener::onTap;
    this->handlers[CHS_TOUCH_TYPE_SWIPE] = (TouchHandleFunc)&ChsTouchListener::onSwipe;
    this->handlers[CHS_TOUCH_TYPE_PINCH] = (TouchHandleFunc)&ChsTouchListener::onPinch;
    this->handlers[CHS_TOUCH_TYPE_LONGPRESS] = (TouchHandleFunc)&ChsTouchListener::onLongPress;
  }

  //------------------------------------------------------------------------------------------------
  void ChsTouchListener::handleTouches( ChsTouchType type, const ChsTouch & touch ){
    if( type > CHS_TOUCH_TYPE_INVALID && type < CHS_TOUCH_TYPE_MAX )
      if( this->isTouchable() && this->isAvaliable() )
        (this->*handlers[type])( touch );
  }
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
