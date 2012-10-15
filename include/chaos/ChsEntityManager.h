#ifndef _CHS_ENTITYMANAGER_H
#define _CHS_ENTITYMANAGER_H
//--------------------------------------------------------------------------------------------------
#include "ChsManagerWithCache.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
	class ChsEntity;

  //------------------------------------------------------------------------------------------------
	class ChsEntityManager : public ChsManagerWithCache< ChsEntity > {
	public:
		boost::shared_ptr<ChsEntity> getEntity( const std::string & entityName );
		
		boost::shared_ptr<ChsEntity> getEntityWithModel( const std::string & entityName,
                                                     const std::string & modelName );
		
		boost::shared_ptr<ChsEntity> getEntityWithModelAndAnimation( const std::string & entityName, 
                                                                 const std::string & modelName,
                                                                 const std::string & animationName );
	};
	
  //------------------------------------------------------------------------------------------------
	
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_ENTITYMANAGER_H
