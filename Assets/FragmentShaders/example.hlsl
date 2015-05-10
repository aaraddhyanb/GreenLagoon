/*
	This is an example of a fragment shader
*/

// Uniforms
//=========

uniform float g_secondsElapsed = 1.0;
uniform  float4 i_lightSource=0;
uniform float4 lightParameter;
sampler2D tex;
sampler2D normalTex;



// Shader program
//===============


void main( in float4 i_color : COLOR0, 
		   in float2 i_texture: TEXCOORD0,
		   in float3 i_worldPos:TEXCOORD1,
		   in float3 i_tangent:TANGENT,
		   in float3 i_binormal:BINORMAL,
		   in float3 i_normal: NORMAL,
           out float4 diffuseLight : COLOR0
		   )
{
	
	float3 T= normalize(i_tangent);
	float3 B= normalize(i_binormal);
	float3 N=normalize( i_normal);

	float3x3 rotation_textureToWorld=
	{
	  T,
	  B,
	  N 
	};

	float3 sample=tex2D(tex, i_texture);
	float4 normalMap=tex2D(normalTex, i_texture);
	float3 normalMapSample=normalMap.xyz;
	 normalMapSample= ( normalMapSample * 2.0 ) - 1.0;
	float3 normal_world = mul( normalMapSample, rotation_textureToWorld );

	 float3 lightDirection=normalize(i_lightSource-i_worldPos);
	 float brightness= saturate(dot(lightDirection, normal_world));
	

	float lightIntensity=lightParameter.w;
	float3 lightColor=lightParameter.xyz;

	diffuseLight =i_color * float4(sample,1);
	
}
