#pragma once

#include"struct.h"

#include"Creature.h"
#include"camelaMatrix.h"

class Enemy :public Creature {

private:

	Camela* camela_;
	Matrix3x3 wvMatrix_;

	GH texture_;

	Particle particle_[20];
	Emitter  emitter_;
	bool isParticle_;

	Matrix3x3 partceMatrix_[20];
	Matrix3x3 partclewvMatrix_[20];
	Vertex particleScreen_[20];
	Vertex particleLocal_;

	GH deathBlock_;

public:

	Enemy(float posX,float posY);

	void Init(float posX, float posY);
	void Update();
	void Draw();
	void Burst();

	void SetCamela(Camela* camela) { camela_ = camela; }
};
