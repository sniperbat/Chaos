#ifndef _CHS_TEXTURE2D_H
#define _CHS_TEXTURE2D_H

#include <string>
#include "platform/ChsOpenGL.h"
#include "ChsDefine.h"

namespace Chaos {

  struct ChsTexWrap{
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

    inline GLint getWrap( ChsTexWrapType st )const;
    inline void setWrap( ChsTexWrapType st, GLint value );
    
	private:
    GLuint textureHandle;
    GLuint width;
    GLuint height;
		GLenum format;
		GLenum type;
		std::string name;
		boolean hasAlpha;
    
    ChsTexWrap wraps[CHS_TEXTURE_WRAP_MAX];
    void updateWrap( void );
	};
	
  //------------------------------------------------------------------------------------------------
  GLint ChsTexture2D::getWrap( ChsTexWrapType st )const{
    return this->wraps[st].value;
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsTexture2D::setWrap( ChsTexWrapType st, GLint value ){
    this->wraps[st].value = value;
    this->wraps[st].needUpdate = true;
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
