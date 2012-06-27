#ifndef _CHS_SCENE_H
#define _CHS_SCENE_H

#include <boost/scoped_ptr.hpp>
#include <string>
#include "ChsRenderNode.h"

namespace Chaos {
  class ChsRenderNode;
  //------------------------------------------------------------------------------------------------  
  class ChsScene{
  public:
    ChsScene( void );
    virtual ~ChsScene( void ){};
    
    virtual void onEnter( void ) = 0;
    virtual void onExit( void ) = 0;
    virtual void onUpdate( float dt ) = 0;
    virtual void onInit( void ) = 0;
    virtual void onRelease( void ) = 0;

    inline ChsNode * getRoot( void );
  private:
    boost::scoped_ptr<ChsRenderNode> root;
  };

  //------------------------------------------------------------------------------------------------
  inline ChsNode * ChsScene::getRoot( void ){
    return this->root.get();
  }
  //------------------------------------------------------------------------------------------------
}

#endif//_CHS_SCENE_H
