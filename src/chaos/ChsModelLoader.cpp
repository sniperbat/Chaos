#include <tinyxml2.h>
#include "ChsModelLoader.h"
#include "ChsModel.h"
#include "ChsMesh.h"
#include "ChsIndexBuffer.h"
#include "ChsVertexBuffer.h"
#include "io/ChsFileSystem.h"
#include "ChsResourceManager.h"
#include "core/ChsUtility.h"
#include "ChsMaterial.h"
#include "ChsTextureEntity.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  void setVertexBuffer( tinyxml2::XMLElement * meshElement, ChsMesh * mesh );
  void setVertexBuffer( tinyxml2::XMLElement * meshElement, ChsMesh * mesh ){
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
  void setIndexBuffer( tinyxml2::XMLElement * meshElement, ChsMesh * mesh );
  void setIndexBuffer( tinyxml2::XMLElement * meshElement, ChsMesh * mesh ){
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
  void setAttributes( tinyxml2::XMLElement * meshElement, ChsMesh * mesh );
  void setAttributes( tinyxml2::XMLElement * meshElement, ChsMesh * mesh ){
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
        case CHS_SHADER_UNIFORM_VEC2_INT:
        case CHS_SHADER_UNIFORM_VEC3_INT:
        case CHS_SHADER_UNIFORM_VEC4_INT:
        case CHS_SHADER_UNIFORM_VEC2_FLOAT:
        case CHS_SHADER_UNIFORM_VEC3_FLOAT:
        case CHS_SHADER_UNIFORM_VEC4_FLOAT:{
          std::string valueStr = propertyElement->Attribute( "value" );
          std::vector<float> value;
          lexicalCastToArray( value, valueStr );
          material->setProperty( propertyName, value.data() );
          break;
        }
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
      std::shared_ptr<ChsTextureEntity> texture( new ChsTextureEntity( resMgr->getTexture2D( textureFileName ) ) );
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
      material->setRenderState( static_cast<ChsRenderStateId>( index ), value );
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
  void setMaterial( tinyxml2::XMLElement * meshElement, ChsMesh * mesh );
  void setMaterial( tinyxml2::XMLElement * meshElement, ChsMesh * mesh ){
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
  void setTransform( tinyxml2::XMLElement * meshElement, ChsMesh * mesh );
  void setTransform( tinyxml2::XMLElement * meshElement, ChsMesh * mesh ){
    tinyxml2::XMLElement * transformElement = meshElement->FirstChildElement( "ChsMatrix" );
    if( transformElement ){
      std::vector<float> array;
      const char * valueText = transformElement->GetText();
      lexicalCastToArray( array, valueText );
      ChsMatrix transform( array.data() );
      mesh->applyTransform( transform );
    }
  }
  
  std::vector<ChsMesh*> meshList;
  //------------------------------------------------------------------------------------------------
  void loadMesh( tinyxml2::XMLElement * parentMeshElement, ChsNode * parentNode );
  void loadMesh( tinyxml2::XMLElement * parentMeshElement, ChsNode * parentNode ){
    tinyxml2::XMLElement * meshElement = parentMeshElement->FirstChildElement( "ChsMesh" );
      while( meshElement ){
        std::string meshName = meshElement->Attribute( "id" );
        int index = meshElement->IntAttribute( "index" );
        ChsMesh * mesh = new ChsMesh( meshName );
        meshList[index] = mesh;
        setAttributes( meshElement, mesh );
        setVertexBuffer( meshElement, mesh );
        setIndexBuffer( meshElement, mesh );
        setTransform( meshElement, mesh );
        setMaterial( meshElement, mesh );
        parentNode->add( mesh );
        
        loadMesh( meshElement, mesh );
        meshElement = meshElement->NextSiblingElement( "ChsMesh" );
      }
  }
  //------------------------------------------------------------------------------------------------
	ChsModel * ChsModelLoader::loadAsXML( const char * data ){
    ChsModel * model = nullptr;
		tinyxml2::XMLDocument doc;
    do{
      int ret = doc.Parse( data );
      if( tinyxml2::XML_NO_ERROR != ret ){
        printf( "errorStr1:%s\n", doc.GetErrorStr1() );
        printf( "errorStr2:%s\n", doc.GetErrorStr2() );
        doc.PrintError();//get some error
        break;
      }
      tinyxml2::XMLElement * modelElement = doc.FirstChildElement( "ChsModel" );
      if( !modelElement ){
        printf( "there no model elements\n" );
        break;
      }
      std::string modelName = modelElement->Attribute( "id" );
      meshList.resize( modelElement->IntAttribute( "meshCount" ) );
      model = new ChsModel( modelName );
      loadMesh( modelElement, model );
    }while(0);
		return model;
	}
	
	//------------------------------------------------------------------------------------------------
	ChsModel * ChsModelLoader::loadAsBinary( char *data ){
    ChsModel * model = nullptr;
    do{
      if( data[0] != 'c' || data[1] != 'h'||data[2] != 's' || data[3] != 'm' ){
        printf( "this is not chsmodel file" );
        break;
      }
      readData<int>( data );//skip magic number
      //load xml segment
      int xmlSize = readData<int>( data );
      model = this->loadAsXML( data );
      skipData( data, xmlSize );
      //load binary segment
      unsigned int meshCount = meshList.size();
      for( int i = 0; i < meshCount; i++ ){
        ChsMesh * mesh = meshList[i];
        int vertexArraySize = readData<int>( data );

        mesh->getVertexBuffer()->setDataWithArray( data, vertexArraySize );
        skipData( data, vertexArraySize );
        
        int indexArraySize = readData<int>( data );
        int count = mesh->getIndexBuffer()->getCount();
        int type = mesh->getIndexBuffer()->getType();
        
        mesh->getIndexBuffer()->setDataWithArray( data, count, type );
        skipData( data, indexArraySize );
      }
    }while (0);
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
    std::unique_ptr<char[]> modelData( data );
    if( XML_FORMAT == fileType )
      return this->loadAsXML( modelData.get() );
    else
      return this->loadAsBinary( modelData.get() );
    meshList.clear();
	}
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
