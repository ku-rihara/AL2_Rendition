#pragma once

#include"Creature.h"

//class
#include"mapchip.h"
#include"camelaMatrix.h"

class Player:public Creature {

private:

	Mapchip* mapchip_;
	CamelaMatrix* camelaMatrix_;


	//Pos
	Vertex screenVertex_;
	Vector2 scrollPos_;
	

	//Matrix3x3
	Matrix3x3 wvpVpMatrix_;

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

	void Move(char* keys);
	void ColligionMapChip();

	void SetCamelaMatrix(CamelaMatrix* camelamatrix) { camelaMatrix_ = camelamatrix; }


};