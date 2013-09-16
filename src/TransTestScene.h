#ifndef Chaos_TransTestScene_h
#define Chaos_TransTestScene_h

#include "chaos/framework/ChsScene.h"
#include "chaos/core/ChsDynamicClass.h"

class TransTestScene: public Chaos::ChsDynamicClass< TransTestScene, Chaos::ChsScene >{
public:
  TransTestScene( void );
  ~TransTestScene( void );
  void onEnter( void );
  void onExit( void );
  void onUpdate( double timeInterval );
  void onInit( void );
  void onRelease( void );
};

#endif
