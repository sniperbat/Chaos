#ifndef _CHS_SCENEMANAGER_H
#define _CHS_SCENEMANAGER_H
//--------------------------------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include "ChsSingleton.h"

//--------------------------------------------------------------------------------------------------
namespace Chaos {
  
  //------------------------------------------------------------------------------------------------
  class ChsNode;
  class ChsRenderNode;
  
  //------------------------------------------------------------------------------------------------
  class ChsSceneManager : public ChsSingleton<ChsSceneManager> {
  private:
    boost::scoped_ptr<ChsRenderNode> root;
  public:
    ChsSceneManager( void );
    ~ChsSceneManager( void );
    
    ChsNode * getRoot( void )const;
    void update( void );
    void purge( void );
  };

  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif//_CHS_SCENEMANAGER_H
