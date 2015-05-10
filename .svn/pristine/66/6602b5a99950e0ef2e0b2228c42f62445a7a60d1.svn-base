#include"WaypointsData.h"

namespace Engine{

WaypointsData *WaypointsData::singleton=NULL;

void WaypointsData::Init()
{
	points.clear();
	links.clear();
}

void WaypointsData::AddLink(int point1, int point2, float i_distance)
{
	Link newLink;
	newLink.distance=i_distance;
	newLink.firstWaypointID=point1;
	newLink.secondWaypointID=point2;
	links.push_back(newLink);
}

void WaypointsData::AddWaypoint(int id, float positionX, float positionY, float positionZ)
{
	Waypoint newPoint;
	newPoint.id=id;
	D3DXVECTOR3 wayPointPosition = D3DXVECTOR3(positionX, positionY, positionZ);
	newPoint.position= wayPointPosition;
	points.push_back(newPoint);
}

} //namespace end