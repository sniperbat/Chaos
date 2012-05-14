#include "ChsSceneManager.h"
#include "ChsNode.h"
#include "ChsRenderNode.h"

namespace Chaos{
  class ChsSceneRoot : public ChsRenderNode{
  public:
    ChsSceneRoot( void ) : ChsRenderNode( "root" ){}
    void update( void ){}
  };
  
  ChsSceneManager::ChsSceneManager( void ) : root( new ChsSceneRoot() ){
  }
  
  ChsSceneManager::~ChsSceneManager( void ){
  }
  
  void ChsSceneManager::update( void ){
    root->updateTree();
  }
 
  void ChsSceneManager::purge( void ){
    
  }
  
  ChsNode * ChsSceneManager::getRoot( void )const{
    return this->root.get();
  }
  
}
