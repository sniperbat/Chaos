#include "ChsTextureEntity.h"
#include "ChsTexture2D.h"

namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  ChsTextureEntity::ChsTextureEntity( boost::shared_ptr<ChsTexture2D> texture ){
    this->texture = texture;
    for( ChsTexParameterType type = CHS_TEXPARAM_WRAP_T; type < CHS_TEXPARAM_MAX; type++ ){
      this->parameters[type] = texture->getParameter( type );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTextureEntity::apply( void )const{
    if( this->texture.expired() )
      return;
    boost::shared_ptr<ChsTexture2D> texture = this->texture.lock();
    for( ChsTexParameterType type = CHS_TEXPARAM_WRAP_T; type < CHS_TEXPARAM_MAX; type++ ){
      if( texture->getParameter( type ) != this->parameters[type]){
        texture->setParameter( type, this->parameters[type] );
      }
    }
    texture->bindToUnit( this->activeUnit );
  }
  
  //------------------------------------------------------------------------------------------------
  int ChsTextureEntity::getWidth( void )const{
    if( this->texture.expired() )
      return 0;
    return this->texture.lock()->getWidth();
  }
  //------------------------------------------------------------------------------------------------
  int ChsTextureEntity::getHeight( void )const{
    if( this->texture.expired() )
      return 0;
    return this->texture.lock()->getHeight();
  }
  

}
