#ifndef _CHS_TEXTURE2D_H
#define _CHS_TEXTURE2D_H

#include <string>
#include "platform/ChsOpenGL.h"

namespace Chaos {
	//------------------------------------------------------------------------------------------------
	class ChsTexture2D {
		friend class ChsTextureFactory;
	public:
		ChsTexture2D( void );
		~ChsTexture2D( void );
		void build( GLuint width, GLuint height, GLenum format, GLubyte * data );
		void bind( void )const;
  
    inline const std::string & getName( void )const;
    
    inline GLuint getHandle( void )const;
    
    inline boolean hasAlphaChannel( void )const;
    
    inline GLint getActiveUnit( void )const;
    inline void setActiveUnit( GLint unit );
    
    inline const std::string & getSampleName( void )const;
    inline void setSampleName( const std::string & sampleName );

    inline unsigned int getWidth( void )const;
    inline unsigned int getHeight( void )const;

	private:
    GLuint textureHandle;
    GLuint width;
    GLuint height;
		GLenum format;
		GLenum type;
		std::string name;
		boolean hasAlpha;
		GLint activeUnit;
		std::string sampleName;
	};
	
	//------------------------------------------------------------------------------------------------
	inline GLuint ChsTexture2D::getHandle( void )const{
    return this->textureHandle;
  }
  
  //------------------------------------------------------------------------------------------------
	inline const std::string & ChsTexture2D::getName( void )const{
    return this->name;
  }
  
  //------------------------------------------------------------------------------------------------
	inline boolean ChsTexture2D::hasAlphaChannel( void )const{
    return this->hasAlpha;
  }
  
  //------------------------------------------------------------------------------------------------
	inline GLint ChsTexture2D::getActiveUnit( void )const{
    return this->activeUnit;
  }
  
  //------------------------------------------------------------------------------------------------
  inline void ChsTexture2D::setActiveUnit( GLint unit ){
    this->activeUnit = unit;
  }
  
  //------------------------------------------------------------------------------------------------
  inline const std::string & ChsTexture2D::getSampleName( void )const{
    return this->sampleName;
  }
	
	//------------------------------------------------------------------------------------------------
  inline void ChsTexture2D::setSampleName( const std::string & sampleName ){
    this->sampleName = sampleName;
  }

  //------------------------------------------------------------------------------------------------
  inline unsigned int ChsTexture2D::getWidth( void )const{
    return this->width;
  }

  //------------------------------------------------------------------------------------------------
  inline unsigned int ChsTexture2D::getHeight( void )const{
    return this->height;
  }

}


#endif//_CHS_TEXTURE2D_H
