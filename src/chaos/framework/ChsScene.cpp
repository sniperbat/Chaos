#include "ChsScene.h"

namespace Chaos{
  //------------------------------------------------------------------------------------------------
  ChsScene::ChsScene( void ){
  }

  //------------------------------------------------------------------------------------------------
  void ChsScene::update( double timeInterval ){
    this->onUpdate( timeInterval );
  }

}
