#import <Foundation/Foundation.h>

#include "platform/ChsSystem.h"

namespace Chaos{

  double getSystemTime( void ){
    CFAbsoluteTime time =  CFAbsoluteTimeGetCurrent();
    return time;
  }
  
}
