#include "Geometry.h"

namespace vnaon_geometry {

	// interface of geometry.
	geoObject::geoObject() {
		this->type = GEO_TYPE::GEO_UNDEFINED;
	}

	geoObject::~geoObject() {
	}

	GEO_TYPE geoObject::getType() const {
		return GEO_TYPE::GEO_UNDEFINED;
	}

}