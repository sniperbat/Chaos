#include "ChsNode.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
	//------------------------------------------------------------------------------------------------
	ChsNode::ChsNode( const std::string & name ) : parent( nullptr ) {
    this->name = name;
		this->children.clear();
	}
	
  //------------------------------------------------------------------------------------------------
	ChsNode::~ChsNode( void ){
		this->children.clear();
	}

	//------------------------------------------------------------------------------------------------
	void ChsNode::add( const std::string & name, ChsNode * node ){
    if( node != nullptr && this->children.find( name ) == this->children.end() ){
      this->children.insert( std::make_pair( name, node ) );
      node->parent = this;
    }
	}
	
	//------------------------------------------------------------------------------------------------
	ChsNode * ChsNode::remove( const std::string & name ){
		ChsNode * node = this->get( name );
		if( node != nullptr ){
			this->children.erase( name );
      node->parent = nullptr;
    }
		return node;
	}
	
	//------------------------------------------------------------------------------------------------
	ChsNode * ChsNode::get( const std::string & name ){
		auto iter = this->children.find( name );
		return  ( iter == this->children.end() ) ? nullptr : iter->second;
	}

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
