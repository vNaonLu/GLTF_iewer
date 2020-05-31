#pragma once
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "Geometry.h"

namespace vNaonGeometry {

	class Vector : public geoObject{
		typedef glm::dvec3 _vec;
	
	public:
		double x, y, z;

	public:
		Vector();
		Vector(const _vec &other);
		Vector(const double &x, const double &y, const double &z);
		~Vector();

		Vector operator+ (const Vector &other) const;
		Vector operator+ (const _vec &other) const;
		Vector operator- (const Vector &other) const;
		Vector operator- (const _vec &other) const;
		Vector operator* (const double &value) const;
		Vector operator/ (const double &value) const;

		Vector &operator+= (const Vector &other);
		Vector &operator+= (const _vec &other);
		Vector &operator-= (const Vector &other);
		Vector &operator-= (const _vec &other);
		Vector &operator*= (const double &value);
		Vector &operator/= (const double &value);

	public:
		static double length(const Vector &v);
		static Vector &normalize(Vector &v);
		static void transform(const Vector &v, _vec &out);

	};

}