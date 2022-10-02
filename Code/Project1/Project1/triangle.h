#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "rtweekend.h"

#include "hittable.h"
#include<cmath>


class triangle : public hittable {
public:
	triangle() {}

	triangle(point3 in_a, point3 in_b, point3 in_c, shared_ptr<material> m)
		: a(in_a), b(in_b), c(in_c), mat_ptr(m) {};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 a;
	point3 b;
	point3 c;
	shared_ptr<material> mat_ptr;

};


bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	
	const auto epsilon = 1e-8;
	double u, v, t;
	vec3 ab = b - a;
	vec3 ac = c - a;

	vec3 cross_dirr_ac = cross(r.direction(), ac);
	double det = (dot(ab, cross_dirr_ac));

	
	if (det < 0) {
		return false;
	
	}

	if (det < epsilon && det>-epsilon) {
		return false;

	}
	
	double invers_det = 1 / det;

	vec3 t_vec = r.origin() - a;
	u = dot(t_vec, cross_dirr_ac) * invers_det;
	if (u < 0.0 || u>1.0)return false;

	vec3 v_vec = cross(t_vec, ab);
	v = dot(r.direction(), v_vec)*invers_det;
	if (v < 0.0 || v+u>1.0)return false;

	t = dot(ac, v_vec) * invers_det;

	if(t>epsilon){

		rec.t = t;
		rec.p = r.origin()+t*r.direction();
		rec.normal = unit_vector(cross(ab, ac));
		rec.mat_ptr = mat_ptr;
	
		return true;
	}

	else {
		return false;
	}
	

}


#endif#pragma once
