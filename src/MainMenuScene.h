#ifndef _MAINMENUSCENE_H
#define _MAINMENUSCENE_H
//--------------------------------------------------------------------------------------------------
#include "chaos/framework/ChsScene.h"
#include "chaos/core/ChsDynamicClass.h"

//--------------------------------------------------------------------------------------------------v
class MainMenuScene : public Chaos::ChsDynamicClass< MainMenuScene, Chaos::ChsScene >{
public:
  MainMenuScene( void );
  ~MainMenuScene( void );
  void onEnter( void );
  void onExit( void );
  void onUpdate( float dt );
  void onInit( void );
  void onRelease( void );
};

//--------------------------------------------------------------------------------------------------
#endif
