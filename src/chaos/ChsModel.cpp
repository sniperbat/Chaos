#include <boost/foreach.hpp>
#include "ChsModel.h"
#include "ChsMesh.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	ChsModel::ChsModel( const std::string & name ): ChsRenderNode( name ){
	}

	//------------------------------------------------------------------------------------------------
	ChsModel::~ChsModel( void ){
		this->meshs.clear();
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsModel::update( double timeInterval ) {
		BOOST_FOREACH( boost::shared_ptr<ChsMesh> & mesh, this->meshs ){
			if( mesh ){
				mesh->updateTree( timeInterval );
      }
    }
	}

	//------------------------------------------------------------------------------------------------
	void ChsModel::addMesh( const boost::shared_ptr<ChsMesh> & mesh ){
		if( mesh ){
			this->meshs.push_back( mesh );
    }
	}
	
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
