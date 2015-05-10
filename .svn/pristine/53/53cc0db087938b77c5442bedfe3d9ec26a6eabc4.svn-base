#ifndef CMESH_H
#define CMESH_H

#include "cTime.h"
#include "UserInput.h"
#include <d3dx9math.h>
#include <d3dx9.h>
#include<assert.h>
#include<string>
#include<fstream>
#include<istream>
#include <cassert>
#include "SpatialPartition.h"


namespace cs6963
{
		struct s_vertex
	{
		float x, y, z;
		D3DCOLOR color;
		D3DXVECTOR2 text;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 bitangent;
	};
	

	class cMesh
	{
	private:


		// Ideally a game would have many different vertex declarations,
		// but we will only use a single one for our class
		IDirect3DVertexDeclaration9* m_vertexDeclaration;

		struct
		{
			IDirect3DIndexBuffer9 * indexBuffer;
			IDirect3DVertexBuffer9* vertexBuffer;
			
		} m_scene;

		static Octree *octree;

		static D3DPRIMITIVETYPE primitiveType;
		int triangleCount;
		int vertexCount;
		float rotation;
		D3DXVECTOR3 position;
		std::string meshAddress;
		IDirect3D9* m_direct3dInterface;
		IDirect3DDevice9* m_direct3dDevice;
		bool playerPosChanged;

		std::string mTextureName;

	public:
		s_vertex* vertexData;

		cMesh(){}
	    cMesh(IDirect3DDevice9 *i_direct3dDevice,IDirect3D9 * i_direct3dInterface,char * i_meshAddress, float i_rotation,D3DXVECTOR3 i_position);
	

		bool Initialize(IDirect3DDevice9 * i_direct3dDevice,IDirect3D9 * i_direct3dInterface,char * i_meshAddress, float i_rotation,D3DXVECTOR3 i_position,
	                          int i_vertexCount, int i_triangleCount);
		bool createBuffers();
		bool fillBuffers(int i_vertexCount, int i_triangleCount, std::ifstream &meshFileReadOnly);

		void Update();
		void BeginScene();
	    void LocalizeMesh();

		static void createOctTree();
		void detectCollision();

		int meshCount;
		bool isStatic;

		static void WireMode(bool status);

		D3DXVECTOR3 GetPosition( void );
		float GetRotation();
		void SetRotation(float i_rotation);
		void SetPosition( const D3DXVECTOR3 &i_position );
		void SetPosition(float i_positionX, float i_positionY, float i_positionZ );
        void Translate( const D3DXVECTOR3 &i_offset );

	    float Dot(D3DXVECTOR3 qp, D3DXVECTOR3 n);

	    D3DXVECTOR3 Cross(D3DXVECTOR3 ab, D3DXVECTOR3 ac);

	    int IntersectSegmentTriangle(D3DXVECTOR3 p, D3DXVECTOR3 q, D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c,
								 float &u, float &v, float &w, float &t);
	
		void setTextureName(std::string i_textureName);
		std::string getTextureName();

		bool positionChanged();

		bool getNature();
		void SetStatic(bool i_status);

		D3DXVECTOR3 cameraPosition;
	};

}

#endif