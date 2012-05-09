#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsModel.h"
#include "ChsMesh.h"
#include "ChsRenderSystem.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	ChsModel::ChsModel( std::string name ): ChsRenderNode( name ){
	}

	//------------------------------------------------------------------------------------------------
	ChsModel::~ChsModel( void ){
		this->meshs.clear();
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsModel::update( void ) {
		BOOST_FOREACH( boost::shared_ptr<ChsMesh> & mesh, this->meshs )
			if( mesh )
				mesh->update();
	}

	//------------------------------------------------------------------------------------------------
	void ChsModel::addMesh( boost::shared_ptr<ChsMesh> mesh ){
		if( mesh )
			this->meshs += mesh;
	}
	
  //------------------------------------------------------------------------------------------------
  
}//namespace
