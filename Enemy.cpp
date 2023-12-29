#include<Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include"Matrix3x3.h"
#include"Function.h"

#include"Enemy.h"

Enemy::Enemy(float posX, float posY) {
	Init(posX, posY);

	srand(unsigned int(time(nullptr)));

	deathBlock_.Handle = Novice::LoadTexture("white1x1.png");
	texture_.Handle = Novice::LoadTexture("./Resources/enemy.png");
}

void Enemy::Init(float posX, float posY) {
	//座標
	worldPos_ = { posX,posY };
	oldWorldPos_ = {};
	fitMapsizePos_ = {};

	//速度、加速度
	velocity_ = {};
	acceleration_ = {};

	//matrix
	matrix_ = {};
	wvMatrix_ = {};

	//スケールとサイズ
	scale_ = { 1.0f,1.0f };
	size_ = { 48.0f,48.0f };

	vertexPos_ = {};

	//ローカル座標系
	localVertex_ = {
		{48.0f,48.0f},
		{48.0f,48.0f},
		{48.0f,48.0f},
		{48.0f,48.0f},
	};
	//ローカル座標の保存用
	localVertexSave_ = {
		{48.0f,48.0f},
		{48.0f,48.0f},
		{48.0f,48.0f},
		{48.0f,48.0f},
	};

	particleLocal_ = {
		{16,16},
		{16,16},
		{16,16},
		{16,16},
	};

	theta_ = 0.0f;
	isDeath_ = false;

	for (int i = 0; i < 20; i++) {
		particle_[i] = {};
		 partceMatrix_[i] = {};
		 partclewvMatrix_[i] = {};
		 particleScreen_[i] = {};
	}
	emitter_ = {};
	isParticle_ = false;
}

void Enemy::Update() {

	Burst();

	matrix_ = MakeAffineMatrix(scale_, 0, worldPos_);
	wvMatrix_ = Multiply(matrix_, camela_->GetViewMatrix());

	for (int i = 0; i < 20; i++) {

		partceMatrix_[i] = MakeAffineMatrix(scale_, particle_[i].theta, particle_[i].Pos);
		partclewvMatrix_[i] = Multiply(partceMatrix_[i], camela_->GetViewMatrix());

	}

}

void Enemy::Draw() {


	screenPos_ = Transform(localVertex_, wvMatrix_);
	if (isDeath_ == false) {
		newDrawQuad(screenPos_, 0, 0, size_.x, size_.y, texture_.Handle, WHITE);
	}

	for (int i = 0; i < 20; i++) {
		particleScreen_[i] = Transform(particleLocal_, partclewvMatrix_[i]);
		newDrawQuad(particleScreen_[i], 0, 0, 16, 16, deathBlock_.Handle, GREEN);
	}

}

void Enemy::Burst() {

	if (isDeath_ == true && isParticle_ == false) {
		isParticle_ = true;
	}

	if (isParticle_ == true) {
		for (int i = 0; i < 20; i++) {

			if (particle_[i].isStart == false) {

				emitter_.spownPos.x = worldPos_.x;
				emitter_.spownPos.y = worldPos_.y;

				emitter_.direction = (float(i) / (20)) * float(M_PI);

				emitter_.velocity.x = float(rand() % 6 + 10);
				emitter_.velocity.y = float(rand() % 6 + -10);

				particle_[i].Pos.x = emitter_.spownPos.x;
				particle_[i].Pos.y = emitter_.spownPos.y;

				particle_[i].direction.x = cosf(-emitter_.direction);

				particle_[i].velocity.x = emitter_.velocity.x;
				particle_[i].velocity.y = emitter_.velocity.y;

				particle_[i].isStart = true;

			}
		}

		for (int i = 0; i < 20; i++) {

			if (particle_[i].isStart == true) {

				particle_[i].Pos.x += particle_[i].velocity.x * particle_[i].direction.x;
				particle_[i].Pos.y += particle_[i].velocity.y;

				particle_[i].velocity.y += 0.8f;

				particle_[i].theta+=0.4f;
			}

		}

	}
}
