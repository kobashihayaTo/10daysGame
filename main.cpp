#include "DxLib.h"
#include "Enum.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "3043_���v���C";

// �E�B���h�E����
const int WIN_WIDTH = 1600;
// �E�B���h�E�c��
const int WIN_HEIGHT = 900;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ�
	//�^�C�g��
	int Title = LoadGraph("Resources/title.png");
	int Title_start01 = LoadGraph("Resources/title_start01.png");
	int Title_start02 = LoadGraph("Resources/title_start02.png");
	//�N���A
	int Clear = LoadGraph("Resources/clear.png");
	int Clear_start01 = LoadGraph("Resources/clear_title01.png");
	int Clear_start02 = LoadGraph("Resources/clear_title02.png");
	//�}�j���A��
	int Manual_1 = LoadGraph("Resources/menu01.png");
	int Manual_2 = LoadGraph("Resources/menu02.png");
	//�X�e�[�W�̌��
	int BackGround_1 = LoadGraph("Resources/background.png");
	int BackGround_2 = LoadGraph("Resources/background2.png");
	//�X�e�[�W��1��ڂ�2��ڂ̊ԂɎg������
	int ClearTime= LoadGraph("Resources/cleartime.png");
	int ClearTime_2 = LoadGraph("Resources/cleartime02.png");
	//�}�b�v
	int block = LoadGraph("Resources/Block01.png");//�}�b�v�`�b�v��1�ɕ\�������
	int goal = LoadGraph("Resources/E.png");//�}�b�v�`�b�v��1�ɕ\�������
	//�X�e�[�W�؂�ւ�
	int StageSelect = LoadGraph("Resources/stage_select.png");
	int StageSelect_1 = LoadGraph("Resources/stage_select01.png");
	int StageSelect_2 = LoadGraph("Resources/stage_select02.png");
	int StageSelect_3 = LoadGraph("Resources/stage_select03.png");
	//�����z��
	int graphHandle[10] = {};
	int graphHandle_2[10] = {};
	int graphHandleResult_[10] = {};
	int graphHandleResult_2[10] = {};

	int Number = LoadDivGraph("Resources/digits.png", 10, 10, 1, 16, 29, graphHandle);//�ԍ��̕\��
	int Number_2 = LoadDivGraph("Resources/digits.png", 10, 10, 1, 16, 29, graphHandle_2);//�ԍ��̕\��

	int NumberResult_ = LoadDivGraph("Resources/digits_2.png", 10, 10, 1, 64, 116, graphHandleResult_);//�ԍ��̕\��
	//BGM
	int TitleBGM;
	int Stage;
	int Result;
	TitleBGM = LoadSoundMem("Sound/title.mp3");
	Stage = LoadSoundMem("Sound/stage.mp3");
	Result = LoadSoundMem("Sound/result.mp3");
	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	// �^�C�g��
	Scene scene = Scene::TITLE;
	// �v���C���[
	Player* player_ = new Player();
	player_->Initialize();
	// �}�b�v
	Map* map_ = new Map();
	map_->Initialize();
	//UI
	UI* ui_ = new UI();
	ui_->Initialize();

	// �ϐ�
	//�^�C�g���Ŏg��
	int IntervalTimer = 0;
	int BlinkingTimer = 0;

	int eachNumber[10] = {};
	int eachNumber_2[10] = {};
	int eachNumber_[10] = {};

	int Timer = 000000;
	int Timer_2 = 000000;

	int ManualFlag = 0;
	int StageSelectFlag = 0;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

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
					StopSoundMem(TitleBGM);//�X�g�b�v
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
				StopSoundMem(Stage);//�X�g�b�v
				scene = Scene::END;
			}
			if (map_->GetTimerFlag() == 1) {
				StopSoundMem(Stage);//�X�g�b�v
				if (CheckSoundMem(Result) == 0) {
					PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
					ChangeVolumeSoundMem(128, Result);
				}
				if (keys[KEY_INPUT_SPACE] == 1) {
					StopSoundMem(Result);//�X�g�b�v
					StopSoundMem(Stage);//�X�g�b�v
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
				StopSoundMem(Stage);//�X�g�b�v
				scene = Scene::CLEAR;
			}
			if (map_->GetTimerFlag() == 5) {
				StopSoundMem(Stage);//�X�g�b�v
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
				StopSoundMem(Stage);//�X�g�b�v
				scene = Scene::END;
			}
			if (map_->GetTimerFlag() == 1) {
				StopSoundMem(Stage);//�X�g�b�v
				if (CheckSoundMem(Result) == 0) {
					PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
					ChangeVolumeSoundMem(128, Result);
				}
				if (keys[KEY_INPUT_SPACE] == 1) {
					StopSoundMem(Result);//�X�g�b�v
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
				StopSoundMem(Stage);//�X�g�b�v
				scene = Scene::CLEAR;
			}
			if (map_->GetTimerFlag() == 5) {
				StopSoundMem(Stage);//�X�g�b�v
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
				StopSoundMem(Stage);//�X�g�b�v
				if (CheckSoundMem(Result) == 0) {
					PlaySoundMem(Result, DX_PLAYTYPE_LOOP, true);
					ChangeVolumeSoundMem(128, Result);
				}
				if (keys[KEY_INPUT_SPACE] == 1) {
					StopSoundMem(Result);//�X�g�b�v
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

				StopSoundMem(Stage);//�X�g�b�v

				scene = Scene::CLEAR;
			}
			if (map_->GetTimerFlag() == 5) {

				StopSoundMem(Stage);//�X�g�b�v

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

					StopSoundMem(Result);//�X�g�b�v

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

				StopSoundMem(Result);//�X�g�b�v

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

				StopSoundMem(Result);//�X�g�b�v

				scene = Scene::TITLE;
			}
			break;
		}

		// �`�揈��
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

			//�^�C�}�[�̕`��
			Timer = map_->GetTimer_();

			printf("�S�̈�:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("�\�̈�:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("��̈�:%d", Timer);
			eachNumber[2] = Timer;


			// �֐���яo��
			map_->Draw(block, goal);
			player_->Draw();
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			if (map_->GetTimerFlag() == 1) {
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawGraph(0, 0, ClearTime, true);
				printf("�S�̈�:%d", Timer / 100);
				eachNumber_[0] = Timer / 100;
				Timer = Timer % 100;
				printf("�\�̈�:%d", Timer / 10);
				eachNumber_[1] = Timer / 10;
				Timer = Timer % 10;
				printf("��̈�:%d", Timer);
				eachNumber_[2] = Timer;

				// �֐���яo��
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
			printf("�S�̈�:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("�\�̈�:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("��̈�:%d", Timer);
			eachNumber[2] = Timer;

			// �֐���яo��
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			Timer_2 = map_->GetTimer_2();
			printf("�S�̈�:%d", Timer_2 / 100);
			eachNumber_2[0] = Timer_2 / 100;
			Timer_2 = Timer_2 % 100;

			printf("�\�̈�:%d", Timer_2 / 10);
			eachNumber_2[1] = Timer_2 / 10;
			Timer_2 = Timer_2 % 10;

			printf("��̈�:%d", Timer_2);
			eachNumber_2[2] = Timer_2;

			for (int j = 0; j < 3; j++)
			{
				DrawGraph(1350 + 16 * j, 60, graphHandle_2[eachNumber_2[j]], true);
			}

			// �֐���яo��
			map_->Draw(block, goal);
			player_->Draw();
			break;

		case Scene::Stage2GAME:

			DrawGraph(0, 0, BackGround_1, true);
			//DrawFormatString(0, 200, GetColor(255, 255, 255), "�X�e�[�W�Q");
			//�^�C�}�[�̕`��
			Timer = map_->GetTimer_();

			printf("�S�̈�:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("�\�̈�:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("��̈�:%d", Timer);
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
				printf("�S�̈�:%d", Timer / 100);
				eachNumber_[0] = Timer / 100;
				Timer = Timer % 100;
				printf("�\�̈�:%d", Timer / 10);
				eachNumber_[1] = Timer / 10;
				Timer = Timer % 10;
				printf("��̈�:%d", Timer);
				eachNumber_[2] = Timer;

				// �֐���яo��
				for (int i = 0; i < 3; i++)
				{
					DrawGraph(700 + 64 * i, 200, graphHandleResult_[eachNumber_[i]], true);
				}
			}
			break;

		case Scene::Stage2GAME2:

			DrawGraph(0, 0, BackGround_2, true);
			//DrawFormatString(0, 200, GetColor(255, 255, 255), "�X�e�[�W�Q");


			Timer = map_->GetTimer_();
			printf("�S�̈�:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("�\�̈�:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("��̈�:%d", Timer);
			eachNumber[2] = Timer;

			// �֐���яo��
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			Timer_2 = map_->GetTimer_2();
			printf("�S�̈�:%d", Timer_2 / 100);
			eachNumber_2[0] = Timer_2 / 100;
			Timer_2 = Timer_2 % 100;

			printf("�\�̈�:%d", Timer_2 / 10);
			eachNumber_2[1] = Timer_2 / 10;
			Timer_2 = Timer_2 % 10;

			printf("��̈�:%d", Timer_2);
			eachNumber_2[2] = Timer_2;

			for (int j = 0; j < 3; j++)
			{
				DrawGraph(1350 + 16 * j, 60, graphHandle_2[eachNumber_2[j]], true);
			}
			// �֐���яo��
			map_->Draw(block, goal);
			player_->Draw();
			break;

		case Scene::Stage3GAME:

			DrawGraph(0, 0, BackGround_1, true);
			//DrawFormatString(0, 200, GetColor(255, 255, 255), "�X�e�[�W3");
			// �֐���яo��

			//�^�C�}�[�̕`��
			Timer = map_->GetTimer_();

			printf("�S�̈�:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("�\�̈�:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("��̈�:%d", Timer);
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
				printf("�S�̈�:%d", Timer / 100);
				eachNumber_[0] = Timer / 100;
				Timer = Timer % 100;
				printf("�\�̈�:%d", Timer / 10);
				eachNumber_[1] = Timer / 10;
				Timer = Timer % 10;
				printf("��̈�:%d", Timer);
				eachNumber_[2] = Timer;

				// �֐���яo��
				for (int i = 0; i < 3; i++)
				{
					DrawGraph(700 + 64 * i, 200, graphHandleResult_[eachNumber_[i]], true);
				}
			}
			break;

		case Scene::Stage3GAME2:

			DrawGraph(0, 0, BackGround_2, true);
			//DrawFormatString(0, 200, GetColor(255, 255, 255), "�X�e�[�W3");


			Timer = map_->GetTimer_();
			printf("�S�̈�:%d", Timer / 100);
			eachNumber[0] = Timer / 100;
			Timer = Timer % 100;

			printf("�\�̈�:%d", Timer / 10);
			eachNumber[1] = Timer / 10;
			Timer = Timer % 10;

			printf("��̈�:%d", Timer);
			eachNumber[2] = Timer;

			// �֐���яo��
			for (int i = 0; i < 3; i++)
			{
				DrawGraph(1450 + 16 * i, 60, graphHandle[eachNumber[i]], true);
			}

			Timer_2 = map_->GetTimer_2();
			printf("�S�̈�:%d", Timer_2 / 100);
			eachNumber_2[0] = Timer_2 / 100;
			Timer_2 = Timer_2 % 100;

			printf("�\�̈�:%d", Timer_2 / 10);
			eachNumber_2[1] = Timer_2 / 10;
			Timer_2 = Timer_2 % 10;

			printf("��̈�:%d", Timer_2);
			eachNumber_2[2] = Timer_2;

			for (int j = 0; j < 3; j++)
			{
				DrawGraph(1350 + 16 * j, 60, graphHandle_2[eachNumber_2[j]], true);
			}
			// �֐���яo��
			map_->Draw(block, goal);
			player_->Draw();
			break;

		case Scene::BADEND:

			if (map_->GetTimerFlag() == 5) {
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawGraph(0, 0, ClearTime_2, true);

				Timer = map_->GetTimer_();
				printf("�S�̈�:%d", Timer / 100);
				eachNumber[0] = Timer / 100;
				Timer = Timer % 100;

				printf("�\�̈�:%d", Timer / 10);
				eachNumber[1] = Timer / 10;
				Timer = Timer % 10;

				printf("��̈�:%d", Timer);
				eachNumber[2] = Timer;

				// �֐���яo��
				for (int i = 0; i < 3; i++)
				{
					DrawGraph(700 + 64 * i, 100, graphHandleResult_[eachNumber_[i]], true);
				}

				Timer_2 = map_->GetTimer_2();
				printf("�S�̈�:%d", Timer_2 / 100);
				eachNumber_2[0] = Timer_2 / 100;
				Timer_2 = Timer_2 % 100;

				printf("�\�̈�:%d", Timer_2 / 10);
				eachNumber_2[1] = Timer_2 / 10;
				Timer_2 = Timer_2 % 10;

				printf("��̈�:%d", Timer_2);
				eachNumber_2[2] = Timer_2;

				for (int j = 0; j < 3; j++)
				{
					DrawGraph(700 + 64 * j, 250, graphHandleResult_[eachNumber_2[j]], true);
				}
			}
			break;

		case Scene::END:

			DrawBox(0, 0, 1600, 900, GetColor(0, 0, 255), true);
			DrawFormatString(700, 450, GetColor(255, 0, 0), "���Ԑ؂ꂾ");
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

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
