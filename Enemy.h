#pragma once

#include"struct.h"

#include"Creature.h"
#include"camelaMatrix.h"

class Enemy :public Creature {

private:

	Camela* camela_;
	Matrix3x3 wvMatrix_;

	GH texture_;

public:

	Enemy(float posX,float posY);

	void Init(float posX, float posY);
	void Update();
	void Draw();

	void SetCamela(Camela* camela) { camela_ = camela; }
};
