#ifndef _CHS_RENDERABLE_H
#define _CHS_RENDERABLE_H
//--------------------------------------------------------------------------------------------------
#include "math/ChsMatrix.h"
#include "ChsRenderSystem.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	class ChsRenderable {
  public:
    inline bool isVisible( void )const;
    inline void setVisible( bool visibel );
    inline void setRenderTag( ChsRenderTag tag );
	protected:
    ChsMatrix  renderTransform;
    
		virtual void update( float dt )=0;
    void sendToRender( ChsRenderUnit & unit );
	private:
		bool visible;
    ChsRenderTag renderTag;
	};
 
  inline void ChsRenderable::setRenderTag( ChsRenderTag tag ){
    this->renderTag = tag;
  }
  //------------------------------------------------------------------------------------------------
	inline bool ChsRenderable::isVisible( void )const{
    return this->visible;
  }
  //------------------------------------------------------------------------------------------------
  inline void ChsRenderable::setVisible( bool visible ){
    this->visible = visible;
  }
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif
