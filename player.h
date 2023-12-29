#pragma once

#include"Creature.h"

//class
#include"mapchip.h"
#include"camelaMatrix.h"
#include"Weapon.h"


class Player:public Creature {

private:

	Mapchip* mapchip_;
	Camela* camela_;
	Weapon* weapon_;

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
	bool isStart_;

	//武器
	float shakeTime_;
	bool isShake_;
	int randX_;
	int randY_;
	
	
	//効果音・画像
	SE jumpSE_;
	GH leftTexture_;
	GH rightTexture_;
	GH arrow_;

	
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

	void SetWeapon(Weapon* weapon) { weapon_ = weapon; }
};