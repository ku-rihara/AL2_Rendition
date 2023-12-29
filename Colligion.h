#pragma once

#include"struct.h"

//class
#include"player.h"
#include"Enemy.h"
#include"Weapon.h"
#include"camelaMatrix.h"


class Colligion {
public:

	Player* player_;
	Enemy* enemy_;
	Weapon* weapon_;

	float playerEnemyDistance_;
	float bulletEnemyDistance_;

public:

	Colligion();

	void WeaponEnemyColligion(Player& player, Enemy& enemy, Weapon& weapon);
	void ColligionUpdate(Player& player, Enemy& enemy, Weapon& weapon);

	//setter
	void SetPlayer(Player* player) { player_ = player; }
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }
	void SetWeapon(Weapon* weapon) { weapon_ = weapon; }

};