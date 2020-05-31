#pragma once

namespace vNaonGeometry {
	/* Geometry Title */

	enum class GEO_TYPE {
		GEO_UNDEFINED, GEO_POINT, GEO_RECT
	};

	class geoObject {
	
	public:
		GEO_TYPE type;

	public:
		geoObject();
		~geoObject();

		GEO_TYPE getType() const;
	
	};
}