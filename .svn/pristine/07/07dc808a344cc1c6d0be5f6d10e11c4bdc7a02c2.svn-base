#include "LightSource.h"
#include "cTime.h"
#include "UserInput.h"
#include"Scene.h"

namespace cs6963
{
       void LightSource::SetPosition(D3DXVECTOR4 i_lightPosition)                
       {
			   position=i_lightPosition;	   
       }

	   void LightSource::SetColor(D3DXVECTOR4 i_lightColor)                
       {
			   color=i_lightColor;
       }
    
       void LightSource::Update()
       {
               D3DXVECTOR4 offset(0.0f, 0.0f, 0.0f,0.0f);

               if( UserInput::IsKeyPressed('I'))
               {
                       offset.y += 0.1f;
               }
               if( UserInput::IsKeyPressed('J'))
               {
                       offset.x -= 0.1f;
               }
               if( UserInput::IsKeyPressed('K'))
               {
                       offset.y -= 0.1f;
               }
               if( UserInput::IsKeyPressed('L'))
               {
                       offset.x += 0.1f;
               }

			   position += offset;
              
       }

	   D3DXVECTOR4 LightSource::getLightPosition()
	   {
		   return position;
	   }

	     D3DXVECTOR4 LightSource::getColor()
	   {
		   return color;
	   }
}