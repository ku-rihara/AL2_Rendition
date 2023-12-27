#include<Novice.h>

//function
#include"Function.h"
#include"Matrix3x3.h"
#include"Easing.h"

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
	worldPos_ = { 48*53,48*53 };
	oldWorldPos_ = {};
	fitMapsizePos_ = {};
	screenVertex_ = {};
	scrollPos_ = {};
	maxPos_ = {};

	//マップチップ
	centerMapNum_ = {};
	mapNum_ = {};
	oldMapNum_ = {};

	//速度、加速度
	velocity_ = {};
	acceleration_ = {};

	//matrix
	matrix_ = {};

	//イージング
	move_ = {};
	wait_ = {};
	jump_ = {};
	landing_ = {};

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
	direction_ = LEFT;

	isFlight_ = true;
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

	//スクロール範囲の制限
	const float LeftMost = 480.0f * camelaMatrix_->GetZoomLevel().x;
	const float RightMost = (mapchip_->GetMapchipSize()) * mapxMax - (LeftMost * 2);
	const float TopMost = 432.0f * camelaMatrix_->GetZoomLevel().y;
	const float BottomMost = (mapchip_->GetMapchipSize()) *mapyMax-(TopMost*2);

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
			camelaMatrix_->SetPosX(RightMost- LeftMost);
		}
	}
	//Y
	if (worldPos_.y >= TopMost && worldPos_.y <= BottomMost) {
		
		camelaMatrix_->SetPosY(worldPos_.y-TopMost);
	}
	//スクロール範囲外はスクロールしない
	else {
		if (worldPos_.y <= TopMost) {
			camelaMatrix_->SetPosY(0);
		}

		if (worldPos_.y >= BottomMost) {
			camelaMatrix_->SetPosY(BottomMost - TopMost);
		}
	}
	
	//プレイヤーのモーション
	MoveMotion(keys);
	WaitMotion(keys);
	JumpMotion();
	LandingMotion();

	//カメラ行列、プレイヤーの行列の作成
		camelaMatrix_->MakeCamelaMatrix();
	matrix_ = MakeAffineMatrix(scale_, 0, worldPos_);
	wvpVpMatrix_ = wvpVpMatrix(matrix_, camelaMatrix_->GetViewMatrix(), camelaMatrix_->GetOrthoMatrix(), camelaMatrix_->GetViewportMatrix());

}

void Player::Draw() {

	//スクリーン座標に変換
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
			velocity_.y = -15;
			isFlight_ = true;
			jumpSE_.isStart = true;

			//ジャンプモーションのフラグ立て
			jump_.isEasing = true;
			wait_.isEasing = false;
			move_.isEasing = false;
			jump_.easingPlus = 1;
			localVertex_ = localVertexSave_;
		}
	}

	if (isFlight_ == true) {
		acceleration_.y = 1.0f;
	}

	if (velocity_.y >= 16.0f) {
		acceleration_.y = 0;
	}

	velocity_.y += acceleration_.y;

	if (keys[DIK_A] || keys[DIK_D]) {
		worldPos_.x += velocity_.x;
	}
	worldPos_.y += velocity_.y;
}

void Player::ColligionMapChip() {

	/*maxPos_.x = MAX(worldPos_.x, oldWorldPos_.x);
	maxPos_.y = MAX(worldPos_.y, oldWorldPos_.y);

	fitMapsizePos_.intx = int(maxPos_.x / (mapchip_->GetMapchipSize() / 2));
	fitMapsizePos_.intx = int(fitMapsizePos_.intx * (mapchip_->GetMapchipSize() / 2));

	fitMapsizePos_.inty = int(maxPos_.y / (mapchip_->GetMapchipSize() / 2));
	fitMapsizePos_.inty = int(fitMapsizePos_.inty * (mapchip_->GetMapchipSize() / 2));*/

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
				landing_.easingRock = false;
			}

			//上にぶつかったら加速度と速度を0にする
			if (mapchip_->map[int(mapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] == BLOCK || mapchip_->map[int(mapNum_.RightTop.y)][int(mapNum_.RightTop.x)] == BLOCK) {
				velocity_.y = 0;

			}
		}
	}
	else {
		isFlight_ = true;
		landing_.easingRock = false;
	}


}

//プレイヤーのモーション関数
void Player::MoveMotion(char* keys) {

	//イージングフラグを立てる
	if (move_.isEasing == false && jump_.isEasing == false) {

		if (keys[DIK_A] || keys[DIK_D]) {

			move_.isEasing = true;
			wait_.isEasing = false;
			jump_.isEasing = false;
			move_.easingPlus = 1;
			localVertex_ = localVertexSave_;
		}
	}

	//イージングをする
	if (move_.isEasing == true) {

		move_.easingTime += move_.easingPlus;

		if (move_.easingTime >= 5 || move_.easingTime <= 0) {

			move_.easingPlus = -move_.easingPlus;
		}

		localVertex_.LeftTop.y = easeInSine(move_.easingTime/5, localVertexSave_.LeftTop.y, localVertexSave_.LeftTop.y - 10);
		localVertex_.RightTop.y = easeInSine(move_.easingTime/5, localVertexSave_.RightTop.y, localVertexSave_.RightTop.y - 10);
	}

	//イージングをしてないとき
	if (move_.isEasing == false) {
		move_.easingPlus = 0;
		move_.easingTime = 0;
	}
}

