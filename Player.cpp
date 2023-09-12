#include "Player.h"

void Player::Initialize()
{
	PlayerTransX = 100;
	PlayerTransY = 847;
	Playerradius = 16.0f;
	JumpFlag = 1;
}

void Player::Update(char* keys, char* oldkeys)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (keys[KEY_INPUT_RIGHT] == 1 || key & PAD_INPUT_RIGHT) {
		PlayerTransX += move;
	}
	if (keys[KEY_INPUT_LEFT] == 1 || key & PAD_INPUT_LEFT) {
		PlayerTransX -= move;
	}
	Jamp(keys, oldkeys);
}

void Player::Draw()
{
	DrawBox((int)(PlayerTransX + Playerradius), (int)(PlayerTransY + Playerradius), (int)(PlayerTransX - Playerradius), (int)(PlayerTransY - Playerradius)
		, GetColor(255, 255, 255), true);

	/*DrawFormatString(0, 40, GetColor(255, 0, 0), "PlayerTransX;%f PlayerTransY;%f", PlayerTransX, PlayerTransY);
	DrawFormatString(500, 40, GetColor(255, 0, 0), "PlayerMove:%f", move);*/
}

void Player::Jamp(char* keys, char* oldkeys)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (JumpFlag == 1) {
		JumpSpeed = JumpSpeed + 0.5f;
	}
	if (keys[KEY_INPUT_UP] && JumpFlag == false || key & PAD_INPUT_2 && JumpFlag == false) {
		if (JumpFlag == 0) {
			JumpFlag = 1;
			JumpSpeed = -11;
		}
	}
	if (PlayerTransY >= 847) {
		PlayerTransY = 847;
	}

	PlayerTransY = PlayerTransY + JumpSpeed;
}
