#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

class camera {
public:
	camera(
		point3 lookfrom,
		point3 lookat,
		vec3 vup,
		double vfov,
		double aspect_ratio);

	ray get_ray(double x, double y) const;

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};
#endif