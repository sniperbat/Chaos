#ifndef _CHS_TEXTUREENTITY_H
#define _CHS_TEXTUREENTITY_H

#include <boost/shared_ptr.hpp>
#include <string>
#include "ChsDefine.h"

namespace Chaos {

  class ChsTexture2D;
  
  class ChsTextureEntity {
  private:
    boost::shared_ptr<ChsTexture2D> texture;
		int activeUnit;
		std::string sampleName;
    int parameters[CHS_TEXPARAM_MAX];
  public:
    ChsTextureEntity( boost::shared_ptr<ChsTexture2D> texture );
    inline int getActiveUnit( void )const;
    inline void setActiveUnit( int unit );
    
    inline const std::string & getSampleName( void )const;
    inline void setSampleName( const std::string & sampleName );

    inline const boost::shared_ptr<ChsTexture2D> & instance( void )const;
    void apply( void );
    
    inline void setParameter( ChsTexParameterType type, int value );
  };

  //------------------------------------------------------------------------------------------------
  inline void ChsTextureEntity::setParameter( ChsTexParameterType type, int value ){
    this->parameters[type] = value;
  }
  //------------------------------------------------------------------------------------------------
  inline const boost::shared_ptr<ChsTexture2D> & ChsTextureEntity::instance( void )const{
    return this->texture;
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
