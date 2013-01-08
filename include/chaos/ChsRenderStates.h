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
		void set( ChsRenderStateId id, const ChsRenderState state );
    void save( void );
    void restore( void );
    void save( ChsRenderStateId id );
    void restore( ChsRenderStateId id );

	private:
		ChsRenderState states[CHS_RS_MAX];
    ChsRenderState statesBackup[CHS_RS_MAX];
	};

  //--------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_RENDERSTATES_H
