#pragma once

#include"Creature.h"

//class
#include"mapchip.h"
#include"camelaMatrix.h"

class Player:public Creature {

private:

	Mapchip* mapchip_;
	Camela* camela_;

	//座標
	Vertex screenVertex_;
	Vector2 scrollPos_;
	
	//Matrix3x3
	Matrix3x3 wvpVpMatrix_;

	//イージング
	Easing move_;
	Easing wait_;
	Easing jump_;
	Easing landing_;

	Easing warp_;

	//状態
	bool isFlight_;
	bool isStartBlockColligion_;

	//武器
	


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
	void Update(char* keys,char*preKeys);
	void Draw();

	//プレイヤーの動き、当たり判定
	void Move(char* keys);
	void ColligionMapChip();

	//プレイヤーのモーション
	void MoveMotion(char* keys);
	void WaitMotion(char* keys);
	void JumpMotion();
	void LandingMotion();

	//ゲーム開始
	void GameStart(char* keys, char* preKeys);

	void SetCamelaMatrix(Camela* camelamatrix) { camela_ = camelamatrix; }
};