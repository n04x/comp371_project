#include "BoundingBox.h"
BoudingBox makeBB(float far, float near, float left, float right) {
	BoudingBox bounding_box;
	bounding_box.far = far;
	bounding_box.near = near;
	bounding_box.left = left;
	bounding_box.right = right;

	return bounding_box;
}
