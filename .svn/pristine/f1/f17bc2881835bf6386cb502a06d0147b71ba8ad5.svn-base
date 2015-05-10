#include "Camera.h"
#include"Scene.h"
#include <math.h>



namespace cs6963
{
      void Camera::CreateCamera(const D3DXVECTOR3 &i_cameraPosition) 
      {
		  lookAtPoint=D3DXVECTOR3(0.0f, -200.0f, 0.0f);
		  up=D3DXVECTOR3(0.0f, 1.0f, 0.0f);
          rotation=0.f;
		  position=i_cameraPosition;
		  freeFollowing=true;
       }

       void Camera::SetPosition( const D3DXVECTOR3 &i_position )
       {
               position = i_position;
       }

	   D3DXVECTOR3  Camera::getPosition()
       {
               return position;
       }

	   float Camera::getRotation()
	   {
		   return rotation;
	   }

       void Camera::Translate( const D3DXVECTOR3 &i_offset )
       {
               position += i_offset;
       }
       void Camera::SetLookAtPointAndRotation( const D3DXVECTOR3 &i_lookAtPoint, const D3DXVECTOR3 &i_camPosition,float i_rotation )
       {
               lookAtPoint = i_lookAtPoint;
	           position=i_camPosition;
       }

       D3DXMATRIX Camera::GetWorldToViewTransform() const
       {
              D3DXMATRIX transform_worldToView;
              D3DXMatrixLookAtLH( &transform_worldToView, &position,&lookAtPoint,&up);
              return transform_worldToView;
       }

	   void Camera::Follow(cs6963::cMesh *i_followEntity)
	   {
		   freeFollowing=false;
		   followEntity=i_followEntity;
	   }

       void Camera::Update()
       {
		   if(freeFollowing)
		   {
               D3DXVECTOR3 offset(0.0f, 0.0f, 0.0f);

               if( UserInput::IsKeyPressed('W'))
               {
				       offset.x -= sin(rotation) *100.f;
                       offset.z += cos(rotation) * 100.f;

               }
               if( UserInput::IsKeyPressed('A'))
               {
                       rotation+=0.02f;
					   if(rotation>360.f)
						   rotation= rotation- 360.f;
               }
               if( UserInput::IsKeyPressed('S'))
               {
					   offset.x += sin(rotation) *100.f;
                       offset.z -= cos(rotation) * 100.f;
               }
               if( UserInput::IsKeyPressed('D'))
               {
				       rotation-=0.02f;
					   if(rotation<-360.f)
						   rotation= rotation+ 360.f;
               }
			    if( UserInput::IsKeyPressed(VK_SPACE))
               {
                       offset.y += 500.f;
               }
			   
               float movement = 2.0f;

               offset *= (movement * g_time.GetSecondsElapsedThisFrame() );

               Translate(offset);
		   }
		   else
		   {
			   if(followEntity!=NULL)
			   {
				   SetLookAtPointAndRotation(followEntity->GetPosition(), followEntity->cameraPosition , followEntity->GetRotation());
			   }
		   }
       }
}