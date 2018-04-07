#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

typedef struct {
	float top;
	float bottom;
	float left;
	float right;
}BoudingBox;

BoudingBox makeBB(float top, float bottom, float left, float right);
#endif // !BOUNDING_BOX_H
