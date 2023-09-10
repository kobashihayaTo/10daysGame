#pragma once
#include "DxLib.h"

class Player
{
public:
	///<summary>
	///������
	///</summary>
	///<param name="model">���f��</param>
	///<param name="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize();

	///<summary>
	///�X�V
	///</summary>
	void Update(char* keys, char* oldkeys);

	///<summary>
	///�`��
	///</summary>
	void Draw();

	///<summary>
	///�W�����v
	///</summary>
	void Jamp(char* keys, char* oldkeys);

	float GetPlayerTransX() { return PlayerTransX; }
	float GetPlayerTransY() { return PlayerTransY; }
	float GetPlayerRadius() { return Playerradius; }
	float GetPlayerMove() { return move; }

	float GetJumpSpeed() { return JumpSpeed; }
	int GetJumpFlag() { return JumpFlag; }

	void SetPlayerTransX(float PlayerTransX_) { PlayerTransX = PlayerTransX_; }
	void SetPlayerTransY(float PlayerTransY_) { PlayerTransY = PlayerTransY_; }
	void SetPlayerMove(float PlayerMove_) { move = PlayerMove_; }
	void SetJumpSpeed(float JumpSpeed_) { JumpSpeed = JumpSpeed_; }
	void SetJumpFlag(int JumpFlag_) { JumpFlag = JumpFlag_; }

private:

	//�v���C���[-----------
	float PlayerTransX = 100;
	float PlayerTransY = 800;

	float Playerradius = 16.0f;
	float move = 6.0f;


	//--------------------

	//�W�����v---------------------
	bool jflag = false;
	float y_temp = 0;
	float y_prev = 0;
	int jampChange = 25;

	bool dflag = false;

	float JumpSpeed = 1;
	int JumpFlag;
	//----------------------------
};

