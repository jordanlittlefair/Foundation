/*
	A function to get a point on a bezier curve.
	
	Used for light falloff.
*/

inline float BezierInterpolate( float4 p, float s )
{
	const float S = min( max( s, 0.0f ), 1.0f );

	return
	( ( ( 1.0f - S ) * ( 1.0f - S ) * ( 1.0f - S ) ) * p.x ) +
	( ( ( 3.0f * S ) * ( 1.0f - S ) * ( 1.0f - S ) ) * p.y ) +
	( ( S * S * 3.0f * ( 1.0f - S ) )				 * p.z ) +
	( ( S * S * S )							         * p.w );
}



/*
	Functions used to calculate falloff for lights.
*/

inline float DistanceFalloff(	float distance,
								float range,
								float falloff_start,
								float4 control_points )
{			
	const float distance_percent = saturate( distance / range );
	
	const float falloff_param = saturate( ( distance_percent - falloff_start ) / ( 1 - falloff_start ) );
	
	const float distance_falloff = saturate( BezierInterpolate( control_points, falloff_param ) );
	
	return distance_falloff;
}

inline float AngularFalloff(	float fov,
								float3 centre_direction,
								float3 direction,
								float falloff_start,
								float4 control_points )
{
	const float angular_range = saturate( 1 - cos( fov / 2 ) );
	
	const float angular_percent = saturate( ( 1 - dot( centre_direction, direction ) ) / angular_range );
	
	const float angular_falloff_param = saturate( ( angular_percent - ( falloff_start -0.01) ) / ( 1 - ( falloff_start -0.01 ) ) );
	
	const float angular_falloff = saturate( BezierInterpolate( control_points, angular_falloff_param ) );
	
	return angular_falloff;
}