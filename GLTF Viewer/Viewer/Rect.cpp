#include<cmath>
#include "Rect.h"

namespace vNaonGeometry {

	Rect::Rect()
		: left(0.0), top(0.0), right(0.0), bottom(0.0) {
		this->type = GEO_TYPE::GEO_RECT;
	}

	Rect::Rect(const Vector &lt, const Vector &rb) 
		: left(lt.x), top(lt.y), right(rb.x), bottom(rb.y){
		this->type = GEO_TYPE::GEO_RECT;
	}

	Rect::Rect(const double &l, const double &t, const double &r, const double &b)
		: left(l), top(t), right(r), bottom(b) {
		this->type = GEO_TYPE::GEO_RECT;
	}

	Rect::~Rect() {
	}

	double Rect::width(const Rect &rect) {
		return std::abs(rect.right - rect.left);
	}

	double Rect::height(const Rect &rect) {
		return std::abs(rect.top - rect.bottom);
	}

	void Rect::setEmpty(Rect &rect) {
		rect.left = rect.top = rect.right = rect.bottom = 0.0;
	}

	Vector Rect::leftTop(const Rect &rect) {
		return Vector(rect.left, rect.top, 0.0);
	}

	Vector Rect::rightBottom(const Rect &rect) {
		return Vector(rect.right, rect.bottom, 0.0);
	}

}