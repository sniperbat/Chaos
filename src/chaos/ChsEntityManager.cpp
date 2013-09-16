#include "ChsEntityManager.h"
#include "ChsEntity.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	std::shared_ptr<ChsEntity> ChsEntityManager::getEntity( const std::string & entityName ){
		std::shared_ptr<ChsEntity> entityPtr = this->getFromCache( entityName );
		if( !entityPtr ){
			entityPtr = std::shared_ptr<ChsEntity>( new ChsEntity( entityName ) );
			printf( "生成Entity:%s\n", entityName.c_str() );
			this->cache.insert( std::make_pair( entityName, entityPtr ) );
		}
		return entityPtr;
	}
  
#if 0
  //------------------------------------------------------------------------------------------------
	std::shared_ptr<ChsEntity> ChsEntityManager::getEntityWithModel( const std::string & entityName,
                                                                     const std::string &  modelName ){
		if( entityName.empty() )
			return nullptr;
		ChsEntity * entity = this->getEntity( entityName );
		//TODO: set model
		return entity;
	}


	//------------------------------------------------------------------------------------------------
	std::shared_ptr<ChsEntity> ChsEntityManager::getEntityWithModelAndAnimation( const std::string & entityName,
                                                                                 const std::string &  modelName,
                                                                                 const std::string &  animationName ){
		if( entityName.empty() )
			return nullptr;
		ChsEntity * entity = this->getEntityWithModel( entityName, modelName );
		//TODO: set animation
		return entity;
	}
#endif
  
	//------------------------------------------------------------------------------------------------
	
}//namespace

//--------------------------------------------------------------------------------------------------
