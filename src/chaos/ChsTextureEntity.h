#ifndef _CHS_TEXTUREENTITY_H
#define _CHS_TEXTUREENTITY_H

#include "ChsDefine.h"

namespace Chaos {

  class ChsTexture2D;
  
  class ChsTextureEntity {
  private:
    boost::weak_ptr<ChsTexture2D> texture;
		int activeUnit;
		std::string sampleName;
    int wraps[CHS_TEXTURE_WRAP_MAX];
  public:
    ChsTextureEntity( const boost::shared_ptr<ChsTexture2D> & texture );
    inline int getActiveUnit( void )const;
    inline void setActiveUnit( int unit );
    
    inline const std::string & getSampleName( void )const;
    inline void setSampleName( const std::string & sampleName );

    void apply( void )const;
    
    inline void setWrap( ChsTexWrapType type, int value );
    
    int getWidth( void )const;
    int getHeight( void )const;
    
  };

  //------------------------------------------------------------------------------------------------
  inline void ChsTextureEntity::setWrap( ChsTexWrapType type, int value ){
    this->wraps[type] = value;
  }

  //------------------------------------------------------------------------------------------------
  inline void ChsTextureEntity::setActiveUnit( int unit ){
    this->activeUnit = unit;
  }
 
  //------------------------------------------------------------------------------------------------
  inline int ChsTextureEntity::getActiveUnit( void )const{
    return this->activeUnit;
  }

  //------------------------------------------------------------------------------------------------
  inline const std::string & ChsTextureEntity::getSampleName( void )const{
    return this->sampleName;
  }

  //------------------------------------------------------------------------------------------------
  inline void ChsTextureEntity::setSampleName( const std::string & sampleName ){
    this->sampleName = sampleName;
  }

}

#endif//_CHS_TEXTUREENTITY_H
