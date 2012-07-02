#ifndef _SPLASHSCENE_H
#define _SPLASHSCENE_H

#include "chaos/framework/ChsScene.h"
#include "chaos/core/ChsDynamicClass.h"

class SplashScene : public Chaos::ChsDynamicClass< SplashScene, Chaos::ChsScene >{
public:
  SplashScene( void );
  ~SplashScene( void );
  void onEnter( void );
  void onExit( void );
  void onUpdate( double timeInterval );
  void onInit( void );
  void onRelease( void );
};

#endif//_SPLASHSCENE_H
