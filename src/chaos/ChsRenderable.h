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
	protected:
    ChsMatrix  renderTransform;
    
		virtual void update( void )=0;
    void sendToRender( ChsRenderTag tag, ChsRenderUnit & unit );
    
	private:
		bool visible;

	};
 
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
