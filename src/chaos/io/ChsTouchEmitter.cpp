#include <boost/foreach.hpp>
#include <vector>
#include "ChsTouchEmitter.h"
#include "ChsTouchListener.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  std::vector<ChsTouchListener*> listeners;
  
  //------------------------------------------------------------------------------------------------
  ChsTouchEmitter::ChsTouchEmitter( void ){
  }
  
  //------------------------------------------------------------------------------------------------
  ChsTouchEmitter::~ChsTouchEmitter( void ){
    this->purge();
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::purge( void ){
    if( !listeners.empty()) 
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
  void ChsTouchEmitter::handleTouches( ChsTouchType type, const ChsTouch & touch ){
    /*
    const char * types[] = {
      "CHS_TOUCH_TYPE_BEGAN",
      "CHS_TOUCH_TYPE_CHANGED",
      "CHS_TOUCH_TYPE_ENDED",
      "CHS_TOUCH_TYPE_CANCELLED",
      
      "CHS_TOUCH_TYPE_TAP",
      "CHS_TOUCH_TYPE_SWIPE",
      "CHS_TOUCH_TYPE_PINCH",
      "CHS_TOUCH_TYPE_LONGPRESS",
    };
    printf( "%s\n", types[type] );
    */
    BOOST_FOREACH( ChsTouchListener * listener, listeners ){
      listener->handleTouches( type, touch );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
