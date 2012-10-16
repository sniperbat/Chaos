#ifndef _CHS_MODELLOADER_H
#define _CHS_MODELLOADER_H
//--------------------------------------------------------------------------------------------------
namespace Chaos {

  //------------------------------------------------------------------------------------------------
	class ChsModel;
  
  //------------------------------------------------------------------------------------------------
	class ChsModelLoader {
	private:
		ChsModel* loadAsXML( const char * data );
		ChsModel* loadAsBinary( char * data );
	public:
		ChsModel* load( const char * filename );
	};
  
  //------------------------------------------------------------------------------------------------
  
}

//--------------------------------------------------------------------------------------------------
#endif