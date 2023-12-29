#include<Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
//funtion
#include"Easing.h"
#include"Matrix3x3.h"
#include"Function.h"

//class
#include"Weapon.h"

Weapon::Weapon() {
	Init();

	camela_ = new Camela;

	leftTexture_.Handle = Novice::LoadTexture("./Resources/gunLeft.png");
	rightTexture_.Handle = Novice::LoadTexture("./Resources/gunRight.png");
	gun_.Handle= Novice::LoadTexture("./Resources/bullet.png");
}

void Weapon::Init() {

	worldPos_ = {};
	scale_ = {};

	localVertex_ = {
	  {16 * 4,16 * 2},
	  {16 * 4,16 * 2},
	  {16 * 4,16 * 2},
      {16 * 4,16 * 2},
	};

	gunLocalVertex_ = {
	  {16,16},
	  {16,16},
	  {16,16},
	  {16,16},
	};

	screenPos_ = {};

	matrix_ = {};
	wvMatrix_ = {};

	appearance_ = {};
	isShot_ = false;

	theta_ = 0;
	isAppearance = 0;

	direction_ = RIGHT;

	gunWorldPos_={};
	gunDirection_ = {};
	gunScale_ = {1,1};

	 gunScreenPos_ = {};
	 gundirection = 0;

	 gunMatrix_ = {};
	 gunwvMatrix_ = {};
}

void Weapon::Update() {

	
		matrix_ = MakeAffineMatrix(scale_, theta_, worldPos_);
		wvMatrix_ = Multiply(matrix_, camela_->GetViewMatrix());
	
	

	gunMatrix_ = MakeAffineMatrix(gunScale_, 0, gunWorldPos_);
	gunwvMatrix_ = Multiply(gunMatrix_, camela_->GetViewMatrix());

	Weapon::Appearance();
}

void Weapon::Draw() {

	screenPos_ = Transform(localVertex_, wvMatrix_);
	gunScreenPos_ = Transform(gunLocalVertex_, gunwvMatrix_);

	if (isShot_ == true&&coolTime_==0) {
		newDrawQuad(gunScreenPos_, 0, 0, 16, 16, gun_.Handle, WHITE);
	}

	if (direction_ == LEFT) {
		newDrawQuad(screenPos_, 0, 0, localVertex_.LeftTop.x, localVertex_.LeftTop.y, leftTexture_.Handle, WHITE);
	}

	if (direction_ == RIGHT) {
		newDrawQuad(screenPos_, 0, 0, localVertex_.LeftTop.x, localVertex_.LeftTop.y, rightTexture_.Handle, WHITE);
	}
}

void Weapon::Appearance() {

	if (isAppearance == true && appearance_.isEasing == false) {

		appearance_.isEasing = true;
		appearance_.easingPlus = 1;
	}

	if (appearance_.isEasing == true) {
		appearance_.easingTime += appearance_.easingPlus;

		if (appearance_.easingTime >= 30) {
			appearance_.easingTime = 30;
			if (coolTime_ == 0) {
				isShot_ = true;
			}
			appearance_.isEasing = false;
		}

		worldPos_.x = easeOutBack(appearance_.easingTime/30, startPos_.x, endPos_.x);
		worldPos_.y = easeOutBack(appearance_.easingTime/30, startPos_.y, endPos_.y);
		scale_.x = easeOutBack(appearance_.easingTime / 30, 0, 1);
		scale_.y = easeOutBack(appearance_.easingTime / 30, 0, 1);
		theta_= easeOutBack(appearance_.easingTime / 30,  (1.0f / 64.0f) * float(M_PI), (640.0f / 64.0f) * float(M_PI));
	}

	if (isShot_ == false) {

		if (direction_ == LEFT) {
			gunWorldPos_.x = endPos_.x + 24;
			gunWorldPos_.y = endPos_.y - 10;
			gundirection = 1;
		}
		else if (direction_ == RIGHT) {
			gunWorldPos_.x = endPos_.x ;
			gunWorldPos_.y = endPos_.y - 10;
			gundirection = -1;
		}
	}
}
