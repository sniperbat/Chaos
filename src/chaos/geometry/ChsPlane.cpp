#include "platform/ChsOpenGL.h"
#include "ChsPlane.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	ChsPlane::ChsPlane( std::string name, float w, float h ) : ChsMesh( name ) {
		this->init( w, h );
	}
	
  //------------------------------------------------------------------------------------------------
	ChsPlane::ChsPlane( float w, float h ) : ChsMesh( "unnamed" ) {
    this->init( w, h );
	}

  //------------------------------------------------------------------------------------------------
  void ChsPlane::init( float w, float h ){
    const GLfloat vertices[] = {
			-w/2, -h/2, 0.0f,
			1.0f, 1.0f,   0, 1.0f,
			
			w/2, -h/2, 0.0f,
			0,   1.0f, 1.0f, 1.0f,
			
			-w/2,  h/2, 0.0f,
			0,     0,   0,   0,
			
			w/2,  h/2, 0.0f,
			1.0f,   0, 1.0f, 1.0f,
		};
		memcpy( this->vertices, vertices, sizeof( vertices ) );
		
		this->vertexBuffer->addAttrib( 3, GL_FLOAT, false, "position" );
		this->vertexBuffer->addAttrib( 4, GL_FLOAT, true, "vertexColor" );
		this->vertexBuffer->setDataWithArray( vertices, sizeof( vertices ) );
    const GLubyte index[]={0,1,2,3};
		this->indexBuffer->setDataWithArray( index, 4, GL_UNSIGNED_BYTE );
		this->indexBuffer->setMode( GL_TRIANGLE_STRIP );
  }
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
