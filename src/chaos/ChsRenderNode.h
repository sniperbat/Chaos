#ifndef _CHS_RENDERNODE_H
#define _CHS_RENDERNODE_H
#pragma once

#include "ChsNode.h"
#include "ChsRenderable.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos{
  
  //------------------------------------------------------------------------------------------------
	class ChsRenderSystem;

  //------------------------------------------------------------------------------------------------
	class ChsRenderNode : public ChsNode, ChsRenderable{
	public:
		ChsRenderNode( std::string name = "unnamed" );
		virtual ~ChsRenderNode( void );

		void renderNodes( ChsRenderSystem * render );
		inline bool isVisible( void )const;
    inline void setVisible( bool visibel );
	private:
		bool visible;
		
	};
  
	//------------------------------------------------------------------------------------------------
	inline bool ChsRenderNode::isVisible( void )const{
    return this->visible;
  }
  //------------------------------------------------------------------------------------------------
  inline void ChsRenderNode::setVisible( bool visible ){
    this->visible = visible;
  }
  
  //------------------------------------------------------------------------------------------------
  
}//namespace

#endif //_CHS_RENDERNODE_H
