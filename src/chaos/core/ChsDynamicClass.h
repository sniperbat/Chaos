#ifndef _CHS_DYNAMIC_CLASS_H
#define _CHS_DYNAMIC_CLASS_H

#include "core/ChsClassFactory.h"

namespace Chaos{

  template<typename AbstractClassType, typename ClassType>
  class ChsDynamicClass : public AbstractClassType{
  public:
    static bool registerAsDynamic( const std::string & className ){
      ChsClassFactory<AbstractClassType>::sharedInstance()->registerClass( className, ChsDynamicClass::creator );
      return true;
    }
    static AbstractClassType * creator(){
      return new ClassType();
    }
  };
}

#endif//_CHS_DYNAMIC_CLASS_H
