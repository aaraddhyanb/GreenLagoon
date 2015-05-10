// Header Files
//=============

#include "cMayaExporter.h"

#include <cstdint>
#include <map>
#include <maya/MDagPath.h>
#include <maya/MFloatVector.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFnMesh.h>
#include <maya/MGlobal.h>
#include <maya/MIntArray.h>
#include <maya/MItDag.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItSelectionList.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MSelectionList.h>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

// Vertex Definition
//==================

namespace
{
	struct s_vertex
	{
		float x, y, z;
		float nx, ny, nz;
		float u, v;
		float tangentx,tangenty,tangentz;
		float bitangentx,bitangenty,bitangentz;
		uint8_t r, g, b, a;

		s_vertex( const MPoint& i_position, const MFloatVector& i_normal,
			const float i_texcoordU, const float i_texcoordV,
		    const MFloatVector & i_tangent, const MFloatVector & i_bitangent,
			const MColor& i_vertexColor )
			:
			x( static_cast<float>( i_position.x ) ), y( static_cast<float>( i_position.y ) ), z( static_cast<float>( -i_position.z ) ),
			nx( i_normal.x ), ny( i_normal.y ), nz( -i_normal.z ),
			u( i_texcoordU ), v(1- i_texcoordV ),
			tangentx(i_tangent.x), tangenty(i_tangent.y),tangentz(-i_tangent.z),
			bitangentx(-i_bitangent.x), bitangenty(-i_bitangent.y),bitangentz(i_bitangent.z),
			r( static_cast<uint8_t>( ( i_vertexColor.r * 255.0f ) + 0.5f ) ),
			g( static_cast<uint8_t>( ( i_vertexColor.g * 255.0f ) + 0.5f ) ),
			b( static_cast<uint8_t>( ( i_vertexColor.b * 255.0f ) + 0.5f ) ),
			a( static_cast<uint8_t>( ( i_vertexColor.a * 255.0f ) + 0.5f ) )
		{

		}
	};
}

// Helper Function Declarations
//=============================

namespace
{
	std::string CreateUniqueVertexKey( const int i_positionIndex, const int i_normalIndex,
		const int i_texcoordIndex, const int i_vertexColorIndex );
	MStatus ProcessAllMeshes( std::vector<const s_vertex>& o_vertexBuffer, std::vector<unsigned int>& o_indexBuffer );
	MStatus ProcessSelectedMeshes( std::vector<const s_vertex>& o_vertexBuffer, std::vector<unsigned int>& o_indexBuffer );
	MStatus ProcessSingleMesh( const MFnMesh& i_mesh,
		std::vector<const s_vertex>& o_vertexBuffer, std::vector<unsigned int>& o_indexBuffer );
	MStatus FillVertexAndIndexBuffer( const MFnMesh& i_mesh,
		std::vector<const s_vertex>& o_vertexBuffer, std::vector<unsigned int>& o_indexBuffer );
}

// Inherited Interface
//====================

MStatus cs6963::cMayaExporter::writer( const MFileObject& i_file, const MString& i_options, FileAccessMode i_mode )
{
	// Get the name of the file that should be exported
	const MString fileName = i_file.fullName();

	// Gather the vertex and index buffer information
	std::vector<const s_vertex> vertexBuffer;
	std::vector<unsigned int> indexBuffer;
	{
		// The user will decide whether to consider the entire scene or just a selection
		MStatus status;
		if ( i_mode == MPxFileTranslator::kExportAccessMode )
		{
			status = ProcessAllMeshes( vertexBuffer, indexBuffer );
			if ( !status )
			{
				return status;
			}
		}
		else if ( i_mode == MPxFileTranslator::kExportActiveAccessMode )
		{
			status = ProcessSelectedMeshes( vertexBuffer, indexBuffer );
			if ( !status )
			{
				return status;
			}
		}
		else
		{
			MGlobal::displayError( "Unexpected file access mode" );
			return MStatus::kFailure;
		}
	}

	// Export the file
	return Export( fileName, vertexBuffer, indexBuffer );
}

// Implementation
//===============

