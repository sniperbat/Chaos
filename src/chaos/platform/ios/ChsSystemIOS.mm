#import <Foundation/Foundation.h>

#include "../ChsSystem.h"

namespace Chaos{

  double getSystemTime( void ){
    CFAbsoluteTime time =  CFAbsoluteTimeGetCurrent();
    return time;
  }
  
}
