#include "DxLib.h"
#include "Enum.h"
#include "Player.h"
#include "Map.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1600;
// ウィンドウ縦幅
const int WIN_HEIGHT = 900;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int block = LoadGraph("Resources/map.png");//マップチップの1に表示される
	int goal = LoadGraph("Resources/E.png");//マップチップの1に表示される

	// ゲームループで使う変数の宣言
	Scene scene = Scene::TITLE;

	Player* player_ = new Player();
	player_->Initialize();

	Map* map_ = new Map();
	map_->Initialize();

	//変数
	int IntervalTimer = 0;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		switch (scene)
		{
		case Scene::TITLE:
			player_->Initialize();
			map_->AllReset();
			IntervalTimer++;

			if (IntervalTimer >= 30)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					scene = Scene::MANUAL;
					IntervalTimer = 0;
				}
			} 
			break;
		case Scene::MANUAL:

			if (keys[KEY_INPUT_A] == 1)
			{
				map_->SetMapNo(0);
				scene = Scene::Stage1GAME;
			}
			if (keys[KEY_INPUT_S] == 1)
			{
				map_->SetMapNo(1);
				scene = Scene::Stage2GAME;
			}
			if (keys[KEY_INPUT_D] == 1)
			{
				map_->SetMapNo(2);
				scene = Scene::Stage3GAME;
			}
			break;

		case Scene::Stage1GAME:
			player_->Update(keys, oldkeys);
			map_->Update(player_);

			if (map_->GetTimer_() >= 5000)
			{
				scene = Scene::END;
			}

			if (map_->GetTimerFlag() == 1)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					scene = Scene::Stage1GAME2;
					player_->Initialize();
 					map_->SetTimerFlag(2);
				}
			}
			break;
		case Scene::Stage1GAME2:

			player_->Update(keys, oldkeys);
			map_->Update(player_);
			if (map_->GetTimerFlag() == 4)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					scene = Scene::TITLE;
				}
			}
			if (map_->GetTimerFlag() == 5)
			{
				scene = Scene::BADEND;
			}
			break;

		case Scene::Stage2GAME:

			player_->Update(keys, oldkeys);
			map_->Update(player_);

			if (map_->GetTimer_() >= 5000)
			{
				scene = Scene::END;
			}

			if (map_->GetTimerFlag() == 1)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					scene = Scene::Stage2GAME2;
					player_->Initialize();
					map_->SetTimerFlag(2);
				}
			}
			break;

		case Scene::Stage2GAME2:

			player_->Update(keys, oldkeys);
			map_->Update(player_);
			if (map_->GetTimerFlag() == 4)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					scene = Scene::TITLE;
				}
			}
			if (map_->GetTimerFlag() == 5)
			{
				scene = Scene::BADEND;
			}
			break;

		case Scene::Stage3GAME:

			player_->Update(keys, oldkeys);
			map_->Update(player_);

			if (map_->GetTimer_() >= 5000)
			{
				scene = Scene::END;
			}

			if (map_->GetTimerFlag() == 1)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					scene = Scene::Stage3GAME2;
					player_->Initialize();
					map_->SetTimerFlag(2);
				}
			}
			break;
		case Scene::Stage3GAME2:
			player_->Update(keys, oldkeys);
			map_->Update(player_);
			if (map_->GetTimerFlag() == 4)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					scene = Scene::TITLE;
				}
			}
			if (map_->GetTimerFlag() == 5)
			{
				scene = Scene::BADEND;
			}
			break;

			break;
		case Scene::BADEND:

			if (map_->GetTimerFlag() == 5)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					scene = Scene::Stage1GAME2;
					player_->Initialize();
					map_->Reset();
				}
			}
			break;
		case Scene::END:
			if (keys[KEY_INPUT_SPACE] == 1)
			{
				scene = Scene::Stage1GAME;
				player_->Initialize();
				map_->AllReset();
			}
		}
		
		// 描画処理
		switch (scene)
		{


		case Scene::TITLE:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 255), true);
			DrawFormatString(700,450, GetColor(255, 0, 0), "SPACEでへんかするで");
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			break;
		case Scene::MANUAL:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(700, 350, GetColor(255, 0, 0), "A押したらステージ１ ");
			DrawFormatString(700, 400, GetColor(255, 0, 0), "S押したらステージ２ ");
			DrawFormatString(700, 450, GetColor(255, 0, 0), "D押したらステージ３ ");
			break;
		case Scene::Stage1GAME:

			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			map_->Draw(block,goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 1)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "SPACEでへんかするで");
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			}
			break;

		case Scene::Stage1GAME2:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			//関数飛び出し
			map_->Draw(block,goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 4)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "クリア");
				DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			}
			break;
		case Scene::Stage2GAME:

			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 255, 255), " ステージ２");
			map_->Draw(block, goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 1)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "SPACEでへんかするで");
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			}
			break;

		case Scene::Stage2GAME2:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 255, 255), " ステージ２");
			//関数飛び出し
			map_->Draw(block, goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 4)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "クリア");
				DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			}
			break;

		case Scene::Stage3GAME:

			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 255, 255), " ステージ3");
			map_->Draw(block, goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 1)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "SPACEでへんかするで");
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			}
			break;

		case Scene::Stage3GAME2:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 255, 255), " ステージ3");
			//関数飛び出し
			map_->Draw(block, goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 4)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "クリア");
				DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			}
			break;


		case Scene::BADEND:
			if (map_->GetTimerFlag() == 5)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "もう一回やってみよう");
				DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
				DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			}
			break;
		case Scene::END:
			DrawBox(0, 0, 1600, 900, GetColor(0,0, 255), true);
			DrawFormatString(700, 450, GetColor(255, 0, 0), "時間切れだ");
			DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			break;
}


		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
