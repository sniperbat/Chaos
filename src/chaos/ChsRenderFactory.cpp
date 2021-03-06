#include "core/ChsUtility.h"
#include "ChsRenderFactory.h"
#include "ChsRenderSystem.h"


#if defined( CHS_PLATFORM_IOS )
	#include "ChsRenderSystemIOS.h"
#elif defined(CHS_PLATFORM_ANDROID)
	#include "platform/android/ChsRenderSystemAndroid.h"
#elif defined(CHS_PLATFORM_WINDOWS)
#include "platform/windows/ChsRenderSystemWindows.h"
#endif

//--------------------------------------------------------------------------------------------------
namespace Chaos{
	
	//------------------------------------------------------------------------------------------------
	static ChsRenderSystem * currentRender = nullptr;
	
	//------------------------------------------------------------------------------------------------
	ChsRenderSystem * ChsRenderFactory::create( void ) {
		ChsRenderFactory::shutdown();
		ChsRenderSystem * render = 
#if defined (CHS_PLATFORM_IOS)
				new ChsRenderSystemIOS();
#elif defined(CHS_PLATFORM_ANDROID)
				new ChsRenderSystemAndroid();
#elif defined(CHS_PLATFORM_WINDOWS)
        new ChsRenderSystemWindows();
#endif
		if( render ){
			render->init();
			currentRender = render;
		}
		return render;
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsRenderFactory::shutdown( void ){
		if( currentRender ){
			currentRender->shutdown();
			safeDelete( &currentRender, "delete current render" );
		}
	}
	
	//------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
