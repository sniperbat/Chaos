#ifndef _CHS_RENDERNODE_H
#define _CHS_RENDERNODE_H

#include "ChsNode.h"
#include "ChsRenderable.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{
  
  //------------------------------------------------------------------------------------------------
	class ChsRenderSystem;

  //------------------------------------------------------------------------------------------------
	class ChsRenderNode : public ChsNode, public ChsRenderable{
	public:
		ChsRenderNode( const std::string & name = "unnamed" );
		virtual ~ChsRenderNode( void );
    void updateTree( void );
	};
  
	
  //------------------------------------------------------------------------------------------------
  
}//namespace

#endif //_CHS_RENDERNODE_H
