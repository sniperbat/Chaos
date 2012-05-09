#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;
#include <tinyxml2/tinyxml2.h>
#include "ChsHUDManager.h"
#include "ChsCamera.h"
#include "ChsRenderNode.h"
#include "ChsHUD.h"
#include "ChsFileSystem.h"
#include "ChsSprite2D.h"
#include "ChsTexture2D.h"
#include "ChsResourceManager.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
  ChsHUDManager::ChsHUDManager( void ) : camera( new ChsCamera() ){
  }
  
  //------------------------------------------------------------------------------------------------
  ChsHUDManager::~ChsHUDManager( void ){
  }

  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::init( const ChsRect & viewport ){
    this->camera->ortho( viewport.x, viewport.w, viewport.h, viewport.y, 0.0f, 100.0f);
    this->camera->moveTo( 0.0f , 0.0f, 100.0f );
    this->camera->update();
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::purge( void ){
    
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::update( void ){
    std::pair<std::string, ChsHUD* > p;
    BOOST_FOREACH( p, this->hudRenderList ){
      ChsHUD * hud = p.second;
      hud->updateTree();
    }
  }

  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::showHUD( std::string hudName ){
    auto iter = this->hudRenderList.find( hudName );
    if( iter != this->hudRenderList.end() )
      return;//already on showing
    iter = this->hudList.find( hudName );
    if( iter == this->hudList.end() )
      return;//this hud does not exsit
    insert( this->hudRenderList )( hudName, iter->second );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::hideHUD( std::string hudName ){
    auto iter = this->hudRenderList.find( hudName );
    if( iter != this->hudRenderList.end() ){
      this->hudRenderList.erase( hudName );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::loadHUD( std::string hudName ){
    char * data;
		ChsFileSystem::sharedInstance()->readFileAsUTF8( hudName.c_str(), &data );
		boost::scoped_ptr<char> modelData( data );
		tinyxml2::XMLDocument doc;
		int ret = doc.Parse( data );
		if( tinyxml2::XML_NO_ERROR != ret ){
			printf( "errorStr1:%s\n", doc.GetErrorStr1() );
			printf( "errorStr2:%s\n", doc.GetErrorStr2() );
			doc.PrintError();//get some error
			return ;
		}

    tinyxml2::XMLElement * hudElement = doc.FirstChildElement( "ChsHUD" );
    const char * hudId = hudElement->Attribute( "id" );
    ChsHUD* hud = new ChsHUD( hudId );
    tinyxml2::XMLElement * nodeElement = hudElement->FirstChildElement();
    while( nodeElement != NULL ){
      std::string nodeType = nodeElement->Name();
      if( !nodeType.compare( "ChsSprite2D" )){
        const char * sprite2DId = nodeElement->Attribute( "id" );
        ChsSprite2D * sprite2D;
        if( !sprite2DId )
          sprite2D = new ChsSprite2D( "unnamed" );
        else
          sprite2D = new ChsSprite2D( sprite2DId );
        float depth = nodeElement->FloatAttribute( "depth" );
        sprite2D->setDepth( depth );
        float x = nodeElement->FloatAttribute( "x" );
        float y = nodeElement->FloatAttribute( "y" );
        float w = nodeElement->FloatAttribute( "w" );
        float h = nodeElement->FloatAttribute( "h" );
        sprite2D->moveTo( x, y );
        sprite2D->changeSizeTo( w, h );
        tinyxml2::XMLElement * textureElement = nodeElement->FirstChildElement( "ChsTexture2D" );
        while( textureElement != NULL ){
          std::string textureFileName = textureElement->Attribute( "src" );
          boost::shared_ptr<ChsTexture2D> texture = ChsResourceManager::sharedInstance()->getTexture2D( textureFileName );
          texture->setSampleName( textureElement->Attribute( "sampleName" ) );
          texture->setActiveUnit( textureElement->IntAttribute( "activeUnit" ) );
          x = textureElement->FloatAttribute( "x" );
          y = textureElement->FloatAttribute( "y" );
          w = textureElement->FloatAttribute( "w" );
          h = textureElement->FloatAttribute( "h" );
          sprite2D->setImage( texture, x, y, w, h );
          textureElement = textureElement->NextSiblingElement( "ChsTexture2D" );
        }
        hud->add( sprite2D );
      }
      nodeElement = nodeElement->NextSiblingElement();
    }
    insert( this->hudList )( hudName, hud );
  }
}
