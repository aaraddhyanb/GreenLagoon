// Header Files
//=============

#include "cMeshBuilder.h"
#include <fstream>
#include <d3dx9math.h>
#include <d3dx9.h>


   struct s_vertex
	{
		float x, y, z;
		D3DCOLOR color;
		D3DXVECTOR2 text;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 bitangent;

	};


bool cs6963::cMeshBuilder::Build_derived( const char* i_fileName_source, const char* i_fileName_target ) const
{
	// For now meshes don't get "built";
	// instead, copy the source mesh as-is to the target
	BOOL shouldFailIfDestinationFileAlreadyExists = FALSE;
   
	            int vertexCount=0;
				int indexCount;
			    int meshCount;
				std::string texture;

				s_vertex *vertexBuffer;
		     	int *indexBuffer;
		


   // Fill the buffer
   std::ofstream outfile(i_fileName_target,std::ios::binary);
		
	std::ifstream infile;
	infile.open(i_fileName_source, std::ios::in); 
			
/*	if (infile.fail())
	LogMessage( "Failed to open mesh file" );
	*/
std::string word;

infile>>word;
				
//if (word=="TotalMeshes")
{
	infile>>meshCount;
	word=" ";
}
outfile.write(reinterpret_cast<const char*>(&meshCount), sizeof(meshCount));

	for(int j=0; j< meshCount; ++j)
	{
		//infile>>word;
					
		/*if (word=="Texture")
		{
			infile>>texture;
			word=" ";
		}*/

		infile>>word;
		
		if (word=="TotalVertices")
		{
			infile>>vertexCount;
			
				vertexBuffer=new s_vertex[vertexCount];
				word=" ";
		}

		infile>>word;
		if (word=="TotalIndices")
		{
			infile>>indexCount;
			indexBuffer=new int[indexCount];
			word=" ";

		}

		infile>>word;
		if (word=="Vertices")
		{
			for(int i=0;i<vertexCount;i++)
			{
				infile>>vertexBuffer[i].x;
				infile>>vertexBuffer[i].y;
				infile>>vertexBuffer[i].z;
			}
			word=" ";

		}

		infile>>word;
		if (word=="Normals")
		{
			for(int i=0;i<vertexCount;i++)
			{
				infile>>vertexBuffer[i].normal.x;
				infile>>vertexBuffer[i].normal.y;
				infile>>vertexBuffer[i].normal.z;
			}
			word=" ";
		}

		infile>>word;
		if (word=="Colors")
		{
			for(int i=0;i<vertexCount;i++)
			{
				int r,g,b;
				infile>>r;
				infile>>g;
				infile>>b;
				vertexBuffer[i].color=D3DCOLOR_XRGB(r,g,b);
					   
			}

			word=" ";
		}


		infile>>word;			
		if (word=="UV")
		{
			for(int i=0;i<vertexCount;i++)
			{
				infile>>vertexBuffer[i].text.x;
				infile>>vertexBuffer[i].text.y;
			}

			word=" ";
		}

		infile>>word;
		if (word=="Indices")
		{
			for(int i=0;i<indexCount;i++)
			{
					
				infile>>indexBuffer[i];
					   
					 
			}
			word=" ";
		}
					
		/*infile>>word;
		if (word=="Tangents")
		{
			for(int i=0;i<vertexCount;i++)
			{
				
				infile>>vertexBuffer[i].tangent.x;
				infile>>vertexBuffer[i].tangent.y;
				infile>>vertexBuffer[i].tangent.z;

			}
			word=" ";
		}

		infile>>word;
		if (word=="BiTangents")
		{
			for(int i=0;i<vertexCount;i++)
			{
					
					   
				infile>>vertexBuffer[i].bitangent.x;
				infile>>vertexBuffer[i].bitangent.y;
				infile>>vertexBuffer[i].bitangent.z;
					
					 
			 }
			 word=" ";
		 }*/

		    outfile.write(reinterpret_cast<const char*>(&vertexCount), sizeof(vertexCount));

			outfile.write(reinterpret_cast<const char*>(&indexCount), sizeof(indexCount));

			for(int i=0;i<vertexCount;i++)
			{
				outfile.write(reinterpret_cast<const char*>(&vertexBuffer[i]), sizeof(vertexBuffer[i]));
			}

			for(int i=0;i<indexCount;i++)
			{
				outfile.write(reinterpret_cast<const char*>(&indexBuffer[i]), sizeof(indexBuffer[i]));
			}
		}

infile.close();

outfile.close();




	//if ( CopyFile( out, i_fileName_target, shouldFailIfDestinationFileAlreadyExists ) == TRUE )
	//{
		return true;
	//}
		
	/*else
	{
		std::string errorMessage = std::string( "Couldn't copy " ) + i_fileName_source + " to " + i_fileName_target + ":  "
			+ GetLastWindowsError();
		FormatAndOutputErrorMessage( errorMessage );
		return false;
	}*/
}
