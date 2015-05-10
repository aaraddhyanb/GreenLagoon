#ifndef CAMERA
#define CAMERA

#include "cTime.h"
#include "UserInput.h"
#include <d3dx9math.h>



namespace cs6963
{
class cMesh;

       class Camera
       {
               D3DXVECTOR3 position;
               D3DXVECTOR3 lookAtPoint;
               D3DXVECTOR3 up;
			   float rotation;
			   cMesh *followEntity;

       public:
		       Camera(){}
			   void CreateCamera(const D3DXVECTOR3 &i_cameraPosition);
               void Update();

			   void Follow(cs6963::cMesh *i_followEntity);
               void SetPosition( const D3DXVECTOR3 &i_position );
               void Translate( const D3DXVECTOR3 &i_offset );
               void SetLookAtPointAndRotation( const D3DXVECTOR3 &i_lookAtPoint, const D3DXVECTOR3 &i_camPosition, float i_rotation );

			    D3DXVECTOR3 getPosition();
				float getRotation();
				void setRotation(const float &i_rotation);
                D3DXMATRIX GetWorldToViewTransform() const;

	            bool freeFollowing;
       };
}

#endif