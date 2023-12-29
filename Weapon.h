#pragma once

#include"struct.h"

//class
#include"camelaMatrix.h"

class Weapon {
public:
	Camela* camela_;

	Vector2 worldPos_;
	Vector2 scale_;
	
	Vertex localVertex_;
	Vertex screenPos_;

	Matrix3x3 matrix_;
	Matrix3x3 wvpVpMatrix_;

	Easing scaleUp;

	float theta_;

	GH leftTexture_;
	GH rightTexture_;

public:

	Weapon();

	void Init();
	void Update();
	void Draw();

	void SetCamela(Camela* camela) { camela_ = camela; }

};
