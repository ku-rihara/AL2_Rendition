#pragma once

#include"struct.h"

//class
#include"camelaMatrix.h"

class Weapon {
public:
	Camela* camela_;

	Vector2 worldPos_;
	Vector2 startPos_;
	Vector2 endPos_;

	Vector2 scale_;
	
	Vertex localVertex_;
	Vertex screenPos_;

	Matrix3x3 matrix_;
	Matrix3x3 wvMatrix_;

	Easing appearance_;

	//gun
	Vector2 gunWorldPos_;
	Vector2 gunDirection_;
	Vector2 gunScale_;

	Vertex gunLocalVertex_;
	Vertex gunScreenPos_;

	Matrix3x3 gunMatrix_;
	Matrix3x3 gunwvMatrix_;

	float theta_;
	bool isAppearance;

	bool isShot_;
	float gundirection;

	float coolTime_;

	DIRECTION direction_;

	GH leftTexture_;
	GH rightTexture_;
	GH gun_;

public:

	Weapon();

	void Init();
	void Update();
	void Draw();

	void Appearance();
	void Shot();

	//setter
	void SetCamelaMatrix(Camela* camela) { camela_ = camela; }
	void SetDirection(DIRECTION direction) { direction_ = direction; }

	void SetStartPosX(float x) { startPos_.x = x; }
	void SetStartPosY(float y) { startPos_.y = y; }
	void SetEndPosX(float x) { endPos_.x = x; }
	void SetEndPosY(float y) { endPos_.y = y; }
};
