#include <boost/assign.hpp>
using namespace boost::assign;
#include "ChsRenderable.h"

namespace Chaos {
  
  extern ChsRenderChain renderChains[CHS_RENDER_TAG_MAX];
  
  void ChsRenderable::sendToRender( ChsRenderTag tag, ChsRenderUnit unit ){
    renderChains[tag] += unit;
  }
  
}
