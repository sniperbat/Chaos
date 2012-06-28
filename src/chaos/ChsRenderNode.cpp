#include <boost/foreach.hpp>
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
  void ChsRenderNode::updateTree( float dt ){
    if( !this->isVisible() )
			return;//if this node is invisible,then all chilren are invisible too
		this->update( dt );
    this->renderTransform =  this->transform;
    ChsRenderNode * parent = ( ChsRenderNode * )this->getParent();
    if( parent )
      this->renderTransform =  parent->transform * this->renderTransform;
		std::pair<std::string, ChsNode *> p;
		BOOST_FOREACH( p, this->children )
      ( ( ChsRenderNode * )p.second )->updateTree( dt );
  }

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
