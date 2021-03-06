#include <tinyxml2.h>
#include "ChsHUDManager.h"
#include "camera/ChsCamera.h"
#include "ChsRenderNode.h"
#include "ChsHUD.h"
#include "io/ChsFileSystem.h"
#include "ChsSprite2D.h"
#include "ChsTextureEntity.h"
#include "ChsResourceManager.h"
#include "core/ChsUtility.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
  ChsHUDManager::ChsHUDManager( void ) : camera( new ChsCamera() ){
  }
  
  //------------------------------------------------------------------------------------------------
  ChsHUDManager::~ChsHUDManager( void ){
  }

  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::init( const ChsRect<int> & viewport ){
    this->camera->ortho( viewport.x, viewport.w, viewport.h, viewport.y, 0.0f, 100.0f);
    this->camera->moveTo( 0.0f , 0.0f, 100.0f );
    this->camera->update();
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::purge( void ){
    
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::update( float dt ){
    for( std::pair<std::string, ChsHUD* > p : this->hudRenderList ){
      ChsHUD * hud = p.second;
      hud->updateTree( dt );
    }
  }

  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::showHUD( const std::string & hudName ){
    do{
      auto iter = this->hudRenderList.find( hudName );
      if( iter != this->hudRenderList.end() )
        break;//already on showing
      iter = this->hudList.find( hudName );
      if( iter == this->hudList.end() )
        break;//this hud does not exsit
      this->hudRenderList.insert( std::make_pair( hudName, iter->second ) );
    }while( 0 );
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::hideHUD( const std::string & hudName ){
    auto iter = this->hudRenderList.find( hudName );
    if( iter != this->hudRenderList.end() ){
      this->hudRenderList.erase( hudName );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  static std::vector< std::shared_ptr<ChsTexture2D> > textureList;
 
  //------------------------------------------------------------------------------------------------
  void prepareTextureList( const tinyxml2::XMLElement * textureElement );
  void prepareTextureList( const tinyxml2::XMLElement * textureElement ){
    std::string textureFileName = textureElement->Attribute( "src" );
    std::shared_ptr<ChsTexture2D> texture = ChsResourceManager::sharedInstance()->getTexture2D( textureFileName );
    textureList.push_back( texture );
  }
  
  //------------------------------------------------------------------------------------------------
  ChsSprite2D * makeSprite( tinyxml2::XMLElement * spriteElement );
  ChsSprite2D * makeSprite( tinyxml2::XMLElement * spriteElement ){
    const char * sprite2DId = spriteElement->Attribute( "id" );
    ChsSprite2D * sprite2D;
    if( !sprite2DId ){
      sprite2D = new ChsSprite2D( "unnamed" );
    }
    else{
      sprite2D = new ChsSprite2D( sprite2DId );
    }
    sprite2D->setRenderTag( CHS_RENDER_TAG_HUD );
    float depth = spriteElement->FloatAttribute( "depth" );
    sprite2D->setDepth( depth );
    float x = spriteElement->FloatAttribute( "x" );
    float y = spriteElement->FloatAttribute( "y" );
    float w = spriteElement->FloatAttribute( "w" );
    float h = spriteElement->FloatAttribute( "h" );
    sprite2D->moveTo( x, y );
    sprite2D->changeSizeTo( w, h );
    tinyxml2::XMLElement * texEntityElement = spriteElement->FirstChildElement( "ChsTextureEntity" );
    while( texEntityElement != nullptr ){
      int index = texEntityElement->IntAttribute( "index" );
      std::shared_ptr<ChsTextureEntity> texture( new ChsTextureEntity( textureList[index] ) );
      std::string sampleName = texEntityElement->Attribute( "sampleName" );
      texture->setSampleName( sampleName );
      texture->setActiveUnit( texEntityElement->IntAttribute( "activeUnit" ) );
      x = texEntityElement->FloatAttribute( "x" );
      y = texEntityElement->FloatAttribute( "y" );
      w = texEntityElement->FloatAttribute( "w" );
      h = texEntityElement->FloatAttribute( "h" );
      
      const char * wrap_s = texEntityElement->Attribute( "wrap_s" );
      if( wrap_s ){
        texture->setWrap( CHS_TEXTURE_WRAP_S, getTexWrapValue( wrap_s ) );
      }
      const char * wrap_t = texEntityElement->Attribute( "wrap_t" );
      if( wrap_t ){
        texture->setWrap( CHS_TEXTURE_WRAP_T, getTexWrapValue( wrap_t ) );
      }
     
      sprite2D->setImage( texture, x, y, w, h );
      texEntityElement = texEntityElement->NextSiblingElement( "ChsTexture2D" );
    }
    return sprite2D;
  }
  
  //------------------------------------------------------------------------------------------------
  void ChsHUDManager::loadHUD( const std::string & hudName ){
    char * data;
    std::string fullpath = "assets/" + hudName;
		ChsFileSystem::sharedInstance()->readFileAsUTF8( fullpath.c_str(), &data );
		std::unique_ptr<char[]> modelData( data );
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
    textureList.clear();
    while( nodeElement != nullptr ){
      std::string nodeType = nodeElement->Name();
      if( !nodeType.compare( "ChsTexture2D" ) ){
        prepareTextureList( nodeElement );
      }
      else if( !nodeType.compare( "ChsSprite2D" ) ){
        hud->add( makeSprite( nodeElement ) );
      }
      nodeElement = nodeElement->NextSiblingElement();
    }
    this->hudList.insert( std::make_pair( hudName, hud ) );
  }
  
  //--------------------------------------------------------------------------------------------------
  void ChsHUDManager::unloadHUD( const std::string & shudName ){
    
  }
}

//--------------------------------------------------------------------------------------------------
