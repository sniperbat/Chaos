#ifndef _GAMINGSCENE_H
#define _GAMINGSCENE_H

#include "chaos/framework/ChsScene.h"
#include "chaos/core/ChsDynamicClass.h"

class GamingScene : public Chaos::ChsDynamicClass< GamingScene, Chaos::ChsScene >{
public:
  GamingScene( void );
  ~GamingScene( void );
  void onEnter( void );
  void onExit( void );
  void onUpdate( double timeInterval );
  void onInit( void );
  void onRelease( void );
};

#endif//_GAMINGSCENE_H
