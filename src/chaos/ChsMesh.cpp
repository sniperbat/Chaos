#include "platform/ChsOpenGL.h"
#include "ChsMesh.h"
#include "ChsMaterial.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"

//--------------------------------------------------------------------------------------------------

namespace Chaos {
	
  //------------------------------------------------------------------------------------------------
	ChsMesh::ChsMesh( const std::string & name ) : ChsRenderNode( name ),
                                         vertexBuffer( new ChsVertexBuffer() ),
                                         indexBuffer( new ChsIndexBuffer() )
	{
	}

	//------------------------------------------------------------------------------------------------
	ChsMesh::~ChsMesh( void ) {
	}

	//------------------------------------------------------------------------------------------------
	void ChsMesh::update( void ) {
		ChsRenderUnit unit;
		unit.material = this->material.get();
		unit.vertexBuffer = this->vertexBuffer.get();
		unit.indexBuffer = this->indexBuffer.get();
		this->sendToRender( CHS_RENDER_TAG_OPACITY, unit );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMesh::setMaterial( ChsMaterial * material ) {
		this->material.reset( material );
		if( this->material ){
			// Bind attribute locations.
			// This needs to be done prior to linking.
      assert( !this->material->getShaderProgram().expired() );
			this->vertexBuffer->bindAttribLocations( this->material->getShaderProgram().lock().get() );
			this->material->linkShader();
		}
	}

  //------------------------------------------------------------------------------------------------

}//namespace
