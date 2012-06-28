#ifndef _CHS_NODE_H
#define _CHS_NODE_H
//--------------------------------------------------------------------------------------------------
#include <string>
#include <map>

//--------------------------------------------------------------------------------------------------
namespace Chaos {

	//------------------------------------------------------------------------------------------------
	class ChsNode {
	public:
		ChsNode( const std::string & name );
		~ChsNode( void );
		void add( const std::string & name, ChsNode * node );
		inline void add( ChsNode * node );
		ChsNode * remove( const std::string & name );
		ChsNode * get( const std::string & name );
    inline const std::string & getName( void )const;
    inline ChsNode * getParent( void );
	protected:
		std::map< std::string, ChsNode * >  children;
    std::string name;
  private:
    ChsNode * parent;
	};

  //------------------------------------------------------------------------------------------------
  inline ChsNode * ChsNode::getParent( void ){
    return this->parent;
  }
  
	//------------------------------------------------------------------------------------------------
	inline void ChsNode::add( ChsNode * node ){
    if( node != nullptr )
      this->add( node->getName(), node );
	}

	//------------------------------------------------------------------------------------------------
	inline const std::string & ChsNode::getName( void )const{
    return this->name;
  }

	//------------------------------------------------------------------------------------------------
	typedef std::map< std::string, ChsNode * > ChsNodeList;
	
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_NODE_H