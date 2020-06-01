#pragma once
#include "Vector.h"

namespace vnaon_geometry {

	class Rect : public geoObject{
	
	public:
		double left;
		double top;
		double right;
		double bottom;

	public:
		Rect();
		Rect(const Vector &lt, const Vector &rb);
		Rect(const double &l, const double &t, const double &r, const double &b);
		~Rect();

	public:
		static double width(const Rect &rect);
		static double height(const Rect &rect);
		static void setEmpty(Rect &rect);
		static Vector leftTop(const Rect &rect);
		static Vector rightBottom(const Rect &rect);
	
	};

}