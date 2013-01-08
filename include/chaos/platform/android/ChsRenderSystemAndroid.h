#ifndef _CHS_RENDERSYSTEMANDROID_H
#define _CHS_RENDERSYSTEMANDROID_H

#include "ChsRenderSystem.h"

namespace Chaos {
	
	class ChsRenderSystemAndroid final : public ChsRenderSystem {
	public:
		void initContext( void ) override;
	};
}

#endif//_CHS_RENDERSYSTEMANDROID_H
