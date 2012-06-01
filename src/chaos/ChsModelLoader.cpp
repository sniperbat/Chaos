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
  void setVertexBuffer( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh );
  void setVertexBuffer( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh ){
    tinyxml2::XMLElement * vertexElement = meshElement->FirstChildElement( "ChsVertexBuffer" );
    const char * vertexArrayText = vertexElement->GetText();
    if( vertexArrayText == nullptr ){
      //no vertex data in xml segment,just init vertex buffer
      int size = vertexElement->IntAttribute( "count" ) * sizeof( float );
      mesh->getVertexBuffer()->init( size );
    }
    else{
      //have vertex data in xml segment, init and set data
      std::vector<float> vertices;
      lexicalCastToArray( vertices, vertexArrayText );
      mesh->getVertexBuffer()->setDataWithVector( vertices );
      vertices.clear();
    }
  }
  
  //------------------------------------------------------------------------------------------------
  template <typename T> void setIndexData( ChsIndexBuffer * indexBuffer, const char * indexArrayText ){
    std::vector<T> indeices;
    lexicalCastToArray( indeices, indexArrayText );
    indexBuffer->setDataWithVector( indeices );
  }
  //------------------------------------------------------------------------------------------------
  void setIndexBuffer( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh );  
  void setIndexBuffer( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh ){
    tinyxml2::XMLElement * indexElement = meshElement->FirstChildElement( "ChsIndexBuffer" );
    ChsIndexBuffer * indexBuffer = mesh->getIndexBuffer();
    //unsigned short or unsigned int
    const bool isShort = indexElement->BoolAttribute( "isShort" );
    const char * indexArrayText = indexElement->GetText();
    if( indexArrayText == nullptr ){
      //no index data in xml segment, just init the index buffer
      int count = indexElement->IntAttribute( "count" );
      indexBuffer->init( count, isShort ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT );
    }
    else{
      //have data in xml segment, set data to index buffer
      if( isShort )
        setIndexData<unsigned short>( indexBuffer, indexArrayText );
      else
        setIndexData<unsigned int>( indexBuffer, indexArrayText );
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
  void setPropertys( tinyxml2::XMLElement * materialElement, ChsMaterial * material );
  void setPropertys( tinyxml2::XMLElement * materialElement, ChsMaterial * material ){
    tinyxml2::XMLElement * propertyElement = materialElement->FirstChildElement( "ChsProperty" );
    while( propertyElement ){
      std::string propertyName = propertyElement->Attribute( "name" );
      ChsShaderUniformDataType type = static_cast<ChsShaderUniformDataType>( propertyElement->UnsignedAttribute( "type" ) );
      unsigned int count = propertyElement->UnsignedAttribute( "count" );
      material->addProperty( propertyName, type, count );
      switch ( type ) {
        case CHS_SHADER_UNIFORM_1_FLOAT:
          material->setProperty( propertyName, propertyElement->FloatAttribute( "value" ) );
          break;
        case CHS_SHADER_UNIFORM_1_INT:
          material->setProperty( propertyName, propertyElement->IntAttribute( "value" ) );
          break;
        default:
          break;
      }
      propertyElement = propertyElement->NextSiblingElement( "ChsProperty");
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void setTextures( tinyxml2::XMLElement * materialElement, ChsMaterial * material );
  void setTextures( tinyxml2::XMLElement * materialElement, ChsMaterial * material ){
    tinyxml2::XMLElement * textureElement = materialElement->FirstChildElement( "ChsTexture2D" );
    ChsResourceManager * resMgr = ChsResourceManager::sharedInstance();
    while( textureElement ){
      std::string textureFileName = textureElement->Attribute( "src" );
      boost::shared_ptr<ChsTextureEntity> texture( new ChsTextureEntity( resMgr->getTexture2D( textureFileName ) ) );
      texture->setSampleName( textureElement->Attribute( "sampleName" ) );
      texture->setActiveUnit( textureElement->IntAttribute( "activeUnit" ) );
      material->addTexture( texture );
      textureElement = textureElement->NextSiblingElement( "ChsTexture2D");
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void setRenderStates( tinyxml2::XMLElement * materialElement, ChsMaterial * material );
  void setRenderStates( tinyxml2::XMLElement * materialElement, ChsMaterial * material ){
    tinyxml2::XMLElement * renderStateElement = materialElement->FirstChildElement( "ChsRenderState" );
    while( renderStateElement ){
      int index = renderStateElement->IntAttribute( "index" );
      int value = renderStateElement->IntAttribute( "value" );
      material->setRenderState( static_cast<ChsRenderState>( index ), value );
      renderStateElement = renderStateElement->NextSiblingElement( "ChsRenderState");
    }
  }
  
  //------------------------------------------------------------------------------------------------
  void setShaders( tinyxml2::XMLElement * materialElement, ChsMaterial * material );
  void setShaders( tinyxml2::XMLElement * materialElement, ChsMaterial * material ){
    std::string vsName = materialElement->FirstChildElement( "ChsVertexShader" )->Attribute( "src" );
    std::string fsName = materialElement->FirstChildElement( "ChsFragmentShader" )->Attribute( "src" );
    material->setShader( vsName, fsName );
  }
  
  //------------------------------------------------------------------------------------------------
  void setMaterial( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh );
  void setMaterial( tinyxml2::XMLElement * meshElement, boost::shared_ptr<ChsMesh> & mesh ){
    tinyxml2::XMLElement * materialElement = meshElement->FirstChildElement( "ChsMaterial" );
    if( materialElement ){
      ChsMaterial * material = new ChsMaterial();
      setShaders( materialElement, material );
      setTextures( materialElement, material );
      setPropertys( materialElement, material );
      setRenderStates( materialElement, material );
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
		readData<int>( data );//skip magic number
    //load xml segment
    int xmlSize = readData<int>( data );
    ChsModel * model = this->loadAsXML( data );
    skipData( data, xmlSize );
    //load binary segment
    int meshCount = model->meshs.size();
    for( int i = 0; i < meshCount; i++ ){
      ChsMesh * mesh = model->meshs[i].get();
      int vertexArraySize = readData<int>( data );
      mesh->getVertexBuffer()->setDataWithArray( data, vertexArraySize );
      skipData( data, vertexArraySize );
      int indexArraySize = readData<int>( data );
      int count = mesh->getIndexBuffer()->getCount();
      int type = mesh->getIndexBuffer()->getType();
      mesh->getIndexBuffer()->setDataWithArray( data, count, type );
      skipData( data, indexArraySize );
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
