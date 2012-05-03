#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsModelManager.h"
#include "ChsModelLoader.h"
#include "ChsModel.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsModel> ChsModelManager::getModel( std::string name ){
		boost::shared_ptr<ChsModel> model = this->getFromCache( name );
		if( !model ){
			//load from file
			ChsModelLoader loader;
			model.reset( loader.load( name.c_str() ) );
			if( model )
				insert( this->cache )( name, model );
		}
		return model;
	}
	
  //------------------------------------------------------------------------------------------------
  
}
