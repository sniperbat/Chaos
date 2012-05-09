#include "ChsTextureEntity.h"
#include "ChsTexture2D.h"

namespace Chaos {
  
  ChsTextureEntity::ChsTextureEntity( boost::shared_ptr<ChsTexture2D> texture ){
    this->texture = texture;
  }
  
  void ChsTextureEntity::apply( void ){
    this->texture->bindToUnit( this->activeUnit );
  }
  
}
