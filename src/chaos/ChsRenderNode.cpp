#include "ChsRenderNode.h"
#include "core/ChsUtility.h"
#include "math/ChsMatrix.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	ChsRenderNode::ChsRenderNode( const std::string & name ) : ChsNode( name ) {
		this->setVisible( true );
	}

  //------------------------------------------------------------------------------------------------
	ChsRenderNode::~ChsRenderNode( void ){
	}

  //------------------------------------------------------------------------------------------------
  void ChsRenderNode::updateTree( double timeInterval ){
    if( this->isVisible() ){
      this->update( timeInterval );
      this->renderTransform =  this->transform;
      ChsRenderNode * parent = ( ChsRenderNode * )this->getParent();
      if( parent ){
        this->renderTransform =  parent->transform * this->renderTransform;
      }
      //std::pair<std::string, ChsNode *> p;
      for( auto & p : this->children ){
        ( ( ChsRenderNode * )p.second )->updateTree( timeInterval );
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
