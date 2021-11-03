#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

class camera {
public:
	camera(double viewport_height, double viewport_width, double focal_length);

	ray get_ray(double u, double v) const;

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};
#endif