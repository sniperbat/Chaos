#ifndef _CHS_ENGINE_H
#define _CHS_ENGINE_H

#include <boost/noncopyable.hpp>
#include "ChsSingleton.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	class ChsRenderSystem;
	class ChsGameBase;
	
  //------------------------------------------------------------------------------------------------
	class ChsEngine : public ChsSingleton<ChsEngine>, boost::noncopyable {
	public:
		ChsEngine();
		~ChsEngine();
		
		void start( void );
		void run( void )const;
		void shutdown( void );
    
    inline ChsRenderSystem * getRenderSystem( void )const;
    
    inline ChsGameBase * getGame( void )const;
    inline void setGame( ChsGameBase * game );
    
  private:
    ChsRenderSystem * renderSystem;
    ChsGameBase * game;
	};

  //------------------------------------------------------------------------------------------------
	inline ChsRenderSystem * ChsEngine::getRenderSystem( void )const{
    return this->renderSystem;
  }
  
  //------------------------------------------------------------------------------------------------
  inline ChsGameBase * ChsEngine::getGame( void )const{
    return this->game;
  }
  
  //------------------------------------------------------------------------------------------------
  inline void ChsEngine::setGame( ChsGameBase * game ){
    this->game = game;
  }

}

#endif//_CHS_ENGINE_H
