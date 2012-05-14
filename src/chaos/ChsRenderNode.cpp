#include "ChsRenderNode.h"
#include "ChsUtility.h"
#include "math/ChsMatrix.h"
#include <boost/foreach.hpp>

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
  void ChsRenderNode::updateTree( void ){
    if( !this->isVisible() )
			return;//if this node is invisible,then all chilren are invisible too
		this->update();
		std::pair<std::string, ChsNode *> p;
		BOOST_FOREACH( p, this->children )
    ( ( ChsRenderNode * )p.second )->updateTree();
  }

  //------------------------------------------------------------------------------------------------
  
}
