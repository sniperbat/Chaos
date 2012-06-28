#include "ChsScene.h"

namespace Chaos{
  
  //------------------------------------------------------------------------------------------------
  class ChsSceneRoot : public ChsRenderNode{
  public:
    ChsSceneRoot( void ) : ChsRenderNode( "root" ){}
    void update( void ){}
  };
  
  //------------------------------------------------------------------------------------------------
  ChsScene::ChsScene( void ) : root( new ChsSceneRoot() ){
  }

  //------------------------------------------------------------------------------------------------
  void ChsScene::update( float dt ){
    this->onUpdate( dt );
    this->root->updateTree();
  }

}
