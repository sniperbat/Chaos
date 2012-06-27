#ifndef _CHS_SCENE_H
#define _CHS_SCENE_H

#include <boost/scoped_ptr.hpp>
#include <string>
#include "ChsClassFactory.h"
#include "ChsRenderNode.h"

namespace Chaos {

  //------------------------------------------------------------------------------------------------
  class ChsSceneRoot : public ChsRenderNode{
  public:
    ChsSceneRoot( void ) : ChsRenderNode( "root" ){}
    void update( void ){}
  };
  
  //------------------------------------------------------------------------------------------------  
  class ChsScene{
  public:
    ChsScene( void ) : root( new ChsSceneRoot() ){}
    virtual ~ChsScene( void ){};
    
    virtual void onEnter( void ) = 0;
    virtual void onExit( void ) = 0;
    virtual void onUpdate( float dt ) = 0;
    virtual void onInit( void ) = 0;
    virtual void onRelease( void ) = 0;

    ChsNode * getRoot( void ){
      return this->root.get();
    }

  protected:
    template <typename T> static ChsScene * creator(){
      return new T();
    }
  
  private:
    boost::scoped_ptr<ChsRenderNode> root;
  };

  //------------------------------------------------------------------------------------------------
}

#endif//_CHS_SCENE_H
