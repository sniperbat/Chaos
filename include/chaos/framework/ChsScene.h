#ifndef _CHS_SCENE_H
#define _CHS_SCENE_H

#include <string>
#include "ChsRenderNode.h"

namespace Chaos {
  //------------------------------------------------------------------------------------------------  
  class ChsScene : public ChsRenderNode{
    friend class ChsSceneManager;
  public:
    ChsScene( void );
    virtual ~ChsScene( void ){};

    virtual void onInit( void ) = 0;
    virtual void onEnter( void ) = 0;
    virtual void onUpdate( double timeInterval ) = 0;
    virtual void onExit( void ) = 0;
    virtual void onRelease( void ) = 0;

  private:
    void update( double timeInterval );

  };
  
  //------------------------------------------------------------------------------------------------  
  
}

#endif//_CHS_SCENE_H
