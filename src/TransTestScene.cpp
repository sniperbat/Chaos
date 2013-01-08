#include "TransTestScene.h"
#include "chaos/framework/ChsSceneManager.h"
#include "chaos/ChsSprite2D.h"
#include "chaos/ChsEngine.h"
#include "chaos/ChsMaterial.h"
#include "chaos/ChsRenderSystem.h"
//--------------------------------------------------------------------------------------------------
//must do this, any other solutions??
static bool isDynamic = TransTestScene::registerAsDynamic( "TransTestScene" );

static Chaos::ChsSprite2D * backImage= nullptr;
static Chaos::ChsSprite2D * frontImage= nullptr;
static Chaos::ChsSprite2D * mask1Image= nullptr;
static Chaos::ChsSprite2D * mask2Image= nullptr;

TransTestScene::TransTestScene( void ){
}

TransTestScene::~TransTestScene( void ){
  this->onRelease();
}

static float imageAlpha = 0.0f;
void TransTestScene::onInit( void ){
  backImage = new Chaos::ChsSprite2D("background");
  backImage->setImage( "background.png" );
  backImage->setDepth( 1.0f );
  backImage->setAlpha( 1 );
  backImage->getMaterial()->setRenderState( Chaos::CHS_RS_BLEND_FUNC, { Chaos::CHS_BF_SRC_ALPHA, Chaos::CHS_BF_ONE_MINUS_SRC_ALPHA} );

  mask1Image = new Chaos::ChsSprite2D( "maks" );
  mask1Image->setImage( "mask.png" );
  mask1Image->setDepth( 2.0f );
  mask1Image->setAlpha( 1 );
    //  mask1Image->moveTo( 100, 100 );
  mask1Image->getMaterial()->setRenderState( Chaos::CHS_RS_BLEND_FUNC, { Chaos::CHS_BF_ZERO, Chaos::CHS_BF_SRC_COLOR} );
  
  
  frontImage = new Chaos::ChsSprite2D( "frontground" );
  frontImage->setImage( "frontground.png" );
  frontImage->setDepth( 3.0f );
  
  
  mask2Image = new Chaos::ChsSprite2D( "maks" );
  mask2Image->setImage( "mask.png" );
  mask2Image->setDepth( 0.0f );
  mask2Image->getMaterial()->setRenderState( Chaos::CHS_RS_BLEND_FUNC, { Chaos::CHS_BF_ONE_MINUS_SRC_COLOR, Chaos::CHS_BF_SRC_COLOR} );

}

void TransTestScene::onEnter( void ){
  this->add( backImage );
  this->add( mask1Image );
  //this->add( frontImage );
}

static int step = 0;
void TransTestScene::onUpdate( double timeInterval ){
  if(step == 0){
    if( imageAlpha <= 1.0f ){
      imageAlpha += 0.02f;
      backImage->setAlpha( imageAlpha );
    }
    else{
      step = 1;
      mask1Image->getMaterial()->setRenderState( Chaos::CHS_RS_BLEND_FUNC, { Chaos::CHS_BF_DST_COLOR, Chaos::CHS_BF_ZERO} );
    }
  }
  else if(step == 1){
    if( imageAlpha > 0.f ){
      imageAlpha -= 0.02f;
      mask1Image->setAlpha( imageAlpha );
      //std::cout<<"imageAlpha:"<<imageAlpha<<std::endl;
    }
    else{
      step = 2;
      //      mask1Image->setAlpha( 0 );
      this->remove( mask1Image );
    }
  }
}

void TransTestScene::onExit( void ){
}

void TransTestScene::onRelease( void ){
}

