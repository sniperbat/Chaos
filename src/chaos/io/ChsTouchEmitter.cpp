#include <vector>
#include <algorithm>
#include "ChsTouchEmitter.h"
#include "ChsTouchListener.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  std::vector< std::shared_ptr<ChsTouchListener> > listeners;
  
  //------------------------------------------------------------------------------------------------
  ChsTouchEmitter::ChsTouchEmitter( void ){
  }
  
  //------------------------------------------------------------------------------------------------
  ChsTouchEmitter::~ChsTouchEmitter( void ){
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::purge( void ){
    listeners.clear();
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::addListener( std::shared_ptr<ChsTouchListener> listener ){
    auto iter = std::find( listeners.begin(), listeners.end(), listener );
    if( iter == listeners.end() ){
      listeners.push_back( listener );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::removeListener( std::shared_ptr<ChsTouchListener> listener ){
    auto iter = std::find( listeners.begin(), listeners.end(), listener );
    if( iter != listeners.end() ){
      listeners.erase( iter );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTouchEmitter::handleTouches( ChsTouchType type, const ChsTouch & touch )const{
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
    for( const auto & listener : listeners ){
      listener->handleTouches( type, touch );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
