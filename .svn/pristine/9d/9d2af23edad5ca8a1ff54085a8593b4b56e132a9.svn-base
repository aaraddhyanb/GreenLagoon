#ifndef _SPATIALPARTITION_
#define _SPATIALPARTITION_

#include <d3dx9.h>
#include <string>
#include <vector>

using namespace std;

namespace cs6963
{
	struct vertex
	{
		float pos[3];
	};

	struct triangle
	{
		vertex tri[3];
	};
  
	struct OctNode
	{
		int depth;
		D3DXVECTOR3 lfb, rbt; //minXYZ and MaxXYZ
		vector<triangle> triangleList;
		OctNode* child[8];
	};

	struct NodeValuePair
	{
		OctNode* nodeAddress;
		int value;
	};

	struct renderAsLines
	{
		D3DXVECTOR3 vertex;
        DWORD color;
	};

	class Octree
	{
		private :
			OctNode *rootNode;
			int granularity;
			std::string filename;
	
		public:
			void initialize(std::string fileName, int granularity);
			void rayIntersectBB();
			void createOctTree();
			void writeToFile(std::string OctreeFile);
			Octree* readFromFile(std::string OctreeFile);
			OctNode * getRootNode();
			static vector<renderAsLines> debugLines;
			static bool showDebugLines;
	};

} //cs693

#endif 