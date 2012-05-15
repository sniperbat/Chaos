#include <vector>
#include <boost/foreach.hpp>
#include "ChsTouchEmitter.h"
#include "ChsTouchListener.h"

namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  std::vector<ChsTouchListener*> listeners;
  
  //------------------------------------------------------------------------------------------------
  ChsTouchEmitter::ChsTouchEmitter( void ){
    this->purge();
  }
  
  //------------------------------------------------------------------------------------------------
  ChsTouchEmitter::~ChsTouchEmitter( void ){
    this->purge();
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::purge( void ){
    listeners.clear();
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::addListener( ChsTouchListener *listener ){
    auto iter = std::find( listeners.begin(), listeners.end(), listener );
    if( iter == listeners.end() )
      listeners.push_back( listener );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::removeListener( ChsTouchListener *listener ){
    auto iter = std::find( listeners.begin(), listeners.end(), listener );
    if( iter != listeners.end() )
      listeners.erase( iter );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::onTouchesBegan(){
    
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::onTouchesMove(){
    
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::onTouchesCancelled(){
    
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::onTouchesEnded(){
    
  }
  
  //------------------------------------------------------------------------------------------------
  //simple gesture
  void ChsTouchEmitter::onTap( int numberOfTaps, int numberOfTouches, const ChsPoint & position ){
    printf( "tap at: %f, %f, %d taps with %d fingers\n", position.x, position.y, numberOfTaps,numberOfTouches );
    BOOST_FOREACH( ChsTouchListener * listener, listeners ){
      if( listener->isTouchable() && listener->isAvaliable() )
        listener->onTap( numberOfTaps, numberOfTouches, position );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::onSwipe( int direction, int numberOfTouches, const ChsPoint & position ){
    printf( "swipe from:%f,%f to direction:%d, with %d fingers\n",position.x, position.y, direction, numberOfTouches );
    BOOST_FOREACH( ChsTouchListener * listener, listeners ){
      if( listener->isTouchable() && listener->isAvaliable() )
        listener->onSwipe( direction, numberOfTouches, position );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::onPinch( int state, float scale ,float velocity ){
    printf( "pinch state:%d with scale:%f and velocity:%f \n",state,scale,velocity );
    BOOST_FOREACH( ChsTouchListener * listener, listeners ){
      if( listener->isTouchable() && listener->isAvaliable() )
        listener->onPinch( static_cast<ChsGestureState>( state ), scale, velocity );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::onLongPress( int state, int numberOfTouches, const ChsPoint & position ){
    printf( "longPress at %f,%f on state:%d with %d fingers\n", position.x, position.y, state, numberOfTouches );
    BOOST_FOREACH( ChsTouchListener * listener, listeners ){
      if( listener->isTouchable() && listener->isAvaliable() )
        listener->onLongPress( state, numberOfTouches, position );
    }
  }
  
}
