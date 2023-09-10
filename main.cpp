#include "DxLib.h"
#include "Enum.h"
#include "Player.h"
#include "Map.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�^�C�g��";

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

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int block = LoadGraph("Resources/map.png");//�}�b�v�`�b�v��1�ɕ\�������
	int goal = LoadGraph("Resources/E.png");//�}�b�v�`�b�v��1�ɕ\�������

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	Scene scene = Scene::TITLE;

	Player* player_ = new Player();
	player_->Initialize();

	Map* map_ = new Map();
	map_->Initialize();

	//�ϐ�
	int IntervalTimer = 0;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		for (int i = 0; i < 256; i++)
		{
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
		
		// �`�揈��
		switch (scene)
		{


		case Scene::TITLE:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 255), true);
			DrawFormatString(700,450, GetColor(255, 0, 0), "SPACE�łւ񂩂����");
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			break;
		case Scene::MANUAL:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(700, 350, GetColor(255, 0, 0), "A��������X�e�[�W�P ");
			DrawFormatString(700, 400, GetColor(255, 0, 0), "S��������X�e�[�W�Q ");
			DrawFormatString(700, 450, GetColor(255, 0, 0), "D��������X�e�[�W�R ");
			break;
		case Scene::Stage1GAME:

			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			map_->Draw(block,goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 1)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "SPACE�łւ񂩂����");
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			}
			break;

		case Scene::Stage1GAME2:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			//�֐���яo��
			map_->Draw(block,goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 4)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "�N���A");
				DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			}
			break;
		case Scene::Stage2GAME:

			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 255, 255), " �X�e�[�W�Q");
			map_->Draw(block, goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 1)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "SPACE�łւ񂩂����");
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			}
			break;

		case Scene::Stage2GAME2:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 255, 255), " �X�e�[�W�Q");
			//�֐���яo��
			map_->Draw(block, goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 4)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "�N���A");
				DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			}
			break;

		case Scene::Stage3GAME:

			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 255, 255), " �X�e�[�W3");
			map_->Draw(block, goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 1)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "SPACE�łւ񂩂����");
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			}
			break;

		case Scene::Stage3GAME2:
			DrawBox(0, 0, 1600, 900, GetColor(255, 255, 0), true);
			DrawFormatString(0, 200, GetColor(255, 255, 255), " �X�e�[�W3");
			//�֐���яo��
			map_->Draw(block, goal);
			player_->Draw();
			if (map_->GetTimerFlag() == 4)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "�N���A");
				DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			}
			break;


		case Scene::BADEND:
			if (map_->GetTimerFlag() == 5)
			{
				DrawBox(0, 0, 1600, 900, GetColor(0, 255, 255), true);
				DrawFormatString(700, 450, GetColor(255, 0, 0), "����������Ă݂悤");
				DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
				DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
				DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
			}
			break;
		case Scene::END:
			DrawBox(0, 0, 1600, 900, GetColor(0,0, 255), true);
			DrawFormatString(700, 450, GetColor(255, 0, 0), "���Ԑ؂ꂾ");
			DrawFormatString(700, 350, GetColor(255, 0, 0), "Timer_keep;%d ", map_->GetTimer_keep());
			DrawFormatString(700, 400, GetColor(255, 0, 0), "Timer_keep2;%d ", map_->GetTimer_keep2());
			DrawFormatString(0, 200, GetColor(255, 0, 0), "scene;%d ", scene);
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
