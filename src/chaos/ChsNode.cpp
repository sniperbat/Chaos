#include "ChsNode.h"
#include <boost/assign.hpp>
using namespace boost::assign;

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsNode::ChsNode( const std::string & name ){
    this->name = name;
		this->children.clear();
	}
	
  //------------------------------------------------------------------------------------------------
	ChsNode::~ChsNode( void ){
		this->children.clear();
	}

	//------------------------------------------------------------------------------------------------
	void ChsNode::add( const std::string & name, ChsNode * node ){
    if( node ){
      if( this->children.find( name ) == this->children.end() )
        insert( this->children )( name, node );
    }
	}
	
	//------------------------------------------------------------------------------------------------
	ChsNode * ChsNode::remove( const std::string & name ){
		ChsNode * node = this->get( name );
		if( node != NULL )
			this->children.erase( name );
		return node;
	}
	
	//------------------------------------------------------------------------------------------------
	ChsNode * ChsNode::get( const std::string & name ){
		auto iter = this->children.find( name );
		return  ( iter == this->children.end() ) ? NULL : iter->second;
	}

}
