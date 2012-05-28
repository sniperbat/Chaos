#include "tinyxml2/tinyxml2.h"
#include "ChsModelLoader.h"
#include "ChsModel.h"
#include "ChsMesh.h"
#include "ChsIndexBuffer.h"
#include "ChsVertexBuffer.h"
#include "io/ChsFileSystem.h"
#include "ChsResourceManager.h"
#include "ChsUtility.h"
#include "ChsMaterial.h"
#include "ChsTextureEntity.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	template<typename T>
	T readData( char ** data ){
		T value = *(reinterpret_cast<T*>(*data));
		skipData( data, sizeof(T) );
		return value;
	}
	
	//------------------------------------------------------------------------------------------------
	std::string readString( char ** data );
	std::string readString( char ** data ){
		int strCount = readData<int>( data );
		boost::scoped_ptr<char> p( new char[strCount+1] );
		memset( p.get(), 0, strCount+1 );
		memcpy( p.get(), *data, strCount );
		std::string str = p.get();
		skipData( data, strCount );
		return str;
	}
  
  //------------------------------------------------------------------------------------------------
  void setVertexBuffer( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh );
  void setVertexBuffer( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh ){
    tinyxml2::XMLElement * vertexElement = meshElement->FirstChildElement( "ChsVertexBuffer" );
    const char * vertexArrayText = vertexElement->GetText();
    if( vertexArrayText != nullptr ){
      std::vector<float> vertices;
      lexicalCastToArray( vertices, vertexArrayText );
      mesh->getVertexBuffer()->setDataWithVector( vertices );
      vertices.clear();
    }
    else{
      int size = vertexElement->IntAttribute( "count" ) * sizeof( float );
      mesh->getVertexBuffer()->init( size );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void setIndexBuffer( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh );  
  void setIndexBuffer( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh ){
    tinyxml2::XMLElement * indexElement = meshElement->FirstChildElement( "ChsIndexBuffer" );
    ChsIndexBuffer * indexBuffer = mesh->getIndexBuffer();
    const char * indexArrayText = indexElement->GetText();
    const bool isShort = indexElement->BoolAttribute( "isShort" );
    if( indexArrayText != nullptr ){
      if( isShort ){
        std::vector<unsigned short> indeices;
        lexicalCastToArray( indeices, indexArrayText );
        indexBuffer->setDataWithVector( indeices );
        indeices.clear();
      }
      else{
        std::vector<unsigned int> indeices;
        lexicalCastToArray( indeices, indexArrayText );
        indexBuffer->setDataWithVector( indeices );
        indeices.clear();
      }
    }
    else{
      int count = indexElement->IntAttribute( "count" );
      if( isShort )
        indexBuffer->init( count, GL_UNSIGNED_SHORT );
      else
        indexBuffer->init( count, GL_UNSIGNED_INT );
    }
    indexBuffer->setMode( GL_TRIANGLES );
  }
  
  //------------------------------------------------------------------------------------------------
  void setAttributes( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh );
  void setAttributes( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh ){
    tinyxml2::XMLElement * attrElement = meshElement->FirstChildElement( "ChsAttribute" );
    while ( attrElement ) {
      std::string attrName = attrElement->Attribute( "id" );
      int stride = attrElement->IntAttribute( "stride" );
      bool isNormalized = false;
      if( !attrName.compare( "normal" ) )
        isNormalized = true;
      mesh->getVertexBuffer()->addAttrib( stride, GL_FLOAT, isNormalized, attrName );
      attrElement = attrElement->NextSiblingElement( "ChsAttribute" );
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void setMaterial( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh );
  void setMaterial( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh ){
    tinyxml2::XMLElement * materialElement = meshElement->FirstChildElement( "ChsMaterial" );
    if( materialElement ){
      ChsMaterial * material = new ChsMaterial();
      
      const char * src = materialElement->Attribute( "src" );
      if( src ){
        //1: from external material file, reference from src	
      }
      else{
        //2: embed material
        
        std::string vsName = materialElement->FirstChildElement( "ChsVertexShader" )->Attribute( "src" );
        std::string fsName = materialElement->FirstChildElement( "ChsFragmentShader" )->Attribute( "src" );
        material->setShader( vsName, fsName );
        tinyxml2::XMLElement * textureElement = materialElement->FirstChildElement( "ChsTexture2D" );
        while( textureElement ){
          std::string textureFileName = textureElement->Attribute( "src" );
          boost::shared_ptr<ChsTextureEntity> texture( new ChsTextureEntity( ChsResourceManager::sharedInstance()->getTexture2D( textureFileName ) ) );
          texture->setSampleName( textureElement->Attribute( "sampleName" ) );
          texture->setActiveUnit( textureElement->IntAttribute( "activeUnit" ) );
          material->addTexture( texture );
          textureElement = textureElement->NextSiblingElement( "ChsTexture2D");
        }
        
        tinyxml2::XMLElement * propertyElement = materialElement->FirstChildElement( "ChsProperty" );
        while( propertyElement ){
          std::string propertyName = propertyElement->Attribute( "name" );
          std::string type = propertyElement->Attribute( "type" );
          if( !type.compare( "bool" )){
            material->addProperty( propertyName, CHS_SHADER_UNIFORM_1_INT, 1 );
            bool value = propertyElement->BoolAttribute( "value" );
            material->setProperty( propertyName, value );
          }
          propertyElement = propertyElement->NextSiblingElement( "ChsProperty");
        }
        
        tinyxml2::XMLElement * renderStateElement = materialElement->FirstChildElement( "ChsRenderState" );
        while( renderStateElement ){
          int index = renderStateElement->IntAttribute( "index" );
          int value = renderStateElement->IntAttribute( "value" );
          material->setRenderState( static_cast<ChsRenderState>( index ), value );
          renderStateElement = renderStateElement->NextSiblingElement( "ChsRenderState");
        }
      }
      mesh->setMaterial( material );
    }
  }
  
  //------------------------------------------------------------------------------------------------
	ChsModel * ChsModelLoader::loadAsXML( const char * data ){
		tinyxml2::XMLDocument doc;
		int ret = doc.Parse( data );
		if( tinyxml2::XML_NO_ERROR != ret ){
			printf( "errorStr1:%s\n", doc.GetErrorStr1() );
			printf( "errorStr2:%s\n", doc.GetErrorStr2() );
			doc.PrintError();//get some error
			return nullptr;
		}
		
		ChsModel * model = nullptr;
		tinyxml2::XMLElement * modelElement = doc.FirstChildElement( "ChsModel" );
		if( !modelElement ){
			printf( "there no model elements\n" );
			return nullptr;
		}
		
		std::string modelName = modelElement->Attribute( "id" );
		model = new ChsModel( modelName );
		tinyxml2::XMLElement * meshElement = modelElement->FirstChildElement( "ChsMesh" );
		while( meshElement ){
			std::string meshName = meshElement->Attribute( "id" );
			boost::shared_ptr<ChsMesh> mesh( new ChsMesh( meshName ) );
			setAttributes( meshElement, mesh );
      setVertexBuffer( meshElement, mesh );
      setIndexBuffer( meshElement, mesh );
      setMaterial( meshElement, mesh );
			model->addMesh( mesh );
			meshElement = meshElement->NextSiblingElement( "ChsMesh" );
		}
		
		return model;
	}
	
	//------------------------------------------------------------------------------------------------
	ChsModel * ChsModelLoader::loadAsBinary( char *data ){
    if( data[0] != 'c' || data[1] != 'h'||data[2] != 'm' || data[3] != 'o' ){
      printf( "this is not chsmodel file" );
      return nullptr;
    }
		readData<int>( &data );//skip magic number
    int xmlSize = readData<int>( &data );
    ChsModel * model = this->loadAsXML( data );
    skipData( &data, xmlSize );
    
    int meshCount = model->meshs.size();
    for( int i = 0; i < meshCount; i++ ){
      ChsMesh * mesh = model->meshs[i].get();
      int vertexArraySize = readData<int>( &data );
      mesh->getVertexBuffer()->setDataWithArray( data, vertexArraySize );
      skipData( &data, vertexArraySize );
      
      int indexArraySize = readData<int>( &data );
      int count = mesh->getIndexBuffer()->getCount();
      int type = mesh->getIndexBuffer()->getType();
      mesh->getIndexBuffer()->setDataWithArray( data, count, type );
      skipData( &data, indexArraySize );
    }
    
    return model;
	}
	
	//------------------------------------------------------------------------------------------------  
  enum{
    UNKNOWN_FORMAT,
    XML_FORMAT,
    BINARY_FORMAT,
  };
	//------------------------------------------------------------------------------------------------
  int checkFileTypeByName( const std::string & fileName );
  int checkFileTypeByName( const std::string & fileName ){
    if( fileName.find( ".chsmodelx" ) != std::string::npos )
      return XML_FORMAT;
    else if( fileName.find( ".chsmodel" ) != std::string::npos )
      return BINARY_FORMAT;
    else
      return UNKNOWN_FORMAT;
  }
  
	//------------------------------------------------------------------------------------------------
	ChsModel * ChsModelLoader::load( const char *filename ){
		std::string fileName = filename;
    int fileType = checkFileTypeByName( fileName );
    if( UNKNOWN_FORMAT == fileType )
        return nullptr;
    char * data = nullptr;
    ChsFileSystem::sharedInstance()->readFileAsRaw( filename, &data );
    if( data == nullptr )
      return nullptr;
    boost::scoped_ptr<char> modelData( data );
    if( XML_FORMAT == fileType )
      return this->loadAsXML( modelData.get() );
    else
      return this->loadAsBinary( modelData.get() );
	}
  
  //------------------------------------------------------------------------------------------------
  
}
