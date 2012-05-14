#ifndef _CHS_HUD_H
#define _CHS_HUD_H

#include "ChsRenderNode.h"

namespace Chaos {
  
  class ChsHUD : public ChsRenderNode{
  public:
    ChsHUD( std::string name );
    void update( void );
  };

}


#endif//_CHS_HUD_H
