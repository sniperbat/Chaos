#ifndef _CHS_ENTITY_H
#define _CHS_ENTITY_H
//--------------------------------------------------------------------------------------------------
#include "ChsRenderNode.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	class ChsRenderSystem;
	class ChsModel;	
  
	//------------------------------------------------------------------------------------------------
	class ChsEntity : public ChsRenderNode {
	private:
		void update( double timeInterval );
	public:
		ChsEntity( const std::string & name );
		virtual ~ChsEntity( void );
		
		std::weak_ptr<ChsModel> model;
		inline void setModel( const std::shared_ptr<ChsModel> & model );
		
	};
  
	//------------------------------------------------------------------------------------------------
	inline void ChsEntity::setModel( const std::shared_ptr<ChsModel> & model ){
		this->model = model;
	}
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_ENTITY_H
