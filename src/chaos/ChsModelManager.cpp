#include <boost/assign.hpp>
using namespace boost::assign;
#include "ChsModelManager.h"
#include "ChsModelLoader.h"
#include "ChsModel.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	boost::shared_ptr<ChsModel> ChsModelManager::getModel( const std::string & name ){
		boost::shared_ptr<ChsModel> model = this->getFromCache( name );
		if( !model ){
			//load from file
			ChsModelLoader loader;
      std::string fullpath = "assets/" + name;
			model.reset( loader.load( fullpath.c_str() ) );
			if( model ){
        printf( "载入模型:%s\n", fullpath.c_str() );
				insert( this->cache )( name, model );
      }
		}
		return model;
	}
	
  //------------------------------------------------------------------------------------------------
  
}
