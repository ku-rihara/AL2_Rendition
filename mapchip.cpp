#include <Novice.h>
#include <stdio.h>

#include"Matrix3x3.h"
#include"Function.h"

#include"mapchip.h"


Mapchip::Mapchip() {
	Init();
	fileLoad();
	camelaMatrix_ = new CamelaMatrix;


	mapTexture.Handle = Novice::LoadTexture("white1x1.png");//マップ画像
}

void Mapchip::Init() {
	size_ = 48;
	scale_ = { 1,1 };
	scrollPos_ = { 0,0 };

	localVertex_ = {
		{48.0f,48.0f},
		{48.0f,48.0f},
		{48.0f,48.0f},
		{48.0f,48.0f},
	};


	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			pos_[y][x] = {};
			matrix_[y][x] = {};
		}
	}
}

void Mapchip::fileLoad() {

	FILE* fp = NULL;

	if (fopen_s(&fp, "./Resources/map1.csv", "rt") != 0) {
		return;
	}
	int numRects = 0;

	while (numRects < mapxMax * mapyMax && fscanf_s(fp, "%d,", &map[numRects / mapxMax][numRects % mapxMax]) != EOF) {
		++numRects;
	}

	fclose(fp);

	//char filePath[256];
	//for (int num = 1; num < 2; num++) {
	//	sprintf_s(filePath, "./Resources/map%d.csv", num);

	//	FILE* fp = NULL;
	//	fopen_s(&fp, filePath, "rt");
	//	if (fp == NULL) {
	//		return;
	//	}

	//	//マップ1の読み込み
	//	
	//		for (int row = 0; row < mapDelimitY; row++) {
	//			for (int column = 0; column < mapxMax; column++) {
	//				fscanf_s(fp, "%d,", &map[row][column]);
	//			}
	//		}
	//	

	//	////マップ2の読み込み
	//	//if (num == 2) {
	//	//	for (int row = 0; row < mapDelimitY; row++) {
	//	//		for (int column = 35; column < 70; column++) {
	//	//			fscanf_s(fp, "%d,", &map[row][column]);
	//	//		}
	//	//	}
	//	//}
	//	fclose(fp);
	//}
}

void Mapchip::Update() {

	//マップのスクロール
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			pos_[y][x].x = float(x * size_) + (size_ / 2);
			pos_[y][x].y = float(y * size_) + (size_ / 2);

			//マップチップ行列の作成
			matrix_[y][x] = MakeAffineMatrix(scale_, 0, pos_[y][x]);
			wvMatrix_[y][x] = Multiply(matrix_[y][x], camelaMatrix_->GetViewMatrix());
		}
	}
}


void Mapchip::Draw() {

	//スクロール座標の取得
	scrollPos_ = camelaMatrix_->GetPos();

	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			//スクリーンに変換＆描画
			ScreenVertex_[y][x] = Transform(localVertex_, wvMatrix_[y][x]);

			if (pos_[y][x].x - scrollPos_.x >= -size_ && pos_[y][x].x - scrollPos_.x <= kWindowSizeX + size_) {
				if (map[y][x] == BLOCK) {
					newDrawQuad(ScreenVertex_[y][x], 0, 0, size_, size_, mapTexture.Handle, WHITE);
				}
			}
		}
	}

	Novice::ScreenPrintf(600, 200,"%f", pos_[1][17].x);
}