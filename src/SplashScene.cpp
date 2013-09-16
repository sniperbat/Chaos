#include "chaos/framework/ChsSceneManager.h"
#include "chaos/ChsSprite2D.h"
#include "SplashScene.h"
#include "chaos/ChsEngine.h"
#include "chaos/ChsRenderSystem.h"
//--------------------------------------------------------------------------------------------------
//must do this, any other solutions??
static bool isDynamic = SplashScene::registerAsDynamic( "SplashScene" );

static const float FADE_SPEED = 0.05f;
static const int SPLASH_TIME = 2.0f;
static float splashAlpha = 0.0f;
static float showTime = 0.0f;

static Chaos::ChsSprite2D * splashImage = nullptr;

enum STEP{
  FADE_IN,
  SPLASH_SHOWING,
  FADE_OUT,
  GOTO_NEXT,
  IDLE
}step;

SplashScene::SplashScene( void ){
}

SplashScene::~SplashScene( void ){
  this->onRelease();
}

void SplashScene::onInit( void ){
  //load splash image
  splashImage = new Chaos::ChsSprite2D( "splash" );
  splashImage->setImage( "splash.png" );
  //splashImage->moveTo( 0, 0 );
  //  Chaos::ChsRenderSystem * render = Chaos::ChsEngine::sharedInstance()->getRenderSystem();
  //  Chaos::ChsRect<int> rect = render->getViewport();
  //  splashImage->changeSizeTo( rect.w, rect.h );
  splashImage->setAlpha( splashAlpha );
}

void SplashScene::onEnter( void ){
  //start fade out
  this->add( splashImage );
  step = STEP::FADE_IN;
}

void SplashScene::onUpdate( double timeInterval ){
  //process fade in and out
  switch( step ){
		case STEP::FADE_IN:
			splashAlpha += FADE_SPEED;
			if( splashAlpha >= 1.0f ) {
				step = STEP::SPLASH_SHOWING;
				splashAlpha = 1.0f;
			}
			splashImage->setAlpha( splashAlpha );
			break;
		case STEP::SPLASH_SHOWING:
      showTime += timeInterval;
      if( showTime >= SPLASH_TIME )
        step = STEP::FADE_OUT;
			break;
		case STEP::FADE_OUT:
			splashAlpha -= FADE_SPEED;
			if( splashAlpha <= 0.0f) {
				splashAlpha = 0.0f;
				step = STEP::GOTO_NEXT;
			}
			splashImage->setAlpha( splashAlpha );
			break;
		case STEP::GOTO_NEXT:
			Chaos::ChsSceneManager::sharedInstance()->gotoScene( "MainMenuScene", true );
      step = STEP::IDLE;
			break;
		case STEP::IDLE:
			break;
  }
}

void SplashScene::onExit( void ){
  this->remove( splashImage );
}

void SplashScene::onRelease( void ){
  //release splash image
  if(splashImage){
    delete splashImage;
    splashImage = nullptr;
  }
}

