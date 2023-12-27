﻿#pragma once

#include"Creature.h"

//class
#include"mapchip.h"
#include"camelaMatrix.h"

class Player:public Creature {

private:

	Mapchip* mapchip_;
	CamelaMatrix* camelaMatrix_;


	//座標
	Vertex screenVertex_;
	Vector2 scrollPos_;
	
	//Matrix3x3
	Matrix3x3 wvpVpMatrix_;

	//イージング
	

	bool isFlight_;


	//効果音・画像
	SE jumpSE_;
	GH leftTexture_;
	GH rightTexture_;

	//向き
	enum DIRECTION {
		LEFT,
		RIGHT,
	};
	DIRECTION direction_;

public:

	Player();

	void Init();
	void Update(char* keys);
	void Draw();

	//プレイヤーの動き、当たり判定
	void Move(char* keys);
	void ColligionMapChip();

	//プレイヤーのモーション
	void MoveMotion();
	void JumpMotion();
	void StopMotion();
	void LandingMotion();

	void SetCamelaMatrix(CamelaMatrix* camelamatrix) { camelaMatrix_ = camelamatrix; }


};