MStatus cs6963::cMayaExporter::Export( const MString& i_fileName, std::vector<const s_vertex>& i_vertexBuffer, std::vector<unsigned int>& i_indexBuffer )
{
	std::ofstream file;
	file.open(i_fileName.asChar());

	file<<"TotalVertices"<<" "<< i_vertexBuffer.size();
	file<<" ";
	file<<"TotalIndices"<<" "<< i_indexBuffer.size();

	file<<"\r\n \r\n"<<"Vertices"<<"\r\n";
	for(int i=0;i< i_vertexBuffer.size();i++)
	{
		file<<i_vertexBuffer.at(i).x<<" "<<i_vertexBuffer.at(i).y<<" "<<i_vertexBuffer.at(i).z<<"\r\n";

	}

	file<<"\r\n"<<"Normals"<<"\r\n";
	for(int i=0;i< i_vertexBuffer.size();i++)
	{
		file<<i_vertexBuffer.at(i).nx<<" "<<i_vertexBuffer.at(i).ny<<" "<<i_vertexBuffer.at(i).nz<<"\r\n";

	}


	file<<"\r\n"<<"Colors"<<"\r\n";
	for(int i=0;i< i_vertexBuffer.size();i++)
	{
		file<<(int)i_vertexBuffer.at(i).r<<" "<<(int)i_vertexBuffer.at(i).g<<" "<<(int)i_vertexBuffer.at(i).b<<"\r\n";

	}

	file<<"\r\n"<<"UV"<<"\r\n";
	for(int i=0;i< i_vertexBuffer.size();i++)
	{
		file<<i_vertexBuffer.at(i).u<< " "<<i_vertexBuffer.at(i).v<<"\r\n";

	}


	file<<"\r\n"<<"Indices"<<"\r\n";
	for(int i=0;i< i_indexBuffer.size();)
	{
	   	file<<i_indexBuffer.at(i+2)<<" "<<i_indexBuffer.at(i+1)<<" "<<i_indexBuffer.at(i)<<"\r\n";
		i=i+3;
	}

	file<<"\r\n\r\n"<<"Tangents"<<"\r\n";
	for(int i=0;i< i_vertexBuffer.size();i++)
	{
		file<<i_vertexBuffer.at(i).tangentx<<" "<<i_vertexBuffer.at(i).tangenty<<" "<<i_vertexBuffer.at(i).tangentz<<"\r\n";

	}

	file<<"\r\n"<<"BiTangents"<<"\r\n";
	for(int i=0;i< i_vertexBuffer.size();i++)
	{
		file<<i_vertexBuffer.at(i).bitangentx<<" "<<i_vertexBuffer.at(i).bitangenty<<" "<<i_vertexBuffer.at(i).bitangentz<<"\r\n";

	}


	file.close();
	


	return MStatus::kSuccess;
}

// Helper Function Definitions
//============================

namespace
{
	std::string CreateUniqueVertexKey( const int i_positionIndex, const int i_normalIndex,
		const int i_texcoordIndex, const int i_vertexColorIndex )
	{
		std::ostringstream vertexKey;
		vertexKey << i_positionIndex << "_" << i_normalIndex << "_" << i_texcoordIndex << "_" << i_vertexColorIndex;
		return vertexKey.str();
	}

	MStatus ProcessAllMeshes( std::vector<const s_vertex>& o_vertexBuffer, std::vector<unsigned int>& o_indexBuffer )
	{
		for ( MItDag i( MItDag::kDepthFirst, MFn::kMesh ); !i.isDone(); i.next() )
		{
			MFnMesh mesh( i.item() );
			if ( !ProcessSingleMesh( mesh, o_vertexBuffer, o_indexBuffer ) )
			{
				return MStatus::kFailure;
			}
		}

		return MStatus::kSuccess;
	}

	MStatus ProcessSelectedMeshes( std::vector<const s_vertex>& o_vertexBuffer, std::vector<unsigned int>& o_indexBuffer )
	{
		// Iterate through each selected mesh
		MSelectionList selectionList;
		MStatus status = MGlobal::getActiveSelectionList( selectionList );
		if ( status )
		{
			for ( MItSelectionList i( selectionList, MFn::kMesh ); !i.isDone(); i.next() )
			{
				MDagPath dagPath;
				i.getDagPath( dagPath );
				MFnMesh mesh( dagPath );
				if ( !ProcessSingleMesh( mesh, o_vertexBuffer, o_indexBuffer ) )
				{
					return MStatus::kFailure;
				}
			}
		}
		else
		{
			MGlobal::displayError( MString( "Failed to get active selection list: " ) + status.errorString() );
			return MStatus::kFailure;
		}

		return MStatus::kSuccess;
	}

	MStatus ProcessSingleMesh( const MFnMesh& i_mesh,
		std::vector<const s_vertex>& o_vertexBuffer, std::vector<unsigned int>& o_indexBuffer )
	{
		if ( i_mesh.isIntermediateObject() )
		{
			return MStatus::kSuccess;
		}

		return FillVertexAndIndexBuffer( i_mesh, o_vertexBuffer, o_indexBuffer );
	}

