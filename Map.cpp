#include "Map.h"

void Map::Initialize()
{
	TimerFlag = 0;

}

void Map::Update(Player* player)
{
	if (TimerFlag == 0)
	{
		Timer_GAME++;
	}
	if (TimerFlag == 2)
	{
		Timer_GAME2++;
	}

	if (Timer_GAME == 60)
	{
		Timer += 1;
		Timer_GAME = 0;
	}
	if (Timer_GAME2 == 60)
	{
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


	//左上
	leftTopX = (PlayerTransX - PlayerRadius) / BLOCK_SIZE;
	leftTopY = (PlayerTransY - PlayerRadius) / BLOCK_SIZE;
	//左下
	leftBottomX = (PlayerTransX - PlayerRadius) / BLOCK_SIZE;
	leftBottomY = (PlayerTransY + PlayerRadius - 1) / BLOCK_SIZE;
	//右上
	rightTopX = (PlayerTransX + PlayerRadius - 1) / BLOCK_SIZE;
	rightTopY = (PlayerTransY - PlayerRadius) / BLOCK_SIZE;
	//右下
	rightBottomX = (PlayerTransX + PlayerRadius - 1) / BLOCK_SIZE;
	rightBottomY = (PlayerTransY + PlayerRadius - 1) / BLOCK_SIZE;

	for (int Y = -1; Y < DrawMapChipNumY; Y++)
	{
		for (int X = -1; X < DrawMapChipNumX; X++)
		{

			if (MapData->Data[Y][X] == NONE) {

				if (MapData->Data[rightBottomY][rightBottomX] == NONE && MapData->Data[leftBottomY][leftBottomX] == NONE)
				{
					JumpFlag = 1;
					player->SetJumpFlag(JumpFlag);
				}

				//上

				leftTopY = (PlayerTransY - 1 - PlayerRadius) / BLOCK_SIZE;
				rightTopY = (PlayerTransY - 1 - PlayerRadius) / BLOCK_SIZE;
				//両端
				if (MapData->Data[leftTopY][leftTopX] == BLOCK && MapData->Data[rightTopY][rightTopX] == BLOCK)
				{
					isHit = 1;

					JumpSpeed = 0;
					player->SetJumpSpeed(JumpSpeed);

					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				//右だけ
				else if (MapData->Data[leftTopY][leftTopX] == NONE && MapData->Data[rightTopY][rightTopX] == BLOCK)
				{
					isHit = 1;

					/*JumpFlag = 0;
					player->SetJumpFlag(JumpFlag);*/
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				//左だけ
				else if (MapData->Data[leftTopY][leftTopX] == BLOCK && MapData->Data[rightTopY][rightTopX] == NONE)
				{
					isHit = 1;

					/*JumpFlag = 0;
					player->SetJumpFlag(JumpFlag);*/
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				//左側から当たったとき
				if (MapData->Data[leftBottomY][leftBottomX] == BLOCK && MapData->Data[leftTopY][leftTopX] == BLOCK)
				{
					PlayerTransX -= 1;
					player->SetPlayerTransX(PlayerTransX);
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				else if (MapData->Data[leftBottomY][leftBottomX] == NONE && MapData->Data[leftTopY][leftTopX] == BLOCK)
				{
					PlayerTransX -= 1;
					player->SetPlayerTransX(PlayerTransX);
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}

				if (player->GetJumpFlag() == 1)
				{
					if (MapData->Data[leftBottomY][leftBottomX] == BLOCK && MapData->Data[leftTopY][leftTopX] == NONE)
					{
						PlayerTransX -= 1;
						player->SetPlayerTransX(PlayerTransX);
						PlayerTransY += 1;
						player->SetPlayerTransY(PlayerTransY);
					}
				}
				
				//右側から当たったとき
				if (MapData->Data[rightBottomY][rightBottomX] == BLOCK && MapData->Data[rightTopY][rightTopX] == BLOCK)
				{
					PlayerTransX += 1;
					player->SetPlayerTransX(PlayerTransX);
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				else if (MapData->Data[rightBottomY][rightBottomX] == NONE && MapData->Data[rightTopY][rightTopX] == BLOCK)
				{
					PlayerTransX += 1;
					player->SetPlayerTransX(PlayerTransX);
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}

				if (player->GetJumpFlag() == 1 )
				{
					if (MapData->Data[rightBottomY][rightBottomX] == BLOCK && MapData->Data[rightTopY][rightTopX] == NONE)
					{
						PlayerTransX += 1;
						player->SetPlayerTransX(PlayerTransX);
						PlayerTransY += 1;
						player->SetPlayerTransY(PlayerTransY);
					}
				}
				
				//下

				rightBottomY = (PlayerTransY + 1 + PlayerRadius) / BLOCK_SIZE;
				leftBottomY = (PlayerTransY + 1 + PlayerRadius) / BLOCK_SIZE;
				/**ジャンプ後の着地**/
				if (MapData->Data[leftBottomY][leftBottomX] == BLOCK) {
					// 両端
					if (MapData->Data[leftBottomY][leftBottomX] == BLOCK && MapData->Data[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
					// 右下
					else if (MapData->Data[leftBottomY][leftBottomX] == NONE && MapData->Data[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
					// 左下
					else if (MapData->Data[leftBottomY][leftBottomX] == BLOCK && MapData->Data[rightBottomY][rightBottomX] == NONE) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
				}

				if (MapData->Data[rightBottomY][rightBottomX] == BLOCK) {
					if (MapData->Data[leftBottomY][leftBottomX] == BLOCK && MapData->Data[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
					else if (MapData->Data[leftBottomY][leftBottomX] == NONE && MapData->Data[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
					else if (MapData->Data[leftBottomY][leftBottomX] == BLOCK && MapData->Data[rightBottomY][rightBottomX] == NONE) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
				}

				/**/



		//右
				rightTopX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
				rightBottomX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
				if (MapData->Data[rightTopY][rightTopX] == BLOCK && MapData->Data[rightBottomY][rightBottomX] == BLOCK)
				{
					isHit = 3;
					PlayerTransX -= PlayerMove;
					player->SetPlayerTransX(PlayerTransX);
				}
				//左
				leftTopX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
				leftBottomX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
				if (MapData->Data[leftTopY][leftTopX] == BLOCK && MapData->Data[leftBottomY][leftBottomX] == BLOCK)
				{
					isHit = 4;
					PlayerTransX += PlayerMove;
					player->SetPlayerTransX(PlayerTransX);
				}
			}
			//右
			rightTopX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
			rightBottomX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
			if (MapData->Data[rightTopY][rightTopX] == KUSO && MapData->Data[rightBottomY][rightBottomX] == KUSO)
			{
				isHit = 3;
				PlayerTransX -= PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}
			if (MapData->Data[rightTopY][rightTopX] == WALL && MapData->Data[rightBottomY][rightBottomX] == WALL)
			{
				isHit = 3;
				PlayerTransX -= PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}
			//左
			leftTopX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
			leftBottomX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
			if (MapData->Data[leftTopY][leftTopX] == KUSO && MapData->Data[leftBottomY][leftBottomX] == KUSO)
			{
				isHit = 4;
				PlayerTransX += PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}
			if (MapData->Data[leftTopY][leftTopX] == WALL && MapData->Data[leftBottomY][leftBottomX] == WALL)
			{
				isHit = 4;
				PlayerTransX += PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}


			if (MapData->Data[leftTopY][leftTopX] == GOAL && MapData->Data[rightTopY][rightTopX] == GOAL ||
				MapData->Data[rightBottomY][rightBottomX] == GOAL && MapData->Data[leftBottomY][leftBottomX] == GOAL ||
				MapData->Data[rightTopY][rightTopX] == GOAL && MapData->Data[rightBottomY][rightBottomX] == GOAL ||
				MapData->Data[leftTopY][leftTopX] == GOAL && MapData->Data[leftBottomY][leftBottomX] == GOAL)
			{
				if (TimerFlag == 0)
				{
					TimerFlag = 1;
					Timer_keep = Timer;
					player->Initialize();

				}

				if (TimerFlag == 2)
				{
					TimerFlag = 3;
					Timer_keep2 = Timer_2;
					player->Initialize();

				}

				if (TimerFlag == 3)
				{
					if (Timer >= 0.01 && Timer == Timer_2)
					{
						TimerFlag = 4;
					}
					else
					{
						TimerFlag = 5;
					}
				}
			}
		}
	}
}

void Map::Draw(int block, int goal)
{
	// 描画するマップチップの数をセット
	DrawMapChipNumX = 2000 / BLOCK_SIZE;
	DrawMapChipNumY = 1000 / BLOCK_SIZE;

	for (int Y = 0; Y < DrawMapChipNumY; Y++)
	{
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
