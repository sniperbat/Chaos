#include "ChsTextureEntity.h"
#include "ChsTexture2D.h"

namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  ChsTextureEntity::ChsTextureEntity( boost::shared_ptr<ChsTexture2D> texture ){
    if( texture ){
      this->texture = texture;
      for( int index = 0; index < CHS_TEXPARAM_MAX; index++ ){
        ChsTexParameterType type = static_cast<ChsTexParameterType>( index );
        this->parameters[index] = texture->getParameter( type );
      }
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTextureEntity::apply( void )const{
    if( this->texture.expired() )
      return;
    boost::shared_ptr<ChsTexture2D> texture = this->texture.lock();
    for( int index = 0; index < CHS_TEXPARAM_MAX; index++ ){
      ChsTexParameterType type = static_cast<ChsTexParameterType>( index );
      if( texture->getParameter( type ) != this->parameters[index]){
        texture->setParameter( type, this->parameters[index] );
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
