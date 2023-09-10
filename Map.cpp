#include "Map.h"

void Map::Initialize()
{
	TimerFlag = 0;
}

void Map::Update(Player* player)
{
	GetMapNo();

	if (TimerFlag == 0) {
		Timer_GAME++;
	}
	if (TimerFlag == 2) {
		Timer_GAME2++;
	}

	if (Timer_GAME == 60) {
		Timer += 1;
		Timer_GAME = 0;
	}
	if (Timer_GAME2 == 60) {
		Timer_2 += 1;
		Timer_GAME2 = 0;
	}

	PlayerTransX = player->GetPlayerTransX();
	PlayerTransY = player->GetPlayerTransY();
	PlayerRadius = player->GetPlayerRadius();
	PlayerMove = player->GetPlayerMove();

	JumpFlag = player->GetJumpFlag();
	OldJumpFlag = JumpFlag;
	JumpSpeed = player->GetJumpSpeed();

	// ����
	leftTopX = (PlayerTransX - PlayerRadius) / BLOCK_SIZE;
	leftTopY = (PlayerTransY - PlayerRadius) / BLOCK_SIZE;
	// ����
	leftBottomX = (PlayerTransX - PlayerRadius) / BLOCK_SIZE;
	leftBottomY = (PlayerTransY + PlayerRadius - 1) / BLOCK_SIZE;
	// �E��
	rightTopX = (PlayerTransX + PlayerRadius - 1) / BLOCK_SIZE;
	rightTopY = (PlayerTransY - PlayerRadius) / BLOCK_SIZE;
	// �E��
	rightBottomX = (PlayerTransX + PlayerRadius - 1) / BLOCK_SIZE;
	rightBottomY = (PlayerTransY + PlayerRadius - 1) / BLOCK_SIZE;

	for (int Y = 0; Y < DrawMapChipNumY; Y++) {
		for (int X = 0; X < DrawMapChipNumX; X++) {
			/*�@�v���C���[�� BLOCK �̓����蔻��@*/
			if (MapData[MapNo].Data[Y][X] == NONE) {
				if (MapData[MapNo].Data[rightBottomY][rightBottomX] == NONE && MapData[MapNo].Data[leftBottomY][leftBottomX] == NONE) {
					JumpFlag = 1;
					player->SetJumpFlag(JumpFlag);
				}

				// �v���C���[��������u���b�N�ɓ��������Ƃ�
				leftTopY = (PlayerTransY - 1 - PlayerRadius) / BLOCK_SIZE;
				rightTopY = (PlayerTransY - 1 - PlayerRadius) / BLOCK_SIZE;
				// ���[�����������Ƃ�
				if (MapData[MapNo].Data[leftTopY][leftTopX] == BLOCK && MapData[MapNo].Data[rightTopY][rightTopX] == BLOCK) {
					JumpSpeed = 0;
					player->SetJumpSpeed(JumpSpeed);

					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				// �E�������������Ƃ�
				else if (MapData[MapNo].Data[leftTopY][leftTopX] == NONE && MapData[MapNo].Data[rightTopY][rightTopX] == BLOCK) {
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				// ���������������Ƃ�
				else if (MapData[MapNo].Data[leftTopY][leftTopX] == BLOCK && MapData[MapNo].Data[rightTopY][rightTopX] == NONE) {
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}

				// �������瓖�������Ƃ�
				if (MapData[MapNo].Data[leftBottomY][leftBottomX] == BLOCK && MapData[MapNo].Data[leftTopY][leftTopX] == BLOCK) {
					PlayerTransX -= 1;
					player->SetPlayerTransX(PlayerTransX);

					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				else if (MapData[MapNo].Data[leftBottomY][leftBottomX] == NONE && MapData[MapNo].Data[leftTopY][leftTopX] == BLOCK) {
					PlayerTransX -= 1;
					player->SetPlayerTransX(PlayerTransX);

					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}

				if (player->GetJumpFlag() == 1) {
					if (MapData[MapNo].Data[leftBottomY][leftBottomX] == BLOCK && MapData[MapNo].Data[leftTopY][leftTopX] == NONE) {
						PlayerTransX -= 1;
						player->SetPlayerTransX(PlayerTransX);

						PlayerTransY += 1;
						player->SetPlayerTransY(PlayerTransY);
					}
				}

				// �E�����瓖�������Ƃ�
				if (MapData[MapNo].Data[rightBottomY][rightBottomX] == BLOCK && MapData[MapNo].Data[rightTopY][rightTopX] == BLOCK) {
					PlayerTransX += 1;
					player->SetPlayerTransX(PlayerTransX);

					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				else if (MapData[MapNo].Data[rightBottomY][rightBottomX] == NONE && MapData[MapNo].Data[rightTopY][rightTopX] == BLOCK) {
					PlayerTransX += 1;
					player->SetPlayerTransX(PlayerTransX);

					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}

				if (player->GetJumpFlag() == 1) {
					if (MapData[MapNo].Data[rightBottomY][rightBottomX] == BLOCK && MapData[MapNo].Data[rightTopY][rightTopX] == NONE) {
						PlayerTransX += 1;
						player->SetPlayerTransX(PlayerTransX);

						PlayerTransY += 1;
						player->SetPlayerTransY(PlayerTransY);
					}
				}

				// �v���C���[���ォ�瓖�������Ƃ�
				rightBottomY = (PlayerTransY + 1 + PlayerRadius) / BLOCK_SIZE;
				leftBottomY = (PlayerTransY + 1 + PlayerRadius) / BLOCK_SIZE;
				/*�@�W�����v��̒��n�@*/
				// ���[�� BLOCK �ɓ��������Ƃ�
				if (MapData[MapNo].Data[leftBottomY][leftBottomX] == BLOCK) {
					// ���[�����������Ƃ�
					if (MapData[MapNo].Data[leftBottomY][leftBottomX] == BLOCK && MapData[MapNo].Data[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						player->SetJumpFlag(JumpFlag);

						JumpSpeed = 0;
						player->SetJumpSpeed(JumpSpeed);
					}
					// �E�������������Ƃ�
					else if (MapData[MapNo].Data[leftBottomY][leftBottomX] == NONE && MapData[MapNo].Data[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						player->SetJumpFlag(JumpFlag);

						JumpSpeed = 0;
						player->SetJumpSpeed(JumpSpeed);
					}
					// ���������������Ƃ�
					else if (MapData[MapNo].Data[leftBottomY][leftBottomX] == BLOCK && MapData[MapNo].Data[rightBottomY][rightBottomX] == NONE) {
						JumpFlag = 0;
						player->SetJumpFlag(JumpFlag);

						JumpSpeed = 0;
						player->SetJumpSpeed(JumpSpeed);
					}
				}

				// �E�[�� BLOCK �ɓ��������Ƃ�
				if (MapData[MapNo].Data[rightBottomY][rightBottomX] == BLOCK) {
					// ���[�����������Ƃ�
					if (MapData[MapNo].Data[leftBottomY][leftBottomX] == BLOCK && MapData[MapNo].Data[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						player->SetJumpFlag(JumpFlag);

						JumpSpeed = 0;
						player->SetJumpSpeed(JumpSpeed);
					}
					// �E�������������Ƃ�
					else if (MapData[MapNo].Data[leftBottomY][leftBottomX] == NONE && MapData[MapNo].Data[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						player->SetJumpFlag(JumpFlag);

						JumpSpeed = 0;
						player->SetJumpSpeed(JumpSpeed);
					}
					// ���������������Ƃ�
					else if (MapData[MapNo].Data[leftBottomY][leftBottomX] == BLOCK && MapData[MapNo].Data[rightBottomY][rightBottomX] == NONE) {
						JumpFlag = 0;
						player->SetJumpFlag(JumpFlag);

						JumpSpeed = 0;
						player->SetJumpSpeed(JumpSpeed);
					}
				}

				// �E�����瓖�������Ƃ�
				rightTopX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
				rightBottomX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
				if (MapData[MapNo].Data[rightTopY][rightTopX] == BLOCK && MapData[MapNo].Data[rightBottomY][rightBottomX] == BLOCK) {
					PlayerTransX -= PlayerMove;
					player->SetPlayerTransX(PlayerTransX);
				}
				// �������瓖�������Ƃ�
				leftTopX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
				leftBottomX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
				if (MapData[MapNo].Data[leftTopY][leftTopX] == BLOCK && MapData[MapNo].Data[leftBottomY][leftBottomX] == BLOCK) {
					PlayerTransX += PlayerMove;
					player->SetPlayerTransX(PlayerTransX);
				}
			}

			/*�@DUMMY �̓����蔻��@*/
			/*�@WALL �̓����蔻��@*/
			// �E
			rightTopX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
			rightBottomX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
			if (MapData[MapNo].Data[rightTopY][rightTopX] == DUMMY && MapData[MapNo].Data[rightBottomY][rightBottomX] == DUMMY) {
				PlayerTransX -= PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}
			if (MapData[MapNo].Data[rightTopY][rightTopX] == WALL && MapData[MapNo].Data[rightBottomY][rightBottomX] == WALL) {
				PlayerTransX -= PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}

			// ��
			leftTopX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
			leftBottomX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
			if (MapData[MapNo].Data[leftTopY][leftTopX] == DUMMY && MapData[MapNo].Data[leftBottomY][leftBottomX] == DUMMY) {
				PlayerTransX += PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}
			if (MapData[MapNo].Data[leftTopY][leftTopX] == WALL && MapData[MapNo].Data[leftBottomY][leftBottomX] == WALL) {
				PlayerTransX += PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}

			/*�@�S�[���p�����蔻��@*/
			if (MapData[MapNo].Data[leftTopY][leftTopX] == GOAL && MapData[MapNo].Data[rightTopY][rightTopX] == GOAL ||
				MapData[MapNo].Data[rightBottomY][rightBottomX] == GOAL && MapData[MapNo].Data[leftBottomY][leftBottomX] == GOAL ||
				MapData[MapNo].Data[rightTopY][rightTopX] == GOAL && MapData[MapNo].Data[rightBottomY][rightBottomX] == GOAL ||
				MapData[MapNo].Data[leftTopY][leftTopX] == GOAL && MapData[MapNo].Data[leftBottomY][leftBottomX] == GOAL) {
				if (TimerFlag == 0) {
					TimerFlag = 1;
					Timer_keep = Timer;
					player->Initialize();
				}

				if (TimerFlag == 2) {
					TimerFlag = 3;
					Timer_keep2 = Timer_2;
					player->Initialize();
				}

				if (TimerFlag == 3) {
					if (Timer >= 0.01 && Timer == Timer_2) {
						TimerFlag = 4;
					}
					else {
						TimerFlag = 5;
					}
				}
			}
		}
	}
}

void Map::Draw(int block, int goal)
{
	// �`�悷��}�b�v�`�b�v�̐����Z�b�g
	DrawMapChipNumX = 2000 / BLOCK_SIZE;
	DrawMapChipNumY = 1000 / BLOCK_SIZE;

	for (int Y = 0; Y < DrawMapChipNumY; Y++) {
		for (int X = 0; X < DrawMapChipNumX; X++) {
			if (MapData[MapNo].Data[Y][X] == BLOCK) {
				DrawGraph(X * BLOCK_SIZE, Y * BLOCK_SIZE, block, true);
			}
			if (MapData[MapNo].Data[Y][X] == GOAL) {
				DrawGraph(X * BLOCK_SIZE, Y * BLOCK_SIZE, goal, true);
			}
			if (MapData[MapNo].Data[Y][X] == WALL) {
				DrawGraph(X * BLOCK_SIZE, Y * BLOCK_SIZE, block, true);
			}
		}
	}

	DrawFormatString(0, 60, GetColor(255, 0, 0), "TimerFlag;%d ", TimerFlag);
	DrawFormatString(0, 80, GetColor(255, 0, 0), "Timer_GAME;%d ", Timer_GAME);
	DrawFormatString(0, 100, GetColor(255, 0, 0), "Timer_GAME2;%d ", Timer_GAME2);
	DrawFormatString(0, 120, GetColor(255, 0, 0), "Timer_keep;%d ", Timer_keep);
	DrawFormatString(0, 140, GetColor(255, 0, 0), "Timer_keep2;%d ", Timer_keep2);
	DrawFormatString(0, 160, GetColor(255, 0, 0), "Timer;%d ", Timer);
	DrawFormatString(0, 180, GetColor(255, 0, 0), "Timer_2;%d ", Timer_2);
	DrawFormatString(0, 220, GetColor(255, 0, 0), "Hit;%d ", isHit);
}

void Map::AllReset()
{
	Timer_GAME = 0;
	Timer_GAME2 = 0;
	Timer_keep = 0;
	Timer_keep2 = 0;

	Timer = 0;
	Timer_2 = 0;

	TimerFlag = 0;
}

void Map::Reset()
{
	Timer_2 = 0;
	Timer_GAME2 = 0;
	Timer_keep2 = 0;
	TimerFlag = 2;
}
