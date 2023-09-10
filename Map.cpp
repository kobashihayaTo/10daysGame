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

	//行
	for (int Y = 0; Y <= maprows; Y++) {
		//行の要素(列)
		for (int X = 0; X <= mapcois; X++) {

			if (map[Y][X] == NONE) {

				if (map[rightBottomY][rightBottomX] == NONE && map[leftBottomY][leftBottomX] == NONE)
				{
					JumpFlag = 1;
					player->SetJumpFlag(JumpFlag);
				}

				//上

				leftTopY = (PlayerTransY - 1 - PlayerRadius) / BLOCK_SIZE;
				rightTopY = (PlayerTransY - 1 - PlayerRadius) / BLOCK_SIZE;
				//両端
				if (map[leftTopY][leftTopX] == BLOCK && map[rightTopY][rightTopX] == BLOCK)
				{
					isHit = 1;

					JumpSpeed = 0;
					player->SetJumpSpeed(JumpSpeed);

					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				//右だけ
				else if (map[leftTopY][leftTopX] == NONE && map[rightTopY][rightTopX] == BLOCK)
				{
					isHit = 1;

					/*JumpFlag = 0;
					player->SetJumpFlag(JumpFlag);*/
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				//左だけ
				else if (map[leftTopY][leftTopX] == BLOCK && map[rightTopY][rightTopX] == NONE)
				{
					isHit = 1;

					/*JumpFlag = 0;
					player->SetJumpFlag(JumpFlag);*/
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				//左側から当たったとき
				if (map[leftBottomY][leftBottomX] == BLOCK && map[leftTopY][leftTopX] == BLOCK)
				{
					PlayerTransX -= 1;
					player->SetPlayerTransX(PlayerTransX);
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				else if (map[leftBottomY][leftBottomX] == NONE && map[leftTopY][leftTopX] == BLOCK)
				{
					PlayerTransX -= 1;
					player->SetPlayerTransX(PlayerTransX);
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}

				if (player->GetJumpFlag() == 1)
				{
					if (map[leftBottomY][leftBottomX] == BLOCK && map[leftTopY][leftTopX] == NONE)
					{
						PlayerTransX -= 1;
						player->SetPlayerTransX(PlayerTransX);
						PlayerTransY += 1;
						player->SetPlayerTransY(PlayerTransY);
					}
				}
				
				//右側から当たったとき
				if (map[rightBottomY][rightBottomX] == BLOCK && map[rightTopY][rightTopX] == BLOCK)
				{
					PlayerTransX += 1;
					player->SetPlayerTransX(PlayerTransX);
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}
				else if (map[rightBottomY][rightBottomX] == NONE && map[rightTopY][rightTopX] == BLOCK)
				{
					PlayerTransX += 1;
					player->SetPlayerTransX(PlayerTransX);
					PlayerTransY += 1;
					player->SetPlayerTransY(PlayerTransY);
				}

				if (player->GetJumpFlag() == 1 )
				{
					if (map[rightBottomY][rightBottomX] == BLOCK && map[rightTopY][rightTopX] == NONE)
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
				if (map[leftBottomY][leftBottomX] == BLOCK) {
					// 両端
					if (map[leftBottomY][leftBottomX] == BLOCK && map[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
					// 右下
					else if (map[leftBottomY][leftBottomX] == NONE && map[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
					// 左下
					else if (map[leftBottomY][leftBottomX] == BLOCK && map[rightBottomY][rightBottomX] == NONE) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
				}

				if (map[rightBottomY][rightBottomX] == BLOCK) {
					if (map[leftBottomY][leftBottomX] == BLOCK && map[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
					else if (map[leftBottomY][leftBottomX] == NONE && map[rightBottomY][rightBottomX] == BLOCK) {
						JumpFlag = 0;
						JumpSpeed = 0;
						player->SetJumpFlag(JumpFlag);
						player->SetJumpSpeed(JumpSpeed);
					}
					else if (map[leftBottomY][leftBottomX] == BLOCK && map[rightBottomY][rightBottomX] == NONE) {
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
				if (map[rightTopY][rightTopX] == BLOCK && map[rightBottomY][rightBottomX] == BLOCK)
				{
					isHit = 3;
					PlayerTransX -= PlayerMove;
					player->SetPlayerTransX(PlayerTransX);
				}
				//左
				leftTopX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
				leftBottomX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
				if (map[leftTopY][leftTopX] == BLOCK && map[leftBottomY][leftBottomX] == BLOCK)
				{
					isHit = 4;
					PlayerTransX += PlayerMove;
					player->SetPlayerTransX(PlayerTransX);
				}
			}



			//上

			//leftTopY = (PlayerTransY - 1 - PlayerRadius) / BLOCK_SIZE;
			//rightTopY = (PlayerTransY - 1 - PlayerRadius) / BLOCK_SIZE;
			////両端
			//if (map[leftTopY][leftTopX] == KUSO && map[rightTopY][rightTopX] == KUSO)
			//{
			//	isHit = 1;

			//	PlayerTransY += 1;
			//	player->SetPlayerTransY(PlayerTransY);
			//}
			////右だけ
			//else if (map[leftTopY][leftTopX] == NONE && map[rightTopY][rightTopX] == KUSO)
			//{
			//	isHit = 1;

			//	/*JumpFlag = 0;
			//	player->SetJumpFlag(JumpFlag);*/
			//	PlayerTransY += 1;
			//	player->SetPlayerTransY(PlayerTransY);
			//}
			////左だけ
			//else if (map[leftTopY][leftTopX] == KUSO && map[rightTopY][rightTopX] == NONE)
			//{
			//	isHit = 1;

			//	/*JumpFlag = 0;
			//	player->SetJumpFlag(JumpFlag);*/
			//	PlayerTransY += 1;
			//	player->SetPlayerTransY(PlayerTransY);
			//}
			////左側から当たったとき
			//if (map[leftBottomY][leftBottomX] == KUSO && map[leftTopY][leftTopX] == KUSO)
			//{
			//	PlayerTransX -= 1;
			//	player->SetPlayerTransX(PlayerTransX);
			//	PlayerTransY += 1;
			//	player->SetPlayerTransY(PlayerTransY);
			//}
			//else if (map[leftBottomY][leftBottomX] == NONE && map[leftTopY][leftTopX] == KUSO)
			//{
			//	PlayerTransX -= 1;
			//	player->SetPlayerTransX(PlayerTransX);
			//	PlayerTransY += 1;
			//	player->SetPlayerTransY(PlayerTransY);
			//}

			//if (player->GetJumpFlag() == 1)
			//{
			//	if (map[leftBottomY][leftBottomX] == KUSO && map[leftTopY][leftTopX] == NONE)
			//	{
			//		PlayerTransX -= 1;
			//		player->SetPlayerTransX(PlayerTransX);
			//		PlayerTransY += 1;
			//		player->SetPlayerTransY(PlayerTransY);
			//	}
			//}

			////右側から当たったとき
			//if (map[rightBottomY][rightBottomX] == KUSO && map[rightTopY][rightTopX] == KUSO)
			//{
			//	PlayerTransX += 1;
			//	player->SetPlayerTransX(PlayerTransX);
			//	PlayerTransY += 1;
			//	player->SetPlayerTransY(PlayerTransY);
			//}
			//else if (map[rightBottomY][rightBottomX] == NONE && map[rightTopY][rightTopX] == KUSO)
			//{
			//	PlayerTransX += 1;
			//	player->SetPlayerTransX(PlayerTransX);
			//	PlayerTransY += 1;
			//	player->SetPlayerTransY(PlayerTransY);
			//}

			//if (player->GetJumpFlag() == 1)
			//{
			//	if (map[rightBottomY][rightBottomX] == KUSO && map[rightTopY][rightTopX] == NONE)
			//	{
			//		PlayerTransX += 1;
			//		player->SetPlayerTransX(PlayerTransX);
			//		PlayerTransY += 1;
			//		player->SetPlayerTransY(PlayerTransY);
			//	}
			//}

			//下

			//rightBottomY = (PlayerTransY + 1 + PlayerRadius) / BLOCK_SIZE;
			//leftBottomY = (PlayerTransY + 1 + PlayerRadius) / BLOCK_SIZE;
			///**ジャンプ後の着地**/
			//if (map[leftBottomY][leftBottomX] == KUSO) {
			//	 両端
			//	if (map[leftBottomY][leftBottomX] == KUSO && map[rightBottomY][rightBottomX] == KUSO) {
			//		JumpFlag = 0;
			//		JumpSpeed = 0;
			//		player->SetJumpFlag(JumpFlag);
			//		player->SetJumpSpeed(JumpSpeed);
			//	}
			//	 右下
			//	else if (map[leftBottomY][leftBottomX] == NONE && map[rightBottomY][rightBottomX] == KUSO) {
			//		JumpFlag = 0;
			//		JumpSpeed = 0;
			//		player->SetJumpFlag(JumpFlag);
			//		player->SetJumpSpeed(JumpSpeed);
			//	}
			//	 左下
			//	else if (map[leftBottomY][leftBottomX] == KUSO && map[rightBottomY][rightBottomX] == NONE) {
			//		JumpFlag = 0;
			//		JumpSpeed = 0;
			//		player->SetJumpFlag(JumpFlag);
			//		player->SetJumpSpeed(JumpSpeed);
			//	}
			//}

			//if (map[rightBottomY][rightBottomX] == KUSO) {
			//	if (map[leftBottomY][leftBottomX] == KUSO && map[rightBottomY][rightBottomX] == KUSO) {
			//		JumpFlag = 0;
			//		JumpSpeed = 0;
			//		player->SetJumpFlag(JumpFlag);
			//		player->SetJumpSpeed(JumpSpeed);
			//	}
			//	else if (map[leftBottomY][leftBottomX] == NONE && map[rightBottomY][rightBottomX] == KUSO) {
			//		JumpFlag = 0;
			//		JumpSpeed = 0;
			//		player->SetJumpFlag(JumpFlag);
			//		player->SetJumpSpeed(JumpSpeed);
			//	}
			//	else if (map[leftBottomY][leftBottomX] == KUSO && map[rightBottomY][rightBottomX] == NONE) {
			//		JumpFlag = 0;
			//		JumpSpeed = 0;
			//		player->SetJumpFlag(JumpFlag);
			//		player->SetJumpSpeed(JumpSpeed);
			//	}
			//}

			/**/

			//右
			rightTopX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
			rightBottomX = (PlayerTransX + 1 + PlayerRadius) / BLOCK_SIZE;
			if (map[rightTopY][rightTopX] == KUSO && map[rightBottomY][rightBottomX] == KUSO)
			{
				isHit = 3;
				PlayerTransX -= PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}
			if (map[rightTopY][rightTopX] == WALL && map[rightBottomY][rightBottomX] == WALL)
			{
				isHit = 3;
				PlayerTransX -= PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}
			//左
			leftTopX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
			leftBottomX = (PlayerTransX - 1 - PlayerRadius) / BLOCK_SIZE;
			if (map[leftTopY][leftTopX] == KUSO && map[leftBottomY][leftBottomX] == KUSO)
			{
				isHit = 4;
				PlayerTransX += PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}
			if (map[leftTopY][leftTopX] == WALL && map[leftBottomY][leftBottomX] == WALL)
			{
				isHit = 4;
				PlayerTransX += PlayerMove;
				player->SetPlayerTransX(PlayerTransX);
			}


			if (map[leftTopY][leftTopX] == GOAL && map[rightTopY][rightTopX] == GOAL ||
				map[rightBottomY][rightBottomX] == GOAL && map[leftBottomY][leftBottomX] == GOAL ||
				map[rightTopY][rightTopX] == GOAL && map[rightBottomY][rightBottomX] == GOAL ||
				map[leftTopY][leftTopX] == GOAL && map[leftBottomY][leftBottomX] == GOAL)
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
	//行の描画
	for (int Y = 0; Y <= maprows; Y++) {
		//行の要素(列)の描画
		for (int X = 0; X <= mapcois; X++) {
			if (map[Y][X] == BLOCK) {
				DrawGraph(X * BLOCK_SIZE, Y * BLOCK_SIZE, block, true);
			}
			if (map[Y][X] == GOAL) {
				DrawGraph(X * BLOCK_SIZE, Y * BLOCK_SIZE, goal, true);
			}
			if (map[Y][X] == WALL) {
				DrawGraph(X * BLOCK_SIZE, Y * BLOCK_SIZE, block, true);
			}
		}
	}

	/*DrawFormatString(0, 60, GetColor(255, 0, 0), "JumpSpeed;%f ", JumpSpeed);
	DrawFormatString(0, 80, GetColor(255, 0, 0), "JumpFlag;%d ", JumpFlag);*/

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
