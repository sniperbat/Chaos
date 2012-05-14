#ifndef _CHS_TEXTURE2D_H
#define _CHS_TEXTURE2D_H

#include <string>
#include "platform/ChsOpenGL.h"
#include "ChsDefine.h"

namespace Chaos {

  struct ChsTexParameter{
    bool needUpdate;
    GLint value;
  };
	//------------------------------------------------------------------------------------------------
	class ChsTexture2D{
		friend class ChsTextureFactory;
	public:
		ChsTexture2D( void );
		~ChsTexture2D( void );
		void build( GLuint width, GLuint height, GLenum format, GLubyte * data );
		void bindToUnit( GLint unit );
  
    inline const std::string & getName( void )const;
    inline GLuint getHandle( void )const;
    inline boolean hasAlphaChannel( void )const;
    inline unsigned int getWidth( void )const;
    inline unsigned int getHeight( void )const;

    inline GLint getParameter( ChsTexParameterType type )const;
    inline void setParameter( ChsTexParameterType type, GLint value );
    
	private:
    GLuint textureHandle;
    GLuint width;
    GLuint height;
		GLenum format;
		GLenum type;
		std::string name;
		boolean hasAlpha;
    
    ChsTexParameter parameters[CHS_TEXPARAM_MAX];
    void updateParameters( void );
	};
	
  //------------------------------------------------------------------------------------------------
  inline GLint ChsTexture2D::getParameter( ChsTexParameterType type )const{
    return this->parameters[type].value;
  }

  //------------------------------------------------------------------------------------------------
  inline void ChsTexture2D::setParameter( ChsTexParameterType type, GLint value ){
    this->parameters[type].value = value;
    this->parameters[type].needUpdate = true;
  }
  
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
  inline unsigned int ChsTexture2D::getWidth( void )const{
    return this->width;
  }

  //------------------------------------------------------------------------------------------------
  inline unsigned int ChsTexture2D::getHeight( void )const{
    return this->height;
  }
}

#endif//_CHS_TEXTURE2D_H
