#include "GameDemo.h"
#include "ChsEntity.h"
#include "ChsResourceManager.h"
#include "ChsRenderSystem.h"
#include "geometry/ChsPlane.h"
#include "ChsMaterial.h"
#include "ChsShaderProgram.h"
#include "camera/ChsCamera.h"
#include "math/ChsMath.h"
#include "ChsDaeLoader.h"
#include <boost/shared_ptr.hpp>
#include "ChsTexture2D.h"
#include "ChsModel.h"

//--------------------------------------------------------------------------------------------------
using namespace Chaos;
#include <math.h>

GameDemo game;
boost::scoped_ptr<ChsCamera> camera(new ChsCamera());
static float transY = 0.0f;
ChsMaterial * material;
ChsPlane * planeMesh1;
//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
	ChsEntityManager * resMgr = ChsResourceManager::sharedInstance();
	boost::shared_ptr<ChsEntity> plane1 = resMgr->getEntity( "planeEntity1" );

	planeMesh1 = new ChsPlane(40.0f,40.0f);
	
	//planeMesh1->setMaterial();
	//material = planeMesh1->getMaterial();
	//material->hasVertexColor(true);
	
	plane1->add( planeMesh1 );
	
	//this->renderer()->root()->add( plane1->name(), plane1 );
	
	ChsRect viewport = this->getRender()->getViewPort();
	camera->perspective( degree2Radian(39.6), viewport.w/(float)viewport.h, 0.1f, 1000.0f  );
	//camera->ortho( 0.0f, viewport.w/10, 0.0f, viewport.h/10, 0.1f, 1000.0f );
//	camera->moveTo( 5, 5, 5 );
  //camera->targetTo( 1,1,1);
	this->getRender()->setCurrentCamera( camera.get() );
	this->getRender()->showDebugCoordinate( true );
	
	ChsModel * model = ChsResourceManager::sharedInstance()->getModel( "sofa.chsmodelx" ).get();
	this->getRender()->root()->add( model->getName(), model );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
	transY += 0.0075f;
	float alpha = sin(transY);
	camera->moveTo( cos(transY)*5, 5, sin(transY)*5 );
	//alpha = alpha >=0 ? alpha : -alpha;
	//material = planeMesh1->getMaterial();
	//material->alpha(1.0f-alpha);
	
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}
