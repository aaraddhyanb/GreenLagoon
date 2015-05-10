#ifndef PATHFINDINGALGORITHMS_H
#define PATHFINDINGALGORITHMS_H

#include<vector>
#include<map>
#include<d3dx9math.h>
#include"WaypointsData.h"

namespace Engine
{
	struct NeighborData
	{
		int neighbor;
	};

    class PathFinding
    { 

		std::vector<Waypoint> points;
		std::vector<Link> links;
		std::vector<int> pathList;
		std::map<int, std::vector<NeighborData>> neighborList;
	  public:

		void SetPoints(std::vector<Waypoint> i_points);
		void SetLinks(std::vector<Link> i_links);
		static float Distance(D3DXVECTOR3 A, D3DXVECTOR3 B);
		std::vector<D3DXVECTOR3> findShortestPathByAstar(D3DXVECTOR3 goal, D3DXVECTOR3 playerPosition);
   };
}
#endif