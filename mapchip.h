﻿#pragma once

#include"struct.h"

//class
#include"camelaMatrix.h"

//ウィンドウサイズ
const int kWindowSizeX = 1280;
const int kWindowSizeY = 720;

//map
/*1 2 3
  4 5 6
  7 8 9*/

//const int mapDelimitX = 35;
//const int mapDelimitY = 35;

const int mapxMax = 57;
const int mapyMax = 30;

//ブロックのタイプ
enum BlockType {
	NONE,//0
	BLOCK,//1
	START,//2

};

//マップチップクラス
class Mapchip {
private:

	Camela* camelaMatrix_;

	//pos
	Vector2 scrollPos_;
	Vector2 pos_[mapyMax][mapxMax];
	Vector2 scale_;

	//Matrix&Vertex
	Matrix3x3 matrix_[mapyMax][mapxMax];
	Matrix3x3 wvMatrix_[mapyMax][mapxMax];
	Vertex ScreenVertex_[mapyMax][mapxMax];
	Vertex localVertex_;

	//size,texture
	float size_;
	GH mapTexture;
	
public:

	//map
	BlockType map[mapyMax][mapxMax];

	Mapchip();
	void fileLoad();

	void Init();
	void Update();
	void Draw();

	//setter
	void SetCamelaMatrix(Camela* camelamatrix) { camelaMatrix_ = camelamatrix; }
	void SetScrollPosX(float scrollPosX) { this->scrollPos_.x = scrollPosX; }

	//getter
	Vector2 GetScrollPos() const { return scrollPos_; }
	float GetMapchipSize()const { return size_; }

	Vector2 getPos(int x,int y)const { return pos_[y][x]; }
};

