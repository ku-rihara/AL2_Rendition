#define _USE_MATH_DEFINES
#include <math.h>


#include"Function.h"

#include"Colligion.h"


Colligion::Colligion() {

	player_ = new Player;
	weapon_ = new Weapon;
	
	playerEnemyDistance_ = 0;
	bulletEnemyDistance_ = 0;

}

void Colligion::WeaponEnemyColligion(Player& player, Enemy& enemy, Weapon& weapon) {

	playerEnemyDistance_ = Distance(player.worldPos_, enemy.worldPos_);

	if (playerEnemyDistance_ <= 48 * 10) {

		weapon.isAppearance = true;
	}


	if (weapon.isShot_ == true&& weapon.coolTime_ ==0) {
		
			weapon.gunWorldPos_.x += (20.0f/6)*weapon.gundirection;

			if (enemy.isDeath_ == false) {
				bulletEnemyDistance_ = Distance(weapon.gunWorldPos_, enemy.worldPos_);

				if (bulletEnemyDistance_ <= 24) {

					weapon.gunWorldPos_.x = weapon.endPos_.x + 24;
					weapon.gunWorldPos_.y = weapon.endPos_.y - 10;
					weapon.isShot_ = false;
					weapon.coolTime_ = 30;
					enemy.isDeath_ = true;
				}	
			}

			if (weapon.gunScreenPos_.LeftBottom.x >= 1280 || weapon.gunScreenPos_.LeftBottom.x <= 0) {
				weapon.isShot_ = false;
				weapon.gunWorldPos_.x = weapon.endPos_.x + 24;
				weapon.gunWorldPos_.y = weapon.endPos_.y - 10;
				weapon.coolTime_ = 30;
			}
	}

	weapon.coolTime_ -= (1.0f / 6.0f);
	if (weapon.coolTime_ < 0) {
		weapon.coolTime_ = 0;
	}

}

void Colligion::ColligionUpdate(Player& player, Enemy& enemy, Weapon& weapon) {

	Colligion::WeaponEnemyColligion( player,   enemy,   weapon);

}