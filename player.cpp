#include<Novice.h>
#include"Function.h"
#include"Matrix3x3.h"

//class
#include"player.h"

Player::Player() {
	Init();
	mapchip_ = new Mapchip;
	camelaMatrix_ = new CamelaMatrix;

	leftTexture_.Handle = Novice::LoadTexture("white1x1.png");
	rightTexture_.Handle = Novice::LoadTexture("white1x1.png");
}

void Player::Init() {

	//座標
	worldPos_ = { 72,160 };
	oldWorldPos_ = {};
	fitMapsizePos_ = {};
	screenVertex_ = {};
	scrollPos_ = {};

	//マップチップ
	centerMapNum_ = {};
	mapNum_ = {};
	oldMapNum_ = {};

	//速度、加速度
	velocity_ = {};
	acceleration_ = {};

	//matrix
	matrix_ = {};

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

	theta_ = 0.0f;
	direction_ = LEFT;

	isFlight_ = false;
	isDeath_ = false;

	//効果音
	jumpSE_ = {};
	jumpSE_.voiceHandle = -1;

}

void Player::Update(char* keys) {

	oldWorldPos_.x = worldPos_.x;
	oldWorldPos_.y = worldPos_.y;
	Move(keys);
	ColligionMapChip();

	const float LeftMost = 200.0f;
	const float RightMost = (mapchip_->GetMapchipSize() / 2) * mapxMax + LeftMost;
	const float BottomMost = 0.0f;
	const float TopMost = (mapchip_->GetMapchipSize() / 2) * mapyMax + BottomMost;

	//カメラの動き
	//X
	if (worldPos_.x >= LeftMost && worldPos_.x <= RightMost) {
		
		camelaMatrix_->SetPosX(worldPos_.x- LeftMost);
	}
	//スクロール範囲外はスクロールしない
	else {
		if (worldPos_.x <= LeftMost) {
			camelaMatrix_->SetPosX(0);
		}

		if (worldPos_.x >= RightMost) {
			camelaMatrix_->SetPosX(RightMost);
		}
	}
	//Y
	if (worldPos_.y >= BottomMost && worldPos_.y <= TopMost) {
		
		camelaMatrix_->SetPosY(worldPos_.y);
	}
	//スクロール範囲外はスクロールしない
	else {
		if (worldPos_.y <= BottomMost) {
			camelaMatrix_->SetPosY(BottomMost);
		}

		if (worldPos_.y >= TopMost) {
			camelaMatrix_->SetPosY(TopMost);
		}

	}
	//カメラ行列、プレイヤーの行列の作成
		camelaMatrix_->MakeCamelaMatrix();
	matrix_ = MakeAffineMatrix(scale_, 0, worldPos_);
}

void Player::Draw() {

	wvpVpMatrix_ = wvpVpMatrix(matrix_, camelaMatrix_->GetViewMatrix(), camelaMatrix_->GetOrthoMatrix(), camelaMatrix_->GetViewportMatrix());
	screenVertex_ = Transform(localVertex_, wvpVpMatrix_);

	if (direction_ == LEFT) {
		newDrawQuad(screenVertex_, 0, 0, 48, 48, leftTexture_.Handle, RED);
	}

	else if (direction_ == RIGHT) {
		newDrawQuad(screenVertex_, 0, 0, 48, 48, rightTexture_.Handle, RED);

	}

	Novice::ScreenPrintf(100, 100, "%f", worldPos_.x);
	Novice::ScreenPrintf(100, 120, "%f", worldPos_.y);

	Novice::ScreenPrintf(100, 150, "%f", screenVertex_.LeftTop.x);
	Novice::ScreenPrintf(100, 170, "%f", camelaMatrix_->GetPos().x);
}

void Player::Move(char* keys) {

	if (keys[DIK_D]) {
		velocity_.x = 4;
		direction_ = LEFT;
	}

	else if (keys[DIK_A]) {
		velocity_.x = -4;
		direction_ = RIGHT;
	}
	if (isFlight_ == false) {

		acceleration_.y = 0;
		velocity_.y = 0;

		if (keys[DIK_W]) {
			velocity_.y = 15;
			isFlight_ = true;
			jumpSE_.isStart = true;
		}
	}

	if (isFlight_ == true) {
		acceleration_.y = -0.8f;
	}

	if (velocity_.y >= -16.0f) {
		acceleration_.y = 0;
	}

	velocity_.y += acceleration_.y;

	if (keys[DIK_A] || keys[DIK_D]) {
		worldPos_.x += velocity_.x;
	}
	worldPos_.y += velocity_.y;
}

