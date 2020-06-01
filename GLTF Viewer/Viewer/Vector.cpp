#include <cmath>
#include "Vector.h"

namespace vnaon_geometry {

	Vector::Vector()
		:x(0.0), y(0.0), z(0.0) {
		this->type = GEO_TYPE::GEO_POINT;
	}

	Vector::Vector(const _vec &other)
		: x(other.x), y(other.y), z(other.z) {
		this->type = GEO_TYPE::GEO_POINT;
	}

	Vector::Vector(const double &x, const double &y, const double &z)
		: x(x), y(y), z(z) {
		this->type = GEO_TYPE::GEO_POINT;
	}

	Vector::~Vector() {
	}

	Vector Vector::operator+(const Vector &other) const {
		return Vector(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector Vector::operator+(const _vec &other) const {
		return Vector(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector Vector::operator-(const Vector &other) const {
		return Vector(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector Vector::operator-(const _vec &other) const {
		return Vector(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector Vector::operator*(const double &value) const {
		return Vector(this->x * value, this->y * value, this->z * value);
	}

	Vector Vector::operator/(const double &value) const {
		return Vector(this->x / value, this->y / value, this->z / value);
	}

	Vector &Vector::operator+=(const Vector &other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vector &Vector::operator+=(const _vec &other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vector &Vector::operator-=(const Vector &other) {
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vector &Vector::operator-=(const _vec &other) {
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vector &Vector::operator*=(const double &value) {
		this->x *= value;
		this->y *= value;
		this->z *= value;
		return *this;
	}

	Vector &Vector::operator/=(const double &value) {
		this->x /= value;
		this->y /= value;
		this->z /= value;
		return *this;
	}

	double Vector::length(const Vector &v) {
		return std::sqrt(v.x + v.x + v.y * v.y + v.z * v.z);
	}

	Vector &Vector::normalize(Vector &v) {
		return v /= length(v);
	}

	void Vector::transform(const Vector &v, _vec &out) {
		out = _vec(v.x, v.y, v.z);
	}

}