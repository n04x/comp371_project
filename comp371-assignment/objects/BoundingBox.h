#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

typedef struct {
	float far;
	float near;
	float left;
	float right;
}BoudingBox;


BoudingBox makeBB(float far, float near, float left, float right);
#endif // !BOUNDING_BOX_H
