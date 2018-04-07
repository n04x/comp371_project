#include "BoundingBox.h"

BoudingBox makeBB(float top, float bottom, float left, float right) {
	BoudingBox bounding_box;
	bounding_box.top = top;
	bounding_box.bottom = bottom;
	bounding_box.left = left;
	bounding_box.right = right;

	return bounding_box;
}
