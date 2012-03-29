#include "GameDemo.h"
#include "ChsEntity.h"
#include "ChsResourceManager.h"
#include "ChsRenderSystem.h"
#include "geometry/ChsPlane.h"
#include "ChsMaterial.h"
#include "ChsShaderProgram.h"
#include "camera/ChsCameraBase.h"
#include "math/ChsMath.h"
#include "ChsDaeLoader.h"
#include <boost/shared_ptr.hpp>
#include "ChsTexture2D.h"
#include "ChsModel.h"

//--------------------------------------------------------------------------------------------------
using namespace Chaos;
#include <math.h>

GameDemo game;
boost::scoped_ptr<ChsCameraBase> camera(new ChsCameraBase());
static float transY = 0.0f;
ChsMaterial * material;
ChsPlane * planeMesh1;
//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
	ChsEntityManager * resMgr = ChsResourceManager::sharedInstance();
	boost::shared_ptr<ChsEntity> plane1 = resMgr->getEntity( "planeEntity1" );

	planeMesh1 = new ChsPlane(4.0f,4.0f);
	
	//planeMesh1->setMaterial();
	//material = planeMesh1->getMaterial();
	//material->hasVertexColor(true);
	
	plane1->add( planeMesh1 );
	
	//this->renderer()->root()->add( plane1->name(), plane1 );
	
	ChsRect viewport = this->renderer()->getViewPort();
	camera->perspective( degree2Radian(60), viewport.w/(float)viewport.h, 0.1f, 1000.0f  );
	camera->lookAt( 0,20,0,0,0,0 );
	this->renderer()->currentCamera( camera.get() );
	this->renderer()->showDebugCoordinate( true );
	
	
	ChsModel * model = ChsResourceManager::sharedInstance()->getModel( "test.chsmodel" ).get();
//	material = mesh->getMaterial();
	//material->hasVertexColor(true);
//	boost::shared_ptr<ChsTexture2D> texture = ChsResourceManager::sharedInstance()->getTexture2D( "sofaLeather.png" );
//	texture->sampleName( "diffuseTexture" );
//	texture->activeUnit( 0 );
//	material->addTexture( texture );

	this->renderer()->root()->add( model->name(), model );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
	transY += 0.0075f;
	float alpha = sin(transY);
	camera->moveTo( cos(transY)*3, 2, sin(transY)*3);
	alpha = alpha >=0 ? alpha : -alpha;
	//material = planeMesh1->getMaterial();
	//material->alpha(1.0f-alpha);
	
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}
