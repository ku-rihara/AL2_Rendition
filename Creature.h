#pragma once

#include"struct.h"

class Creature {
public:

	//Pos
	Vector2 worldPos_;
	Vector2 oldWorldPos_;
	Vector2 maxPos_;
	Vertex screenPos_;
	Vector2i fitMapsizePos_;

	//Mapnum
	Vector2 centerMapNum_;
	Vertex mapNum_;
	Vertex oldMapNum_;

	//Vertex
	Vertex vertexPos_;
	Vertex localVertex_;
	Matrix3x3 matrix_;
	float theta_;

	//Parameter
	Vector2 velocity_;
	Vector2 acceleration_;
	Vector2 scale_;
	Vector2 size_;

	bool isDeath_;
};