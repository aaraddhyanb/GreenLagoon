#ifndef WAYPOINTSDATA_H
#define WAYPOINTSDATA_H

#include<vector>
#include<d3dx9math.h>

struct Waypoint
{
	D3DXVECTOR3 position;
	int id;
};

struct Link
{
	int firstWaypointID, secondWaypointID;
	float distance;
};

namespace Engine
{
    class WaypointsData
    { 
	private:
		
		static WaypointsData *singleton;
	
		//Private constructors 
		WaypointsData(){}
		WaypointsData(const WaypointsData &i_object);
		void operator=(const WaypointsData &i_object);

	  public:

		static WaypointsData& Manager()
		{
			if(singleton==NULL)
			{
				singleton= new WaypointsData();
				return *singleton;
			}
			return *singleton;
		}

		std::vector<Waypoint> points;
		std::vector<Link> links;

		void Init();
		void AddWaypoint(int id, float positionX, float positionY, float positionZ);
		void AddLink(int point1, int point2, float distance);
   };
}
#endif