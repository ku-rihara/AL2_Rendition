#include<Novice.h>

//funtion
#include"Easing.h"

//class
#include"Weapon.h"

Weapon::Weapon() {
	Init();

	camela_ = new Camela;

	leftTexture_.Handle = Novice::LoadTexture("./Resources/gunLeft.png");
	rightTexture_.Handle = Novice::LoadTexture("./Resources/gunRight.png");

}

void Weapon::Init() {

	worldPos_ = {};
	 scale_ = {};

	 localVertex_ = {};
	 screenPos_ = {};

	 matrix_ = {};
	 wvpVpMatrix_ = {};

	 scaleUp = {};

	theta_=0;
}

void Weapon::Update() {




}

void Weapon::Draw() {

}