#version 400
precision mediump float;
//http://www.geeks3d.com/20130122/normal-mapping-without-precomputed-tangent-space-vectors/

// Uniforms
uniform sampler2D color_map;
uniform sampler2D normal_map;

uniform vec4 tint_color;
uniform vec4 light_color;

uniform vec4 specular_color;
uniform float specular_power;


// Varying variables
in VS_OUT
{
	vec4 normals;
	vec2 texCoords;
	vec4 lightDir;
	vec4 eyeDir;
} vin;


// Fragment shader output
out vec4 Out_Color;
 
 
 
// http://www.thetenthplanet.de/archives/1180
mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv)
{
	// get edge vectors of the pixel triangle
	vec3 dp1 = dFdx( p );
	vec3 dp2 = dFdy( p );
	vec2 duv1 = dFdx( uv );
	vec2 duv2 = dFdy( uv );
 
	// solve the linear system
	vec3 dp2perp = cross( dp2, N );
	vec3 dp1perp = cross( N, dp1 );
	vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
	// construct a scale-invariant frame 
	float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
	return mat3( T * invmax, B * invmax, N );
}
 


vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord )
{
	// assume N, the interpolated vertex normal and 
	// V, the view vector (vertex to eye)
	vec3 map = texture(normal_map, vin.texCoords).xyz;
   
	map = map * 255./127. - 128./127.;
	mat3 TBN = cotangent_frame(N, -V, vin.texCoords);
	return normalize(TBN * map);
}
 


 // BEGIN Fragment Shader
void main()
{
	vec2 uv = vin.texCoords;
  
	vec3 N = normalize(vin.normals.xyz);
	vec3 L = normalize(vin.lightDir.xyz);
	vec3 V = normalize(vin.eyeDir.xyz);
  
	vec3 PN = perturb_normal(N, V, uv);
  

	vec4 textureColor = texture(color_map, uv).rgba;
	vec4 final_color = vec4(0.15, 0.15, 0.15, 1.0) * textureColor; 
  

	float lambertTerm = dot(PN, L);
	if (lambertTerm > 0.0)
	{
		// DIFFUSE
		final_color += light_color * tint_color * lambertTerm * textureColor; 
	

		// SPECULAR
		vec3 E = normalize(vin.eyeDir.xyz);
		vec3 R = reflect(-L, PN);
		float specular = pow( max(dot(R, E), 0.0), specular_power);
		final_color += specular_color * specular;
	}


	Out_Color.rgb = final_color.rgb;
	Out_Color.a = 1.0;
}