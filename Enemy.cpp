#include<Novice.h>

#include"Matrix3x3.h"
#include"Function.h"

#include"Enemy.h"

Enemy::Enemy(float posX, float posY) {
	Init(posX,posY);
	


	texture_.Handle = Novice::LoadTexture("white1x1.png");
}

void Enemy::Init(float posX, float posY) {
	//座標
	worldPos_ = {posX,posY};
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

	theta_ = 0.0f;
	isDeath_ = false;
}

void Enemy::Update() {

	matrix_ = MakeAffineMatrix(scale_, 0, worldPos_);
	wvMatrix_ = Multiply(matrix_, camela_->GetViewMatrix());

}

void Enemy::Draw() {

	screenPos_ = Transform(localVertex_, wvMatrix_);

	newDrawQuad(screenPos_, 0, 0, size_.x, size_.y, texture_.Handle, GREEN);


}