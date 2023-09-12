#include "DxLib.h"
#include "Enum.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "3043_リプレイ";

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

	// 画像などのリソースデータの変数宣言と読み込
	//タイトル
	int Title = LoadGraph("Resources/title.png");
	int Title_start01 = LoadGraph("Resources/title_start01.png");
	int Title_start02 = LoadGraph("Resources/title_start02.png");
	//クリア
	int Clear = LoadGraph("Resources/clear.png");
	int Clear_start01 = LoadGraph("Resources/clear_title01.png");
	int Clear_start02 = LoadGraph("Resources/clear_title02.png");
	//マニュアル
	int Manual_1 = LoadGraph("Resources/menu01.png");
	int Manual_2 = LoadGraph("Resources/menu02.png");
	//ステージの後ろ
	int BackGround_1 = LoadGraph("Resources/background.png");
	int BackGround_2 = LoadGraph("Resources/background2.png");
	//ステージの1回目と2回目の間に使うもの
	int ClearTime= LoadGraph("Resources/cleartime.png");
	int ClearTime_2 = LoadGraph("Resources/cleartime02.png");
	//マップ
	int block = LoadGraph("Resources/Block01.png");//マップチップの1に表示される
	int goal = LoadGraph("Resources/E.png");//マップチップの1に表示される
	//ステージ切り替え
	int StageSelect = LoadGraph("Resources/stage_select.png");
	int StageSelect_1 = LoadGraph("Resources/stage_select01.png");
	int StageSelect_2 = LoadGraph("Resources/stage_select02.png");
	int StageSelect_3 = LoadGraph("Resources/stage_select03.png");
	//数字配列
	int graphHandle[10] = {};
	int graphHandle_2[10] = {};
	int graphHandleResult_[10] = {};
	int graphHandleResult_2[10] = {};

	int Number = LoadDivGraph("Resources/digits.png", 10, 10, 1, 16, 29, graphHandle);//番号の表示
	int Number_2 = LoadDivGraph("Resources/digits.png", 10, 10, 1, 16, 29, graphHandle_2);//番号の表示

	int NumberResult_ = LoadDivGraph("Resources/digits_2.png", 10, 10, 1, 64, 116, graphHandleResult_);//番号の表示
	//BGM
	int TitleBGM;
	int Stage;
	int Result;
	TitleBGM = LoadSoundMem("Sound/title.mp3");
	Stage = LoadSoundMem("Sound/stage.mp3");
	Result = LoadSoundMem("Sound/result.mp3");
	// ゲームループで使う変数の宣言
	// タイトル
	Scene scene = Scene::TITLE;
	// プレイヤー
	Player* player_ = new Player();
	player_->Initialize();
	// マップ
	Map* map_ = new Map();
	map_->Initialize();
	//UI
	UI* ui_ = new UI();
	ui_->Initialize();

	// 変数
	//タイトルで使う
	int IntervalTimer = 0;
	int BlinkingTimer = 0;

	int eachNumber[10] = {};
	int eachNumber_2[10] = {};
	int eachNumber_[10] = {};

	int Timer = 000000;
	int Timer_2 = 000000;

	int ManualFlag = 0;
	int StageSelectFlag = 0;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		for (int i = 0; i < 256; i++) {
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
			if (CheckSoundMem(TitleBGM) == 0) {
				PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, TitleBGM);
			}
			if (IntervalTimer >= 30) {
				if (keys[KEY_INPUT_SPACE] == 1) {
					StopSoundMem(TitleBGM);//ストップ
					scene = Scene::MANUAL;
					IntervalTimer = 0;
					BlinkingTimer = 0;

				}
			}
			break;

		case Scene::MANUAL:
			IntervalTimer++;
			if (IntervalTimer >= 30) {
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					ManualFlag++;
					IntervalTimer = 0;
				}

				if (ManualFlag == 2)
				{
					IntervalTimer = 0;
					ManualFlag = 0;
					scene = Scene::SELECT;
				}
			}

			break;
		case Scene::SELECT:
			if (keys[KEY_INPUT_LEFT] == 1 && oldkeys[KEY_INPUT_LEFT] == 0)
			{
				StageSelectFlag--;
			}
			if (keys[KEY_INPUT_RIGHT] == 1 && oldkeys[KEY_INPUT_RIGHT] == 0)
			{
				StageSelectFlag++;
			}

			if (StageSelectFlag < 0)
			{
				StageSelectFlag = 0;
			}
			if (StageSelectFlag > 2)
			{
				StageSelectFlag = 2;
			}

			IntervalTimer++;
			if (IntervalTimer >= 30) {
				if (StageSelectFlag == 0) {
					if (keys[KEY_INPUT_SPACE] == 1) {

						map_->SetMapNo(0);
						scene = Scene::Stage1GAME;
					}
				}
				if (StageSelectFlag == 1) {
					if (keys[KEY_INPUT_SPACE] == 1) {

						map_->SetMapNo(1);
						scene = Scene::Stage2GAME;
					}
				}
				if (StageSelectFlag == 2) {
					if (keys[KEY_INPUT_SPACE] == 1) {

						map_->SetMapNo(2);
						scene = Scene::Stage3GAME;
					}
				}
			}
			break;

		case Scene::Stage1GAME:

			if (CheckSoundMem(Stage) == 0) {
				PlaySoundMem(Stage, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Stage);
			}

			player_->Update(keys, oldkeys);
			map_->Update(player_);

			if (map_->GetTimer_() >= 5000) {
				StopSoundMem(Stage);//ストップ
				scene = Scene::END;
			}
			if (map_->GetTimerFlag() == 1) {
				StopSoundMem(Stage);//ストップ
				if (CheckSoundMem(Result) == 0) {
					PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
					ChangeVolumeSoundMem(128, Result);
				}
				if (keys[KEY_INPUT_SPACE] == 1) {
					StopSoundMem(Result);//ストップ
					StopSoundMem(Stage);//ストップ
					scene = Scene::Stage1GAME2;
					player_->Initialize();
					map_->SetTimerFlag(2);
				}
			}
			break;

		case Scene::Stage1GAME2:
			if (CheckSoundMem(Stage) == 0) {
				PlaySoundMem(Stage, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Stage);
			}
			player_->Update(keys, oldkeys);
			map_->Update(player_);
			if (map_->GetTimerFlag() == 4) {
				StopSoundMem(Stage);//ストップ
				scene = Scene::CLEAR;
			}
			if (map_->GetTimerFlag() == 5) {
				StopSoundMem(Stage);//ストップ
				scene = Scene::BADEND;
			}
			break;

		case Scene::Stage2GAME:
			if (CheckSoundMem(Stage) == 0) {
				PlaySoundMem(Stage, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Stage);
			}
			player_->Update(keys, oldkeys);
			map_->Update(player_);
			if (map_->GetTimer_() >= 5000) {
				StopSoundMem(Stage);//ストップ
				scene = Scene::END;
			}
			if (map_->GetTimerFlag() == 1) {
				StopSoundMem(Stage);//ストップ
				if (CheckSoundMem(Result) == 0) {
					PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
					ChangeVolumeSoundMem(128, Result);
				}
				if (keys[KEY_INPUT_SPACE] == 1) {
					StopSoundMem(Result);//ストップ
					scene = Scene::Stage2GAME2;
					player_->Initialize();
					map_->SetTimerFlag(2);
				}
			}
			break;

		case Scene::Stage2GAME2:

			if (CheckSoundMem(Stage) == 0) {
				PlaySoundMem(Stage, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Stage);
			}
			player_->Update(keys, oldkeys);
			map_->Update(player_);
			if (map_->GetTimerFlag() == 4) {
				StopSoundMem(Stage);//ストップ
				scene = Scene::CLEAR;
			}
			if (map_->GetTimerFlag() == 5) {
				StopSoundMem(Stage);//ストップ
				scene = Scene::BADEND;
			}
			break;

		case Scene::Stage3GAME:
			if (CheckSoundMem(Stage) == 0) {
				PlaySoundMem(Stage, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Stage);
			}
			player_->Update(keys, oldkeys);
			map_->Update(player_);

			if (map_->GetTimer_() >= 5000) {
				scene = Scene::END;
			}
			if (map_->GetTimerFlag() == 1) {
				StopSoundMem(Stage);//ストップ
				if (CheckSoundMem(Result) == 0) {
					PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
					ChangeVolumeSoundMem(128, Result);
				}
				if (keys[KEY_INPUT_SPACE] == 1) {
					StopSoundMem(Result);//ストップ
					scene = Scene::Stage3GAME2;
					player_->Initialize();
					map_->SetTimerFlag(2);
				}
			}
			break;

		case Scene::Stage3GAME2:

			if (CheckSoundMem(Stage) == 0) {
				PlaySoundMem(Stage, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Stage);
			}

			player_->Update(keys, oldkeys);
			map_->Update(player_);
			if (map_->GetTimerFlag() == 4) {

				StopSoundMem(Stage);//ストップ

				scene = Scene::CLEAR;
			}
			if (map_->GetTimerFlag() == 5) {

				StopSoundMem(Stage);//ストップ

				scene = Scene::BADEND;
			}
			break;

		case Scene::BADEND:
			if (CheckSoundMem(Result) == 0) {
				PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Result);
			}
			if (map_->GetTimerFlag() == 5) {
				if (keys[KEY_INPUT_SPACE] == 1) {

					StopSoundMem(Result);//ストップ

					scene = Scene::Stage1GAME2;
					player_->Initialize();
					map_->Reset();
				}
			}
			break;

		case Scene::END:
			if (CheckSoundMem(Result) == 0) {
				PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Result);
			}
			if (keys[KEY_INPUT_SPACE] == 1) {

				StopSoundMem(Result);//ストップ

				scene = Scene::Stage1GAME;
				player_->Initialize();
				map_->AllReset();
			}
			break;
		case Scene::CLEAR:
			if (CheckSoundMem(Result) == 0) {
				PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(128, Result);
			}
			if (keys[KEY_INPUT_SPACE] == 1) {

				StopSoundMem(Result);//ストップ

				scene = Scene::TITLE;
			}
			break;
		}

		// 描画処理
		switch (scene)
		{
		case Scene::TITLE:

			BlinkingTimer++;
			DrawGraph(0, 0, Title, true);
			if (BlinkingTimer <= 30)
			{
				//DrawGraph(0, 0, Title_start02, true);
				DrawGraph(0, 0, Title_start01, true);
			}
			if (BlinkingTimer >= 60)
			{
				BlinkingTimer = 0;
			}
			break;

		case Scene::MANUAL:
			if (ManualFlag == 0)
			{
				DrawGraph(0, 0, Manual_1, false);
			}
			if (ManualFlag == 1)
			{
				DrawGraph(0, 0, Manual_2, true);
			}
			break;

		case Scene::SELECT:

			DrawGraph(0, 0, StageSelect, true);

			if (StageSelectFlag == 0)
			{
				DrawGraph(0, 0, StageSelect_1, true);
			}
			if (StageSelectFlag == 1)
			{
				DrawGraph(0, 0, StageSelect_2, true);
			}
			if (StageSelectFlag == 2)
			{
				DrawGraph(0, 0, StageSelect_3, true);
			}
			break;

		case Scene::Stage1GAME:
			DrawGraph(0, 0, BackGround_1, true);
			//DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);

			//タイマーの描画
			Timer = map_->GetTimer_();

			printf("百の位:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("十の位:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("一の位:%d", Timer);
			eachNumber[2] = Timer;


			// 関数飛び出し
			map_->Draw(block, goal);
			player_->Draw();
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			if (map_->GetTimerFlag() == 1) {
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawGraph(0, 0, ClearTime, true);
				printf("百の位:%d", Timer / 100);
				eachNumber_[0] = Timer / 100;
				Timer = Timer % 100;
				printf("十の位:%d", Timer / 10);
				eachNumber_[1] = Timer / 10;
				Timer = Timer % 10;
				printf("一の位:%d", Timer);
				eachNumber_[2] = Timer;

				// 関数飛び出し
				for (int i = 0; i < 3; i++)
				{
					DrawGraph(700 + 64 * i, 200, graphHandleResult_[eachNumber_[i]], true);
				}

			}
			break;

		case Scene::Stage1GAME2:
			DrawGraph(0, 0, BackGround_2, true);
			//DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);

			Timer = map_->GetTimer_();
			printf("百の位:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("十の位:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("一の位:%d", Timer);
			eachNumber[2] = Timer;

			// 関数飛び出し
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			Timer_2 = map_->GetTimer_2();
			printf("百の位:%d", Timer_2 / 100);
			eachNumber_2[0] = Timer_2 / 100;
			Timer_2 = Timer_2 % 100;

			printf("十の位:%d", Timer_2 / 10);
			eachNumber_2[1] = Timer_2 / 10;
			Timer_2 = Timer_2 % 10;

			printf("一の位:%d", Timer_2);
			eachNumber_2[2] = Timer_2;

			for (int j = 0; j < 3; j++)
			{
				DrawGraph(1350 + 16 * j, 60, graphHandle_2[eachNumber_2[j]], true);
			}

			// 関数飛び出し
			map_->Draw(block, goal);
			player_->Draw();
			break;

		case Scene::Stage2GAME:

			DrawGraph(0, 0, BackGround_1, true);
			//DrawFormatString(0, 200, GetColor(255, 255, 255), "ステージ２");
			//タイマーの描画
			Timer = map_->GetTimer_();

			printf("百の位:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("十の位:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("一の位:%d", Timer);
			eachNumber[2] = Timer;

			map_->Draw(block, goal);
			player_->Draw();
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			if (map_->GetTimerFlag() == 1) {
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawGraph(0, 0, ClearTime, true);
				Timer = map_->GetTimer_();
				printf("百の位:%d", Timer / 100);
				eachNumber_[0] = Timer / 100;
				Timer = Timer % 100;
				printf("十の位:%d", Timer / 10);
				eachNumber_[1] = Timer / 10;
				Timer = Timer % 10;
				printf("一の位:%d", Timer);
				eachNumber_[2] = Timer;

				// 関数飛び出し
				for (int i = 0; i < 3; i++)
				{
					DrawGraph(700 + 64 * i, 200, graphHandleResult_[eachNumber_[i]], true);
				}
			}
			break;

		case Scene::Stage2GAME2:

			DrawGraph(0, 0, BackGround_2, true);
			//DrawFormatString(0, 200, GetColor(255, 255, 255), "ステージ２");


			Timer = map_->GetTimer_();
			printf("百の位:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("十の位:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("一の位:%d", Timer);
			eachNumber[2] = Timer;

			// 関数飛び出し
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			Timer_2 = map_->GetTimer_2();
			printf("百の位:%d", Timer_2 / 100);
			eachNumber_2[0] = Timer_2 / 100;
			Timer_2 = Timer_2 % 100;

			printf("十の位:%d", Timer_2 / 10);
			eachNumber_2[1] = Timer_2 / 10;
			Timer_2 = Timer_2 % 10;

			printf("一の位:%d", Timer_2);
			eachNumber_2[2] = Timer_2;

			for (int j = 0; j < 3; j++)
			{
				DrawGraph(1350 + 16 * j, 60, graphHandle_2[eachNumber_2[j]], true);
			}
			// 関数飛び出し
			map_->Draw(block, goal);
			player_->Draw();
			break;

		case Scene::Stage3GAME:

			DrawGraph(0, 0, BackGround_1, true);
			//DrawFormatString(0, 200, GetColor(255, 255, 255), "ステージ3");
			// 関数飛び出し

			//タイマーの描画
			Timer = map_->GetTimer_();

			printf("百の位:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("十の位:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("一の位:%d", Timer);
			eachNumber[2] = Timer;


			map_->Draw(block, goal);
			player_->Draw();
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			if (map_->GetTimerFlag() == 1) {
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawGraph(0, 0, ClearTime, true);
				Timer = map_->GetTimer_();
				printf("百の位:%d", Timer / 100);
				eachNumber_[0] = Timer / 100;
				Timer = Timer % 100;
				printf("十の位:%d", Timer / 10);
				eachNumber_[1] = Timer / 10;
				Timer = Timer % 10;
				printf("一の位:%d", Timer);
				eachNumber_[2] = Timer;

				// 関数飛び出し
				for (int i = 0; i < 3; i++)
				{
					DrawGraph(700 + 64 * i, 200, graphHandleResult_[eachNumber_[i]], true);
				}
			}
			break;

		case Scene::Stage3GAME2:

			DrawGraph(0, 0, BackGround_2, true);
			//DrawFormatString(0, 200, GetColor(255, 255, 255), "ステージ3");


			Timer = map_->GetTimer_();
			printf("百の位:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("十の位:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("一の位:%d", Timer);
			eachNumber[2] = Timer;

			// 関数飛び出し
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			Timer_2 = map_->GetTimer_2();
			printf("百の位:%d", Timer_2 / 100);
			eachNumber_2[0] = Timer_2 / 100;
			Timer_2 = Timer_2 % 100;

			printf("十の位:%d", Timer_2 / 10);
			eachNumber_2[1] = Timer_2 / 10;
			Timer_2 = Timer_2 % 10;

			printf("一の位:%d", Timer_2);
			eachNumber_2[2] = Timer_2;

			for (int j = 0; j < 3; j++)
			{
				DrawGraph(1350 + 16 * j, 60, graphHandle_2[eachNumber_2[j]], true);
			}
			// 関数飛び出し
			map_->Draw(block, goal);
			player_->Draw();
			break;

		case Scene::BADEND:

			if (map_->GetTimerFlag() == 5) {
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawGraph(0, 0, ClearTime_2, true);

				Timer = map_->GetTimer_();
				printf("百の位:%d", Timer / 100);
				eachNumber[0] = Timer / 100;
				Timer = Timer % 100;

				printf("十の位:%d", Timer / 10);
				eachNumber[1] = Timer / 10;
				Timer = Timer % 10;

				printf("一の位:%d", Timer);
				eachNumber[2] = Timer;

				// 関数飛び出し
				for (int i = 0; i < 3; i++)
				{
					DrawGraph(700 + 64 * i, 100, graphHandleResult_[eachNumber_[i]], true);
				}

				Timer_2 = map_->GetTimer_2();
				printf("百の位:%d", Timer_2 / 100);
				eachNumber_2[0] = Timer_2 / 100;
				Timer_2 = Timer_2 % 100;

				printf("十の位:%d", Timer_2 / 10);
				eachNumber_2[1] = Timer_2 / 10;
				Timer_2 = Timer_2 % 10;

				printf("一の位:%d", Timer_2);
				eachNumber_2[2] = Timer_2;

				for (int j = 0; j < 3; j++)
				{
					DrawGraph(700 + 64 * j, 250, graphHandleResult_[eachNumber_2[j]], true);
				}
			}
			break;

		case Scene::END:

			DrawBox(0, 0, 1600, 900, GetColor(0, 0, 255), true);
			DrawFormatString(700, 450, GetColor(255, 0, 0), "時間切れだ");
			DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			break;

		case Scene::CLEAR:
			BlinkingTimer++;

			DrawGraph(0, 0, Clear, true);
			DrawGraph(0, 0, Clear_start01, true);
			if (BlinkingTimer <= 30)
			{
				DrawGraph(0, 0, Clear_start02, true);
			}
			if (BlinkingTimer >= 60)
			{
				BlinkingTimer = 0;
			}


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
