/*
	This is an example of a vertex shader
*/

// Uniforms
//=========

uniform float g_secondsElapsed = 1.0;
uniform float4x4 g_worldMat;
uniform float4x4 g_viewMat;
uniform float4x4 g_projMat;
uniform float alpha;

// Shader program
//===============

void main( in const float3 i_position : POSITION,
           in const float3 i_color : COLOR0, 
		   in float2 i_texture: TEXCOORD0, 
		   in float3 i_normal:NORMAL,
		   in float3 i_tangent:TANGENT,
		   in float3 i_binormal:BINORMAL,
		   out float4 o_position : POSITION, 
		   out float4 o_color : COLOR0, 
		   out float2 o_texture:TEXCOORD0,
		   out float3 o_normal:NORMAL,
		   out float3 o_world: TEXCOORD1,
		   out float4 o_tangent:TANGENT,
		   out float4 o_binormal:BINORMAL
		  
		    )
{
	// Calculate position
	{
		// The easiest example to understand is to use the provided position as-is:
		{
			float4 model_pos= float4( i_position , 1.0 );
			float4 world_pos=mul(model_pos,g_worldMat);
			float4 view_pos=mul(world_pos,g_viewMat);
			float4 proj_pos=mul(view_pos,g_projMat);

			o_position=proj_pos;
		    o_world = world_pos.xyz;

		}
		
	}

	   

	//Calculate normal
	{

	  float3x3 rotation_ModelToWorld=
	  {
	     
	      g_worldMat[0].xyz,
		  g_worldMat[1].xyz,
		  g_worldMat[2].xyz
	  };

	       o_normal=mul(normalize(i_normal),rotation_ModelToWorld );
	  
	        
			o_tangent=mul(normalize(i_tangent),g_worldMat);
			
			
			o_binormal=mul(normalize(i_binormal),g_worldMat);
			

	}


	// Calculate color
	{
		
		// To give a flavor of interpolation we could base the color on the vertex's position:
		{
			o_color = float4(i_color,1.0f);
		}


	    //Calulate Texture
	    {

	         o_texture=i_texture;

	   
	    }
 	}

}