void Player::WaitMotion(char*keys) {

	//イージングフラグを立てる
	if (wait_.isEasing == false) {

		if (keys[DIK_A] == 0 && keys[DIK_D] == 0 && isFlight_ == false && jump_.isEasing == false) {
			wait_.easingCoolTime = 10;
			wait_.isEasing = true;
			move_.isEasing = false;
			jump_.isEasing = false;
			wait_.easingPlus = 1;
			localVertex_ = localVertexSave_;
		}
	}
	//イージングをする
	if (wait_.isEasing == true) {

		wait_.easingCoolTime--;
		if (wait_.easingCoolTime <= 0) {
			wait_.easingCoolTime = 0;
		}

		if (wait_.easingCoolTime == 0) {

			wait_.easingTime += wait_.easingPlus;

			if (wait_.easingTime >= 25 || wait_.easingTime <= 0) {

				wait_.easingPlus = -wait_.easingPlus;
			}

			localVertex_.LeftTop.y = easeInSine(wait_.easingTime / 25, localVertexSave_.LeftTop.y, localVertexSave_.LeftTop.y - 10);
			localVertex_.RightTop.y = easeInSine(wait_.easingTime / 25, localVertexSave_.RightTop.y, localVertexSave_.LeftTop.y - 10);
		}
	}

	//イージングをしてないとき
	if (wait_.isEasing == false) {
		wait_.easingPlus = 0;
		wait_.easingTime = 0;
	}
}

void Player::JumpMotion() {

	//フラグ立ては移動処理のジャンプのところで立てる

	//イージングをする
	if (jump_.isEasing == true) {

		landing_.isEasing = false;
		wait_.isEasing = false;
		move_.isEasing = false;
		jump_.easingTime += jump_.easingPlus;

		//イージングを1往復させる
		if (jump_.easingTime > 10 || jump_.easingTime < 0) {

			jump_.easingPlus = -jump_.easingPlus;
			jump_.easingCount++;

			if (jump_.easingCount >= 2) {
				jump_.isEasing = false;
			}
		}

		localVertex_.LeftBottom.y = easeInQuart(jump_.easingTime / 10, localVertexSave_.LeftBottom.y, localVertexSave_.LeftBottom.y - 15);
		localVertex_.RightBottom.y = easeInQuart(jump_.easingTime / 10, localVertexSave_.RightBottom.y, localVertexSave_.RightBottom.y -15);
	}

	//イージングをしてないとき
	if (jump_.isEasing == false) {
		jump_.easingPlus = 0;
		jump_.easingTime = 0;
		jump_.easingCount = 0;
	}

}

void Player::LandingMotion() {

	//フラグ立てはマップチップの当たり判定のところで行う
	
	if (isFlight_ == false) {
		//着地のモーションフラグを立てる
		if (landing_.isEasing == false && landing_.easingRock == false) {
			landing_.isEasing = true;
			landing_.easingPlus = 1;
		}
	}

	//イージングをする
	if (landing_.isEasing == true) {

		jump_.isEasing = false;
		wait_.isEasing = false;
		move_.isEasing = false;

		landing_.easingTime +=landing_.easingPlus;

		//イージングやめる
		if (landing_.easingTime >= 6) {			   
			landing_.isEasing = false;
			landing_.easingRock = true;
		}

		localVertex_.LeftTop.y = easeOutCubic(landing_.easingTime/6, localVertexSave_.LeftTop.y + 35, localVertexSave_.LeftTop.y);
		localVertex_.RightTop.y = easeOutCubic(landing_.easingTime / 6, localVertexSave_.RightTop.y + 35, localVertexSave_.RightTop.y);
		localVertex_.LeftTop.x = easeOutCubic(landing_.easingTime / 6, localVertexSave_.LeftTop.x - 20, localVertexSave_.LeftTop.x);
		localVertex_.RightTop.x = easeOutCubic(landing_.easingTime / 6, localVertexSave_.RightTop.x + 20, localVertexSave_.RightTop.x);
		localVertex_.LeftBottom.x = easeOutCubic(landing_.easingTime / 6, localVertexSave_.LeftBottom.x - 20, localVertexSave_.LeftBottom.x);
		localVertex_.RightBottom.x = easeOutCubic(landing_.easingTime / 6, localVertexSave_.RightBottom.x + 20, localVertexSave_.RightBottom.x);
	}

	//イージングをしてないとき
	if (landing_.isEasing == false) {
		landing_.easingPlus = 0;
		landing_.easingTime = 0;
	}

}