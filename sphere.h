#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class ray;

class sphere : public hittable {
public:
	sphere(point3 cen, double r, std::shared_ptr<material> m);

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 center;
	double radius;
	std::shared_ptr<material> mat_ptr;
};


#endif