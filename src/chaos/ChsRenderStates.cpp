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
	
  GLenum glBlendFactors[]={
    GL_ZERO,
    GL_ONE,
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA_SATURATE,
  };
  
  //------------------------------------------------------------------------------------------------
	void ChsRenderStates::set( ChsRenderStateId id, const ChsRenderState state ){
    do{
      if( id >=0 && id < CHS_RS_ENABLECAP ){
        if( this->states[ id ].value == state.value )
          break;
        this->states[id ].value = state.value;
        if( state.value )
          glEnable( glStates[ id ] );
        else
          glDisable( glStates[ id ] );
      }
      switch ( id ) {
        case CHS_RS_BLEND_FUNC:
          glBlendFunc( glBlendFactors[ state.value2.v1 ], glBlendFactors[ state.value2.v2 ] );
          break;
        default:
          break;
      }
    }while(0);
	}
  
  //------------------------------------------------------------------------------------------------
	void ChsRenderStates::queryCurrentStates( void ){
		for( int i = CHS_RS_TEXTURE_2D; i < CHS_RS_MAX; i++ ) {
			if( i <= CHS_RS_ENABLECAP){
        this->states[i].value = glIsEnabled( glStates[i] ) ? CHS_RS_ENABLE : CHS_RS_DISABLE;
			}
		}
	}
	
  //------------------------------------------------------------------------------------------------
  void ChsRenderStates::save( void ){
    memcpy( this->statesBackup, this->states, sizeof( this->statesBackup ) );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsRenderStates::restore( void ){
    memcpy( this->states, this->statesBackup, sizeof( this->statesBackup ) );
  }

  //------------------------------------------------------------------------------------------------
  void ChsRenderStates::save( ChsRenderStateId id ){
    this->statesBackup[id] = this->states[id];
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsRenderStates::restore( ChsRenderStateId id ){
    this->states[id] = this->statesBackup[id];
  }

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
