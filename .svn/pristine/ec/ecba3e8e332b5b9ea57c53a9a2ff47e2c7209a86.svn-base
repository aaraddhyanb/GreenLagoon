#include"PathFinding.h"
#include<math.h>
#include"../../../Code/Renderer/Scene.h"
#include"../../../Code/Renderer/SpatialPartition.h"
#include"../Utility/Util.h"

namespace Engine{


void PathFinding::SetLinks(std::vector<Link> i_links)
{
	links=i_links;

	for(int i=0; i<links.size(); ++i)
	{
		NeighborData node1;
		node1.neighbor= links[i].firstWaypointID;

		NeighborData node2;
		node2.neighbor= links[i].secondWaypointID;

		std::map<int,std::vector<NeighborData>>::iterator it= neighborList.find(node1.neighbor);
		if(it== neighborList.end() )
		{
			std::vector<NeighborData> list;
			list.push_back(node2);
			neighborList.insert( std::pair<int,std::vector<NeighborData>>(node1.neighbor,list) );
		}
		else
		{
			it->second.push_back(node2);
		}

		it= neighborList.find(node2.neighbor);
		if(it== neighborList.end() )
		{
			std::vector<NeighborData> list;
			list.push_back(node1);
			neighborList.insert( std::pair<int,std::vector<NeighborData>>(node2.neighbor,list) );
		}
		else
		{
			it->second.push_back(node1);
		}
	}
}

void PathFinding::SetPoints(std::vector<Waypoint> i_points)
{
	points= i_points;
}

float PathFinding::Distance(D3DXVECTOR3 A, D3DXVECTOR3 B)
{
	float distance= (B.x -A.x) * (B.x -A.x) +
					(B.y -A.y) * (B.y -A.y) +
					(B.z -A.z) * (B.z -A.z);
	distance = sqrt(distance);
	return distance;
}

//A*
std::vector<D3DXVECTOR3> PathFinding::findShortestPathByAstar(D3DXVECTOR3 goal, D3DXVECTOR3 playerPosition)
{
	Waypoint startNode;
	Waypoint endNode;

	if(points.size()>0 && links.size()>0)
	{
		float distance=9999.0f;
		for(int i=0; i<points.size(); ++i)
		{
			float distBetweenPoints= Distance(playerPosition, points[i].position);
			if(distBetweenPoints< distance)
			{
				distance=distBetweenPoints;
				startNode= points[i];
			}
		}

		distance=9999.0f;
		for(int i=0; i<points.size(); ++i)
		{
			float distBetweenPoints= Distance(goal, points[i].position);
			if(distBetweenPoints< distance)
			{
				distance=distBetweenPoints;
				endNode= points[i];
			}
		}
	}

	pathList.push_back(startNode.id);

	bool foundPath=false;
	while(!foundPath)
	{
		int currentNode = pathList[pathList.size()-1];
		if(currentNode== endNode.id)
		{
			foundPath=true;
			break;
		}
		bool foundCurrentNode=false;
		for(int k=0; k<points.size(); ++k)
		{
			if( points[k].id==currentNode)
			{
				foundCurrentNode=true;
				break;
			}
		}
		if(!foundCurrentNode)
		{
			//remove from allpaths list 
			int removePoint=pathList[pathList.size()-1];
			pathList.pop_back();
			//remove from points
			int index=-1;
			for(int k=0; k<points.size(); ++k)
			{
				if( points[k].id==removePoint)
				{
					index=k;
					break;
				}
			}
			points.erase(points.begin() + index);
		}
		else
		{
			float F=999999.0f;
			int selectedNode=-1;
			int indexInTheLink=-1;
			//allPaths
			for(int i=0; i< links.size(); ++i)
			{
				if( links[i].firstWaypointID== currentNode)
				{
					float tempF= links[i].distance;
					float tempH=0.0f;
					for(int k=0; k<points.size(); ++k)
					{
						if( points[k].id==links[i].secondWaypointID)
						{
							tempH= Distance(points[k].position, endNode.position);
							break;
						}
					}
					tempF+= tempH;
					if(tempF< F)
					{
						selectedNode= links[i].secondWaypointID;
						F=tempF;
						indexInTheLink=i;
					}
				}
				else if(links[i].secondWaypointID==currentNode )
				{
					float tempF= links[i].distance;
					float tempH=0.0f;
					for(int k=0; k<points.size(); ++k)
					{
						if( points[k].id==links[i].firstWaypointID)
						{
							tempH= Distance(points[k].position, endNode.position);
							break;
						}
					}
					tempF+= tempH;
					if(tempF< F)
					{
						selectedNode= links[i].firstWaypointID;
						F=tempF;
						indexInTheLink=i;
					}
				}
			}
			if(selectedNode!=-1)
			{
				bool presentInTheList=false;
				for(int h=0; h<pathList.size(); ++h)
				{
					if(pathList[h]==selectedNode)
					{
						presentInTheList=true;
					}
				}
				if(!presentInTheList)
				   pathList.push_back(selectedNode);
				else
					links.erase(links.begin() + indexInTheLink);
			}
			else
			{
				pathList.pop_back();
			}
		}
	}



	//deleting redundancy
	int i=pathList.size()-1;

	for(std::vector<int>::iterator vit = pathList.begin()+i; vit != pathList.begin()+1; --vit, --i) 
	{
		for(int j=i-2; j>=0 ; --j)
		{
			std::map<int,std::vector<NeighborData>>::iterator it= neighborList.find(pathList[j]);
			if(it!= neighborList.end() )
			{
				for(int k=0; k< it->second.size(); ++k)
				{
					if(it->second[k].neighbor==pathList[i])
					{
						while(i!=j+1)
						{
						  --vit;
						  vit= pathList.erase(vit);
						  --i;
						}
						--j;
					}
				}
				if(i<2)
					break;
			}
			if(i<2)
				break;
		}
		if(i<2)
			break;
	}
	
	//pass to render lines
	/*cs6963::Entity::pathFindingLines.clear();
	cs6963::renderAsLines line;
	line.color=D3DCOLOR_XRGB (255, 155, 0);
	line.vertex=points[pathList[0]].position;
	cs6963::Entity::pathFindingLines.push_back(line);

	for(int g=1; g<pathList.size()-1; ++g)
	{
		line.vertex=points[pathList[g]].position;
		cs6963::Entity::pathFindingLines.push_back(line);

		line.vertex=points[pathList[g]].position;
		cs6963::Entity::pathFindingLines.push_back(line);
	}

	line.vertex=points[pathList[pathList.size()-1]].position;
	cs6963::Entity::pathFindingLines.push_back(line);*/

	std::vector<D3DXVECTOR3> waypointsPosition;
	for(int i=0; i< pathList.size(); ++i)
	{
		waypointsPosition.push_back(points[pathList[i]].position);	
	}
	return waypointsPosition;
}


} //namespace end