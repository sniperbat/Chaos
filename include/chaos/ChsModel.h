#ifndef _CHSMODEL_H
#define _CHSMODEL_H
//--------------------------------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "ChsRenderNode.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  //------------------------------------------------------------------------------------------------
	class ChsModel : public ChsRenderNode {
    friend class ChsModelLoader;
	public:
		ChsModel( const std::string & name = "unnamed" );
		virtual ~ChsModel( void );
    void update( double timeInterval ) override;
	private:
	};

	//------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHSMODEL_H
