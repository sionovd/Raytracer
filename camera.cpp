#include "camera.h"

camera::camera(double viewport_height, double viewport_width, double focal_length) :
	origin{ point3(0,0,0) },
	horizontal{ vec3(viewport_width, 0, 0) },
	vertical{ vec3(0, viewport_height, 0) }
{
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
}

ray camera::get_ray(double u, double v) const {
	return ray{ origin, lower_left_corner + u * horizontal + v * vertical - origin };
}