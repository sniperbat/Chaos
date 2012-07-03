#include <memory.h>
#include "ChsRenderStates.h"
#include "platform/ChsOpenGL.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	GLenum glStates[]={
		GL_TEXTURE_2D,
		GL_CULL_FACE,
		GL_BLEND,
		GL_DITHER,
		GL_STENCIL_TEST,
		GL_DEPTH_TEST,
		GL_SCISSOR_TEST,
		GL_POLYGON_OFFSET_FILL,
		GL_SAMPLE_ALPHA_TO_COVERAGE,
		GL_SAMPLE_COVERAGE,
	};
	
  //------------------------------------------------------------------------------------------------
	void setEnableOrDisable( ChsRenderState index, unsigned int value );
	void setEnableOrDisable( ChsRenderState index, unsigned int value ){
		if( value )
			glEnable( glStates[index] );
		else
			glDisable( glStates[index] );
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderStates::set( ChsRenderState index, unsigned int value ){
    do{
      if( this->states[ index ] == value )
        break;
      this->states[ index ] = value;
      if( CHS_RS_ENABLECAP < index )
        break;
      setEnableOrDisable( index, value );
    }while(0);
	}
	
  //------------------------------------------------------------------------------------------------
	void ChsRenderStates::queryCurrentStates( void ){
		for( int i = CHS_RS_TEXTURE_2D; i < CHS_RS_MAX; i++ ) {
			if( i <= CHS_RS_ENABLECAP){
        this->states[i] = glIsEnabled( glStates[i] ) ? CHS_RS_ENABLE : CHS_RS_DISABLE;
			}
		}
	}
	
  //------------------------------------------------------------------------------------------------
  void ChsRenderStates::save( void ){
    memcpy( this->statesBackup, this->states, sizeof( this->statesBackup ) );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsRenderStates::restore( void ){
    for( int i = CHS_RS_TEXTURE_2D; i < CHS_RS_MAX; i++ ){
      this->set( static_cast<ChsRenderState>( i ), this->statesBackup[i] );
    }
  }

  //------------------------------------------------------------------------------------------------
  void ChsRenderStates::save( ChsRenderState state ){
    this->statesBackup[state] = this->states[state];
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsRenderStates::restore( ChsRenderState state ){
    this->set( state, this->statesBackup[state] );
  }

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
