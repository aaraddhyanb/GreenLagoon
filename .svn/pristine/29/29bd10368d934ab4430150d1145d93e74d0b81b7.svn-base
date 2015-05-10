
/*
	This is an example of a fragment shader
*/

// Uniforms
//=========
uniform float g_secondsElapsed = 1.0;
uniform float4x4 g_worldToViewTransform; 
uniform float4 i_lightSource;
uniform float4 lightParameter;
sampler2D tex;
sampler2D normalTex;
uniform float alpha=0.0;

// Shader program
//===============

void main( in float4 i_color : COLOR0, 
           in float2 i_texCoord : TEXCOORD0, 
		   in float3 i_worldPos : TEXCOORD1, 
		   in float3 i_normal : NORMAL,
		   in float3 i_tangent:TANGENT,
		   in float3 i_binormal:BINORMAL, 
		   out float4 o_color : COLOR0 )
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

	
	float4 normalMap=tex2D(normalTex, i_texCoord);
	float3 normalMapSample=normalMap.xyz;
	 normalMapSample= ( normalMapSample * 2.0 ) - 1.0;
	float3 normal_world = mul( normalMapSample, rotation_textureToWorld );


		float4 textureSample = tex2D(tex, i_texCoord);
		float4 diffuseColor= textureSample+ i_color;
		
		
		
		float distance = length(i_lightSource.xyz - i_worldPos);
		float3 LightColor=lightParameter.xyz;
	    float LightIntensity=lightParameter.w;
		LightIntensity*=1/(1+lightParameter.y*distance*distance);

		float3 lightDirection = normalize( i_lightSource.xyz - i_worldPos );
		float3 reflectedlight = reflect(-lightDirection, normal_world);
		float3 view = normalize(-g_worldToViewTransform[3].xyz - i_worldPos);
		float3 dotproduct =  dot(lightDirection, normal_world) ;

		float4 attenuationFactor=20*lightParameter.w;
		float3 specularlight = saturate(dot( reflectedlight, view ));
		specularlight = pow(specularlight,attenuationFactor);
		specularlight *= dotproduct;
		specularlight*= lightParameter.w;

		float3 diffuseLight= LightColor * LightIntensity* saturate(dotproduct);
		
		float4 ambient =lightParameter.z;

		diffuseLight+=ambient;

		o_color =   (float4(diffuseLight,1.0)* diffuseColor)+ float4(specularlight,1.0);

		
}
