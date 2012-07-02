#ifndef _CHSMESH_H
#define _CHSMESH_H
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
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
		virtual void update( double timeInterval );
    inline ChsVertexBuffer * getVertexBuffer( void )const;
    inline ChsIndexBuffer * getIndexBuffer( void )const;
	protected:
		boost::shared_ptr<ChsMaterial> material;
    boost::scoped_ptr<ChsVertexBuffer> vertexBuffer;
    boost::scoped_ptr<ChsIndexBuffer> indexBuffer;
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
