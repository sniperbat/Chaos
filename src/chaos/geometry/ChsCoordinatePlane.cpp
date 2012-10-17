#include <boost/scoped_array.hpp>
#include "ChsCoordinatePlane.h"
#include "platform/ChsOpenGL.h"
#include "ChsVertexBuffer.h"
#include "ChsIndexBuffer.h"
#include "ChsMaterial.h"
#include "ChsMesh.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	ChsCoordinatePlane::ChsCoordinatePlane( float size, int divide ) : ChsModel( "Coordinate Plane" ){
		struct Vertex{
			float x;
			float y;
			float z;
			float r;
			float g;
			float b;
			float a;
			Vertex(){
				r = 1.0f;//r
				g = 1.0f;//g
				b = 1.0f;//b
				a = 1.0f;//a
        y = 0.0f;
			}
		};
		int vertexCount = 2 * ( divide + 1 ) * 2 + 6;
		boost::scoped_array<Vertex> vertices( new Vertex[vertexCount] );
		float stepSize = size / divide;
		float width = size / 2;
    int halfDiveide = divide >> 1;
		for( int i = -halfDiveide, k = 0; i <= halfDiveide; ++i, k += 4 ){
			float w = width;
			if( i == 0 ){
				for( int j = 0; j < 4; j++ ){
					vertices[k+j].r = 0.0f;//r
					vertices[k+j].g = 1.0f;//g
					vertices[k+j].b = 0.0f;//b
					vertices[k+j].a = 1.0f;//a
				}
				w += stepSize;
			}
			vertices[k].z = w;
			vertices[k+1].z = -w;
			vertices[k+2].x = w;
			vertices[k+3].x = -w;

			vertices[k].x = i * stepSize;
			vertices[k+1].x = i * stepSize;
			vertices[k+2].z = i * stepSize;
			vertices[k+3].z = i * stepSize;
		}
		
		int arrowIndex = vertexCount - 6;
		
		for( int i=arrowIndex;i<vertexCount;i++){
			vertices[i].r = 0.0f;
			vertices[i].g = 0.0f;
			vertices[i].b = 0.0f;
			vertices[i].a = 1.0f;
			vertices[i].x = 0.0f;
			vertices[i].y = 0.0f;
			vertices[i].z = 0.0f;
			switch ( (i-arrowIndex)/2 ) {
				case 0:
					vertices[i].r = 1.0f;
					break;
				case 1:
					vertices[i].g = 1.0f;
					break;
				case 2:
					vertices[i].b = 1.0f;
					break;
			}
			
			if( i%2 == 0 ){
				vertices[i].x = 0.0f;
				vertices[i].y = 0.0f;
				vertices[i].z = 0.0f;
			}
			
		}
		vertices[arrowIndex+1].x = .5f;
		vertices[arrowIndex+3].y = .5f;
		vertices[arrowIndex+5].z = .5f;		
		
		ChsMesh * mesh = new ChsMesh();
		
		mesh->getVertexBuffer()->addAttrib( 3, GL_FLOAT, false, "position" );
		mesh->getVertexBuffer()->addAttrib( 4, GL_FLOAT, true, "vertexColor" );
		mesh->getVertexBuffer()->setDataWithArray( vertices.get(), sizeof( Vertex ) * (vertexCount-6) );
		
		int indexCount = vertexCount-6;
		boost::scoped_array<GLushort> indices( new GLushort [indexCount] );
		for( int i = 0; i < indexCount; i++ )
			indices[i] = ( GLushort )i;
		
		mesh->getIndexBuffer()->setDataWithArray( indices.get(), indexCount, GL_UNSIGNED_SHORT );
		mesh->getIndexBuffer()->setMode( GL_LINES );
		
		ChsMaterial * material = new ChsMaterial();
		material->setShader( "Wireframe.vsh", "Wireframe.fsh" );
		material->addProperty( "hasVertexColor", CHS_SHADER_UNIFORM_1_INT, 1 );
		material->setProperty( "hasVertexColor", 1 );
		mesh->setMaterial( material );
		this->add( mesh );
		
		mesh = new ChsMesh();
		mesh->getVertexBuffer()->addAttrib( 3, GL_FLOAT, false, "position" );
		mesh->getVertexBuffer()->addAttrib( 4, GL_FLOAT, true, "vertexColor" );
		mesh->getVertexBuffer()->setDataWithArray( vertices.get()+(vertexCount-6), sizeof( Vertex ) * 6 );
		for( int i = 0; i < 6; i++ )
			indices[i] = ( GLushort )i;
		mesh->getIndexBuffer()->setDataWithArray( indices.get(), 6, GL_UNSIGNED_SHORT );
		mesh->getIndexBuffer()->setMode( GL_LINES );
		material = new ChsMaterial();
		material->setShader( "Wireframe.vsh", "Wireframe.fsh" );
		material->addProperty( "hasVertexColor", CHS_SHADER_UNIFORM_1_INT, 1 );
		material->setProperty( "hasVertexColor", 1 );
		mesh->setMaterial( material );
//		material->setRenderState( CHS_RS_DEPTH_TEST, CHS_RS_DISABLE );
		this->add( mesh );
    
	}
  
	//------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
