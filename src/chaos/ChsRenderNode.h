#ifndef _CHS_RENDERNODE_H
#define _CHS_RENDERNODE_H
//--------------------------------------------------------------------------------------------------
#include "core/ChsNode.h"
#include "ChsRenderable.h"
#include "math/ChsMatrix.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos{
  
  //------------------------------------------------------------------------------------------------
	class ChsRenderSystem;

  //------------------------------------------------------------------------------------------------
	class ChsRenderNode : public ChsNode, public ChsRenderable{
	public:
		ChsRenderNode( const std::string & name = "unnamed" );
		virtual ~ChsRenderNode( void );
    void updateTree( float dt );

    inline void applyTransform( const ChsMatrix & matrix );
    inline void applyTransform( const ChsMatrix * matrix );
    //return a copy
    ChsMatrix getTransform( void );
    
  private:
    ChsMatrix transform;
	};

  //------------------------------------------------------------------------------------------------
  inline void ChsRenderNode::applyTransform( const ChsMatrix & matrix ){
    this->transform = matrix;
  }
  
  //------------------------------------------------------------------------------------------------
  inline void ChsRenderNode::applyTransform( const ChsMatrix * matrix ){
    this->transform = *matrix;
  }

  //------------------------------------------------------------------------------------------------
  inline ChsMatrix ChsRenderNode::getTransform( void ){
    return this->transform;
  }
	
  //------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHS_RENDERNODE_H
