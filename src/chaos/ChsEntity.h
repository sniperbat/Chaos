#ifndef _CHS_ENTITY_H
#define _CHS_ENTITY_H
//--------------------------------------------------------------------------------------------------
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "ChsRenderNode.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	class ChsRenderSystem;
	class ChsModel;	
  
	//------------------------------------------------------------------------------------------------
	class ChsEntity : public ChsRenderNode {
	private:
		void update( void );
	public:
		ChsEntity( const std::string & name );
		virtual ~ChsEntity( void );
		
		boost::weak_ptr<ChsModel> model;
		inline void setModel( const boost::shared_ptr<ChsModel> & model );
		
	};
  
	//------------------------------------------------------------------------------------------------
	inline void ChsEntity::setModel( const boost::shared_ptr<ChsModel> & model ){
		this->model = model;
	}
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_ENTITY_H
