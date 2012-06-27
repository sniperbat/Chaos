#include "ChsEngine.h"
#include "ChsResourceManager.h"
#include "ChsRenderStates.h"
#include "hud/ChsHUDManager.h"
#include "framework/ChsSceneManager.h"
#include "io/ChsTouchEmitter.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
	static ChsEngine gEngine;
	static ChsResourceManager gResourceManager;
	static ChsRenderStates gRenderStates;
  static ChsHUDManager gHudManager;
  static ChsSceneManager gSceneManager;
  static ChsTouchEmitter gTouchEmitter;
}

//------------------------------------------------------------------------------------------------
