#ifndef _CHS_CLASSFACTORY_H
#define _CHS_CLASSFACTORY_H

#include <map>
#include <string>

namespace Chaos {
  
  template < typename ClassType, typename ClassCreator = ClassType * (*)() >
  class ChsClassFactory{
  private:
    std::map< std::string, ClassCreator > classCreators;
   public:
    static ChsClassFactory * sharedInstance(){
      static ChsClassFactory<ClassType> instance;
      return &instance;
    }

    bool registerClass( const std::string & className, ClassCreator creator ){
      auto iter = this->classCreators.find( className );
      if( iter == this->classCreators.end() ){
        this->classCreators.insert( std::make_pair( className, creator ) );
        return true;
      }
      return false;
    }
    
    ClassType * create( const std::string & className ){
      auto iter = this->classCreators.find( className );
      if( iter != this->classCreators.end() ){
        return ( iter->second )();
      }
      return nullptr;
    }
  };

}

#endif//_CHS_CLASSFACTORY_H
