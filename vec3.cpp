#include "vec3.h"
#include "utils.h"

vec3::vec3() : e{ 0,0,0 } {}
vec3::vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

vec3 vec3::operator-() const { return vec3{ -e[0], -e[1], -e[2] }; }
double vec3::operator[](int i) const { return e[i]; }
double& vec3::operator[](int i) { return e[i]; }

vec3& vec3::operator+=(const vec3& v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

vec3& vec3::operator*=(const double t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

vec3& vec3::operator/=(const double t) {
	return *this *= 1 / t;
}

double vec3::length() const {
	return std::sqrt(length_squared());
}

double vec3::length_squared() const {
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

bool vec3::near_zero() const {
	// Return true if the vector is close to zero in all dimensions.
	const auto s = 1e-8;
	return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

vec3 vec3::random(double min, double max) {
	return vec3{ random_double(min, max), random_double(min, max), random_double(min, max) };
}



// vec3 Utility Functions

std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

vec3 operator+(const vec3& u, const vec3& v) {
	return vec3{ u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2] };
}

vec3 operator-(const vec3& u, const vec3& v) {
	return vec3{ u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2] };
}

vec3 operator*(const vec3& u, const vec3& v) {
	return vec3{ u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2] };
}

vec3 operator*(double t, const vec3& v) {
	return vec3{ t * v.e[0], t * v.e[1], t * v.e[2] };
}

vec3 operator*(const vec3& v, double t) {
	return t * v;
}

vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

vec3 cross(const vec3& u, const vec3& v) {
	return vec3{ u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0] };
}

vec3 unit_vector(vec3 v) {
	return v / v.length();
}

vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal) {
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}