#include <Novice.h>
#include<stdio.h>

//class
#include"player.h"
#include"mapchip.h"
#include"camelaMatrix.h"
#include"Enemy.h"
#include"Weapon.h"
#include"Colligion.h"

#include"struct.h"


const char kWindowTitle[] = "LC1A_12_クリハラ_ケイタ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	Player* player = new Player();
	Mapchip* mapchip = new Mapchip();
	Camela* camelaMatrix = new Camela;
	Weapon* weapon = new Weapon;

	const int enemyNum = 6;
	Enemy* enemy[enemyNum]{};

	Colligion* colligion = new Colligion;

	for (int i = 0; i < enemyNum; i++) {

		if (i == 0) {
			enemy[0] = new Enemy(48 * 5, 48 * 29 - 24);
		}

		if (i < 3 && i >= 1) {
			enemy[i] = new Enemy(float(48 * 16) + i * (48 * 15), 48 * 9 - 24);
		}

		if (i >= 3) {
			enemy[i] = new Enemy(float(48 * 16) + (i - 3) * (48 * 15), 48 * 29 - 24);
		}
		enemy[i]->SetCamela(camelaMatrix);
		colligion->SetEnemy(enemy[i]);
	}

	player->SetCamelaMatrix(camelaMatrix);
	mapchip->SetCamelaMatrix(camelaMatrix);
	weapon->SetCamelaMatrix(camelaMatrix);

	player->SetWeapon(weapon);

	colligion->SetPlayer(player);
	colligion->SetWeapon(weapon);

	int uiMove = Novice::LoadTexture("./Resources/move.png");
	int uijump = Novice::LoadTexture("./Resources/jump.png");


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		player->Update(keys, preKeys);
		mapchip->Update();

		for (int i = 0; i < enemyNum; i++) {
			enemy[i]->Update();

			colligion->ColligionUpdate(*player, *enemy[i], *weapon);
		}

		if (keys[DIK_R]) {
			player->Init();
			camelaMatrix->Init();
			weapon->Init();

			for (int i = 0; i < enemyNum; i++) {

				if (i == 0) {
					enemy[0]->Init(48 * 5, 48 * 29 - 24);
				}

				if (i < 3 && i >= 1) {
					enemy[i]->Init(float(48 * 16) + i * (48 * 15), 48 * 9 - 24);
				}

				if (i >= 3) {
					enemy[i]->Init(float(48 * 16) + (i - 3) * (48 * 15), 48 * 29 - 24);
				}
			}
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから

		Novice::DrawBox(0, 0, 1280, 720, 0, 0x000000cc, kFillModeSolid);

		mapchip->Draw();

		for (int i = 0; i < enemyNum; i++) {
			enemy[i]->Draw();
		}

		Novice::DrawSprite(0, 0, uiMove, 1, 1, 0, WHITE);
		Novice::DrawSprite(0, 50, uijump, 1, 1, 0, WHITE);

		player->Draw();

		/*for (int i = 0; i < 29; i++) {

			Novice::DrawLine(i * 48, 0, i * 48, 720, RED);
			Novice::DrawLine(0, i * 48,1280, i * 48, GREEN);
		}*/
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