void Player::ColligionMapChip() {

	//マップ間の隙間を埋める
	fitMapsizePos_ = fitMapSize(worldPos_, oldWorldPos_, mapchip_->GetMapchipSize());

	//マップ番号の計算
	mapNum_.LeftTop = LeftTopMapNum(worldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
	mapNum_.RightTop = RightTopMapNum(worldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
	mapNum_.LeftBottom = LeftBottomMapNum(worldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
	mapNum_.RightBottom = RightBottomMapNum(worldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
	centerMapNum_.x = worldPos_.x / mapchip_->GetMapchipSize();
	centerMapNum_.y = worldPos_.y / mapchip_->GetMapchipSize();

	//オールド座標のマップ番号
	oldMapNum_.LeftTop = LeftTopMapNum(oldWorldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
	oldMapNum_.RightTop = RightTopMapNum(oldWorldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
	oldMapNum_.LeftBottom = LeftBottomMapNum(oldWorldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
	oldMapNum_.RightBottom = RightBottomMapNum(oldWorldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());

	//自機の４頂点のどれかが当たっている時
	if (mapchip_->map[int(mapNum_.RightTop.y)][int(mapNum_.RightTop.x)] != NONE || mapchip_->map[int(mapNum_.RightBottom.y)][int(mapNum_.RightBottom.x)] != NONE ||
		mapchip_->map[int(mapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] != NONE || mapchip_->map[int(mapNum_.LeftBottom.y)][int(mapNum_.LeftBottom.x)] != NONE) {

		//Y方向
		if (mapchip_->map[int(oldMapNum_.RightTop.y)][int(mapNum_.RightTop.x)] == NONE && mapchip_->map[int(oldMapNum_.RightBottom.y)][int(mapNum_.RightBottom.x)] == NONE &&
			mapchip_->map[int(oldMapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] == NONE && mapchip_->map[int(oldMapNum_.LeftBottom.y)][int(mapNum_.LeftBottom.x)] == NONE) {

			//縦の斜め移動時にマップとの隙間を埋める
			worldPos_.y = float(fitMapsizePos_.inty);

			//仮に埋まってしまったらプレイヤーの半径分戻す
			if (mapchip_->map[int(centerMapNum_.y)][int(centerMapNum_.x)] == BLOCK) {
				worldPos_.y -= size_.y / 2;
			}


			//地面についていたら浮いている状態のフラグを降ろす
			if (mapchip_->map[int(mapNum_.LeftBottom.y)][int(mapNum_.LeftBottom.x)] == BLOCK || mapchip_->map[int(mapNum_.RightBottom.y)][int(mapNum_.RightBottom.x)] == BLOCK) {

				isFlight_ = false;
			}
			else {
				isFlight_ = true;

			}

			//上にぶつかったら加速度と速度を0にする
			if (mapchip_->map[int(mapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] == BLOCK || mapchip_->map[int(mapNum_.RightTop.y)][int(mapNum_.RightTop.x)] == BLOCK) {
				velocity_.y = 0;

			}
		}

		//X方向
		else if (mapchip_->map[int(mapNum_.RightTop.y)][int(oldMapNum_.RightTop.x)] == NONE && mapchip_->map[int(mapNum_.RightBottom.y)][int(oldMapNum_.RightBottom.x)] == NONE &&
			mapchip_->map[int(mapNum_.LeftTop.y)][int(oldMapNum_.LeftTop.x)] == NONE && mapchip_->map[int(mapNum_.LeftBottom.y)][int(oldMapNum_.LeftBottom.x)] == NONE) {

			//横の斜め移動時にマップとの隙間を埋める
			worldPos_.x = float(fitMapsizePos_.intx);
		}

		else {
			worldPos_.x = float(fitMapsizePos_.intx);
			worldPos_.y = float(fitMapsizePos_.inty);

			//仮に埋まってしまったらプレイヤーの半径分戻す
			if (mapchip_->map[int(centerMapNum_.y)][int(centerMapNum_.x)] == BLOCK) {
				worldPos_.y -= size_.y / 2;
			}

			//地面についていたら浮いている状態のフラグを降ろす
			if (mapchip_->map[int(mapNum_.LeftBottom.y)][int(mapNum_.LeftBottom.x)] == BLOCK || mapchip_->map[int(mapNum_.RightBottom.y)][int(mapNum_.RightBottom.x)] == BLOCK) {

				isFlight_ = false;
			}

			else {
				isFlight_ = true;

			}
			//上にぶつかったら加速度と速度を0にする
			if (mapchip_->map[int(mapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] == BLOCK || mapchip_->map[int(mapNum_.RightTop.y)][int(mapNum_.RightTop.x)] == BLOCK) {
				velocity_.y = 0;

			}
		}
	}
	else {
		isFlight_ = true;
	}


}