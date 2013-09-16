#ifndef _CHSMESH_H
#define _CHSMESH_H
#include "ChsRenderNode.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
	//------------------------------------------------------------------------------------------------
	class ChsMaterial;
	class ChsVertexBuffer;
	class ChsIndexBuffer;

	//------------------------------------------------------------------------------------------------
	class ChsMesh : public ChsRenderNode{
	public:
		ChsMesh( const std::string & name = "unnamed" );
		virtual ~ChsMesh( void );
		void setMaterial( ChsMaterial * material );
		inline ChsMaterial * getMaterial( void )const;
		virtual void update( double timeInterval ) override;
    inline ChsVertexBuffer * getVertexBuffer( void )const;
    inline ChsIndexBuffer * getIndexBuffer( void )const;
	protected:
		std::shared_ptr<ChsMaterial> material;
    std::unique_ptr<ChsVertexBuffer> vertexBuffer;
    std::unique_ptr<ChsIndexBuffer> indexBuffer;
	};

  //------------------------------------------------------------------------------------------------
  inline ChsVertexBuffer* ChsMesh::getVertexBuffer( void )const{
    return this->vertexBuffer.get();
  }
  
  //------------------------------------------------------------------------------------------------
  inline ChsIndexBuffer* ChsMesh::getIndexBuffer( void )const{
    return this->indexBuffer.get();
  }
  
	//------------------------------------------------------------------------------------------------
	inline ChsMaterial * ChsMesh::getMaterial( void )const{
		return this->material.get();
	}
	
	//------------------------------------------------------------------------------------------------
  
}//namespace

//--------------------------------------------------------------------------------------------------
#endif //_CHSMESH_H
