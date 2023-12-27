#include <Novice.h>
#include<stdio.h>

//class
#include"player.h"
#include"mapchip.h"
#include"camelaMatrix.h"


const char kWindowTitle[] = "LC1A_12_クリハラ_ケイタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	Player* player = new Player();
	Mapchip* mapchip = new Mapchip();
	CamelaMatrix* camelaMatrix = new CamelaMatrix;

	player->SetCamelaMatrix(camelaMatrix);
	mapchip->SetCamelaMatrix(camelaMatrix);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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
		player->Update(keys);
		mapchip->Update();
	

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		mapchip->Draw();
		player->Draw();
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
