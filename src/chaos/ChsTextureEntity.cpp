#include "ChsTextureEntity.h"
#include "ChsTexture2D.h"

namespace Chaos {
  
  ChsTextureEntity::ChsTextureEntity( boost::shared_ptr<ChsTexture2D> texture ){
    this->texture = texture;
    for( ChsTexParameterType type = CHS_TEXPARAM_WRAP_T; type < CHS_TEXPARAM_MAX; type++ ){
      this->parameters[type] = this->texture->getParameter( type );
    }
  }
  
  void ChsTextureEntity::apply( void ){
    for( ChsTexParameterType type = CHS_TEXPARAM_WRAP_T; type < CHS_TEXPARAM_MAX; type++ ){
      if( this->texture->getParameter( type ) != this->parameters[type]){
        this->texture->setParameter( type, this->parameters[type] );
      }
    }
    this->texture->bindToUnit( this->activeUnit );
  }
  
}
