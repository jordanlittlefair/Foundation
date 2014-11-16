/*
	Diffuse
*/
//#define DIFFUSE_LDOTN
#define DIFFUSE_ORENNAYAR

inline float3 CalculateDiffuse_LDotN(	float3 view_direction,
										float3 light_direction,
										float3 light_colour,
										float3 surface_normal,
										float3 surface_colour,
										float surface_roughness )
{
	const float intensity = saturate( dot( light_direction, surface_normal ) );
	
	return ( light_colour * surface_colour * intensity );
}

inline float3 CalculateDiffuse_OrenNayar(	float3 view_direction,
											float3 light_direction,
											float3 light_colour,
											float3 surface_normal,
											float3 surface_colour,
											float surface_roughness )
{
	// http://content.gpwiki.org/index.php/D3DBook:(Lighting)_Oren-Nayar

	const float gamma = dot(	view_direction - surface_normal * dot( view_direction, surface_normal ),
								light_direction - surface_normal * dot( light_direction, surface_normal ) );
						
	const float rough_sq = surface_roughness * surface_roughness;
	
	const float A = 1 - 0.5 * ( rough_sq / ( rough_sq + 0.57 ) );
	const float B = 0.45 * ( rough_sq / ( rough_sq + 0.09 ) );
	
	const float alpha = max( acos( dot( view_direction, surface_normal ) ), acos( dot( light_direction, surface_normal ) ) );
	const float beta  = min( acos( dot( view_direction, surface_normal ) ), acos( dot( light_direction, surface_normal ) ) );
	
	const float C = sin( alpha ) * tan( beta );
	
	const float intensity = saturate( ( A + B * max( 0, gamma ) * C ) * max( 0.0f, dot( surface_normal, light_direction ) ) );
	
	return ( light_colour * surface_colour * intensity );
}						

/*
	Specular
*/
//#define SPECULAR_BLINNPHONG
#define SPECULAR_COOKTORRANCE

inline float3 CalculateSpecular_BlinnPhong(	float3 view_direction,
											float3 light_direction,
											float3 light_colour,
											float3 surface_normal,
											float3 surface_colour,
											float surface_roughness )
{
	float exponent = surface_roughness * surface_roughness * 256;
	
	float3 light_dir_plus_view_dir = ( light_direction + view_direction );
	float3 half_vector = normalize( light_dir_plus_view_dir );
	
	float n_dot_h = dot( surface_normal, half_vector );
	
	float intensity = pow( saturate(n_dot_h), exponent );
	
	return saturate( intensity) * surface_colour * light_colour;
}

inline float3 CalculateSpecular_CookTorrance(	float3 view_direction,
												float3 light_direction,
												float3 light_colour,
												float3 surface_normal,
												float3 surface_colour,
												float surface_roughness )
{
	float3 vhalf = normalize( view_direction + light_direction );

	float normal_dot_half = saturate( dot( surface_normal, vhalf ) );
	float view_dot_half = saturate( dot( vhalf, view_direction ) );
	float normal_dot_view = saturate( dot( surface_normal, view_direction ) );
	float normal_dot_light = saturate( dot( surface_normal, light_direction ) );
	
	/*
		Geometry term
	*/
	float G1 = ( 2 * normal_dot_half * normal_dot_view ) / view_dot_half;
	float G2 = ( 2 * normal_dot_half * normal_dot_light ) / view_dot_half;
	float G = min( G1, G2 );
	
	/*
		Fresnel term
	*/
	float refractive_index = 4;	// TODO
	
	float R0_sqrt = ( 1 - refractive_index ) / ( 1 + refractive_index );
	float R0 = R0_sqrt * R0_sqrt;
	float F = R0 + ( 1 - R0 ) * pow( 1 - normal_dot_view, 5 );
		
	/*
		Beckmann distribution term
	*/
	float alpha = acos( normal_dot_half );
	float cos_alpha = cos( alpha );
	float tan_alpha = tan( alpha );
	float num = exp( - tan_alpha * tan_alpha / ( surface_roughness * surface_roughness ) );
	float denom = 3.141592 * surface_roughness * surface_roughness * cos_alpha * cos_alpha * cos_alpha * cos_alpha;
	float D = num / denom;
	
	float intensity = ( G * F * D ) * surface_roughness;// / ( dot( v, n ) * dot( l, n ) ); // 
	
	// 'GFD' should be divided by the dot products but it's far too bright.
	// roughness seems to scale the light appropriately.
	
	// Function needs improving and optimising.
	
	return saturate(intensity) * surface_colour * light_colour;
}

inline float3 CalculateDiffuse(	float3 view_direction,
								float3 light_direction,
								float3 light_colour,
								float3 surface_normal,
								float3 surface_colour,
								float surface_roughness )
{
#ifdef DIFFUSE_LDOTN
	return CalculateDiffuse_LDotN(	view_direction,
									light_direction,
									light_colour,
									surface_normal,
									surface_colour,
									surface_roughness );
#endif
#ifdef DIFFUSE_ORENNAYAR
	return CalculateDiffuse_OrenNayar(	view_direction,
										light_direction,
										light_colour,
										surface_normal,
										surface_colour,
										surface_roughness );
#else
	return float3( 0, 1, 0.5 );
#endif
}

inline float3 CalculateSpecular(	float3 view_direction,
									float3 light_direction,
									float3 light_colour,
									float3 surface_normal,
									float3 surface_colour,
									float surface_roughness )
{
#ifdef SPECULAR_BLINNPHONG
	return CalculateSpecular_BlinnPhong(	view_direction,
											light_direction,
											light_colour,
											surface_normal,
											surface_colour,
											surface_roughness );
#endif
#ifdef SPECULAR_COOKTORRANCE
	return CalculateSpecular_CookTorrance(	view_direction,
											light_direction,
											light_colour,
											surface_normal,
											surface_colour,
											surface_roughness );
#endif
}

