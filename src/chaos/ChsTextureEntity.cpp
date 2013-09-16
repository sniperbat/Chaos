#include "ChsTextureEntity.h"
#include "ChsTexture2D.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  ChsTextureEntity::ChsTextureEntity( const std::shared_ptr<ChsTexture2D> & texture ){
    if( texture ){
      this->texture = texture;
      for( int index = 0; index < CHS_TEXTURE_WRAP_MAX; index++ ){
        ChsTexWrapType type = static_cast<ChsTexWrapType>( index );
        this->wraps[index] = texture->getWrap( type );
      }
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTextureEntity::apply( void )const{
    if( !this->texture.expired() ){
      const std::shared_ptr<ChsTexture2D> & texture = this->texture.lock();
      for( int index = 0; index < CHS_TEXTURE_WRAP_MAX; index++ ){
        ChsTexWrapType type = static_cast<ChsTexWrapType>( index );
        if( texture->getWrap( type ) != this->wraps[index]){
          texture->setWrap( type, this->wraps[index] );
        }
      }
      texture->bindToUnit( this->activeUnit );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  int ChsTextureEntity::getWidth( void )const{
    int width = 0;
    if( !this->texture.expired() )
      width =this->texture.lock()->getWidth();
    return width;
  }
  
  //------------------------------------------------------------------------------------------------
  int ChsTextureEntity::getHeight( void )const{
    int height = 0;
    if( !this->texture.expired() )
      height = this->texture.lock()->getHeight();
    return height;
  }

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
