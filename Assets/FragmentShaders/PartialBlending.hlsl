/*
	This is an example of a fragment shader
*/

// Uniforms
//=========

uniform float g_secondsElapsed = 1.0;
uniform  float4 i_lightSource=0;
uniform float4 lightParameter;
sampler2D tex;
uniform float alpha;



// Shader program
//===============


void main( in float4 i_color : COLOR0, 
           out float4 diffuseLight : COLOR0,
		   in float2 i_texture: TEXCOORD0,
		   in float3 i_normal: NORMAL
		 
		   )
{
	 float3 normal_lightSource=normalize(i_lightSource);
	 float brightness= saturate(dot(normal_lightSource, i_normal));
	
	 float4 someTexture = tex2D(tex, i_texture);
	 someTexture[3]=alpha;
	float lightIntensity=lightParameter.w;
	float3 lightColor=lightParameter.xyz;

	diffuseLight =i_color * brightness * someTexture *float4(lightColor,1) * lightIntensity;

	
}
