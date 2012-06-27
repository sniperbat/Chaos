#ifndef _CHS_RENDERSTATES_H
#define _CHS_RENDERSTATES_H
//--------------------------------------------------------------------------------------------------
#include "ChsDefine.h"
#include "core/ChsSingleton.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	class ChsRenderStates : public ChsSingleton<ChsRenderStates> {
	public:
		void queryCurrentStates( void );
		void set( ChsRenderState state, unsigned int value );
    void save( void );
    void restore( void );
    void save( ChsRenderState state );
    void restore( ChsRenderState state );

	private:
		unsigned int states[CHS_RS_MAX];
    unsigned int statesBackup[CHS_RS_MAX];
	};

  //--------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_RENDERSTATES_H