	MStatus FillVertexAndIndexBuffer( const MFnMesh& i_mesh,
		std::vector<const s_vertex>& o_vertexBuffer, std::vector<unsigned int>& o_indexBuffer )
	{
		MStatus status;

		// Get a list of the positions
		MPointArray positions;
		{
			status = i_mesh.getPoints( positions );
			if ( !status )
			{
				MGlobal::displayError( status.errorString() );
				return status;
			}
		}

		// Get a list of the normals
		MFloatVectorArray normals;
		{
			status = i_mesh.getNormals( normals );
			if ( !status )
			{
				MGlobal::displayError( status.errorString() );
				return status;
			}
		}

		// Get a list of the texture coordinates
		MFloatArray texcoordUs, texcoordVs;
		{
			status = i_mesh.getUVs( texcoordUs, texcoordVs );
			if ( !status )
			{
				MGlobal::displayError( status.errorString() );
				return status;
			}
		}

		// Get a list of the tangents coordinates
		MFloatVectorArray tan;
		{
			status = i_mesh.getTangents(tan);
			if ( !status )
			{
				MGlobal::displayError( status.errorString() );
				return status;
			}
		}

		// Get a list of the bitangents coordinates
		MFloatVectorArray bitan;
		{
			status = i_mesh.getBinormals(bitan);
			if ( !status )
			{
				MGlobal::displayError( status.errorString() );
				return status;
			}
		}

		// Get a list of the vertex colors
		MColorArray vertexColors;
		{
			int colorSetCount = i_mesh.numColorSets();
			if ( colorSetCount > 0 )
			{
				MString* useDefaultColorSet = NULL;
				MColor defaultColor( 1.0f, 1.0f, 1.0f, 1.0f );
				status = i_mesh.getColors( vertexColors, useDefaultColorSet, &defaultColor );
				if ( !status )
				{
					MGlobal::displayError( status.errorString() );
					return status;
				}
			}
		}

		// Gather vertex and triangle information
		std::map<const std::string, const s_vertex> uniqueVertices;
		std::vector<const std::string> triangles;
		{
			MPointArray trianglePositions;
			MIntArray positionIndices;
			for ( MItMeshPolygon i( i_mesh.object() ); !i.isDone(); i.next() )
			{
				if ( i.hasValidTriangulation() )
				{
					// Store information for each vertex in the polygon
					std::map<int, const std::string> indexToKeyMap;
					{
						MIntArray vertices;
						status = i.getVertices( vertices );
						if ( status )
						{
							for ( unsigned int j = 0; j < vertices.length(); ++j )
							{
								const int positionIndex = vertices[j];
								const int normalIndex = i.normalIndex( j );
								int texcoordIndex;
								{
									status = i.getUVIndex( j, texcoordIndex );
									if ( !status )
									{
										MGlobal::displayError( status.errorString() );
										return status;
									}
								}
								int vertexColorIndex = -1;
								MColor vertexColor( 1.0f, 1.0f, 1.0f, 1.0f );
								{
									int colorSetCount = i_mesh.numColorSets();
									if ( colorSetCount > 0 )
									{
										status = i.getColorIndex( j, vertexColorIndex );
										if ( status )
										{
											vertexColor = vertexColors[vertexColorIndex];
										}
										else
										{
											MGlobal::displayError( status.errorString() );
											return status;
										}
									}
								}

								unsigned int tangentIndex;
								{
									tangentIndex = i.tangentIndex(j);
									if ( !status )
									{
										MGlobal::displayError( status.errorString() );
										return status;
									}
								}
								const std::string vertexKey = CreateUniqueVertexKey( positionIndex, normalIndex,
									texcoordIndex, vertexColorIndex );
								indexToKeyMap.insert( std::make_pair( positionIndex, vertexKey ) );
								uniqueVertices.insert( std::make_pair( vertexKey,
									s_vertex( positions[positionIndex], normals[normalIndex],
										texcoordUs[texcoordIndex], texcoordVs[texcoordIndex],
										tan[tangentIndex],bitan[tangentIndex],
										vertexColor ) ) );
							}
						}
						else
						{
							MGlobal::displayError( status.errorString() );
							return status;
						}
					}
					// Store information for each individual triangle in the polygon
					{
						int triangleCount = 0;
						i.numTriangles( triangleCount );
						for ( int j = 0; j < triangleCount; ++j )
						{
							i.getTriangle( j, trianglePositions, positionIndices );
							for ( unsigned int k = 0; k < positionIndices.length(); ++k )
							{
								const int positionIndex = positionIndices[k];
								std::map<int, const std::string>::iterator mapLookUp = indexToKeyMap.find( positionIndex );
								if ( mapLookUp != indexToKeyMap.end() )
								{
									const std::string& vertexKey = mapLookUp->second;
									triangles.push_back( vertexKey );
								}
								else
								{
									MGlobal::displayError( "A triangle gave a different vertex index than the polygon gave" );
									return MStatus::kFailure;
								}
							}
						}
					}
				}
				else
				{
					MGlobal::displayError( "This mesh has an invalid triangulation" );
					return MStatus::kFailure;
				}
			}
		}

		// Convert the triangle information to vertex and index buffers
		o_vertexBuffer.clear();
		o_indexBuffer.clear();
		o_indexBuffer.resize( triangles.size() );
		{
			std::map<const std::string, unsigned int> keyToIndexMap;
			for ( std::map<const std::string, const s_vertex>::iterator i = uniqueVertices.begin(); i != uniqueVertices.end(); ++i )
			{
				keyToIndexMap.insert( std::make_pair( i->first, static_cast<unsigned int>( o_vertexBuffer.size() ) ) );
				o_vertexBuffer.push_back( i->second );
			}
			for ( size_t i = 0; i < triangles.size(); ++i )
			{
				const std::string& key = triangles[i];
				unsigned int index = keyToIndexMap.find( key )->second;
				o_indexBuffer[i] = index;
			}
		}

		return MStatus::kSuccess;
	}
}
