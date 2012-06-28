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
    this->setRenderTag( CHS_RENDER_TAG_OPACITY );
	}

	//------------------------------------------------------------------------------------------------
	ChsMesh::~ChsMesh( void ) {
	}

	//------------------------------------------------------------------------------------------------
	void ChsMesh::update( float dt ) {
		ChsRenderUnit unit;
		unit.material = this->material.get();
		unit.vertexBuffer = this->vertexBuffer.get();
		unit.indexBuffer = this->indexBuffer.get();
		this->sendToRender( unit );
	}
	
	//------------------------------------------------------------------------------------------------
	void ChsMesh::setMaterial( ChsMaterial * material ) {
		this->material.reset( material );
	}

  //------------------------------------------------------------------------------------------------

}//namespace

//--------------------------------------------------------------------------------------------------
