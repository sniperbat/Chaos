#ifndef _CHSMODEL_H
#define _CHSMODEL_H
//--------------------------------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "ChsRenderNode.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	class ChsMesh;

	//------------------------------------------------------------------------------------------------
	class ChsModel : public ChsRenderNode {
    friend class ChsModelLoader;
	public:
		ChsModel( const std::string & name = "unnamed" );
		virtual ~ChsModel( void );
		void addMesh( const boost::shared_ptr<ChsMesh> & mesh );
    void update( void );
	private:
		std::vector< boost::shared_ptr<ChsMesh> > meshs;
	};

	//------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHSMODEL_H
