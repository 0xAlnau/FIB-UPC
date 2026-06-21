float getHeight(vec2 p)
{
	float s1 = sin(time + 10.0 * p.x) * cos(time + 10.0 * p.y);
	float s2 = sin(-2.4*time + 27.0 * p.x) * cos(2.7 * time + 35.0 * p.y);
	float s3 = sin(2.2 * time + 66.0 * p.x) * cos(2.0 * time + 60.0 * p.y);
	return 0.04 * (s1 + s2*0.3 + s3*0.05);
}


vec2 getHeightDerivative(vec2 p)
{
	vec2 ds1 = vec2(cos(time + 10.0 * p.x) * cos(time + 10.0 * p.y) * 10.0,
			        -sin(time + 10.0 * p.x) * sin(time + 10.0 * p.y) * 10.0);
	vec2 ds2 = vec2(cos(-2.4*time + 27.0 * p.x) * cos(2.7 * time + 35.0 * p.y) * 27.0,
					-sin(-2.4*time + 27.0 * p.x) * sin(2.7 * time + 35.0 * p.y) * 35.0);
	vec2 ds3 = vec2(cos(2.2 * time + 66.0 * p.x) * cos(2.0 * time + 60.0 * p.y) * 66.0,
					-sin(2.2 * time + 66.0 * p.x) * cos(2.0 * time + 60.0 * p.y) * 60.0);

	return 0.04 * (ds1 + ds2*0.3 + ds3*0.05);
}