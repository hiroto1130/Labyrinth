#include"Labyrinth.h"

Labyrinth::Labyrinth()
{
	MakeDeadFieldFlag = false;
	MakeLoopFieldFlag = false;

}

Labyrinth::~Labyrinth()
{
	MakeDeadFieldFlag = false;
	MakeLoopFieldFlag = false;

	for (int a = 0; a < MapHeight; a++)
	{
		for (int b = 0; b < MapWidth; b++)
		{
			Map[a][b] = 0;
		}
	}
}

bool Labyrinth::GetMakeDeadFieldFlag()
{
	return MakeDeadFieldFlag;
}

bool Labyrinth::GetMakeLoopFieldFlag()
{
	return MakeLoopFieldFlag;
}

bool Labyrinth::GetSelectFlag()
{
	return SelectFlag;
}

bool Labyrinth::GetGoalFlag()
{
	return GoalFlag;
}

void Labyrinth::SetMakeDeadFieldFlag(bool DeadFieldFlag)
{
	MakeDeadFieldFlag = DeadFieldFlag;
}

void Labyrinth::SetMakeLoopFieldFlag(bool LoopFieldFlag)
{
	MakeLoopFieldFlag = LoopFieldFlag;
}

void Labyrinth::SetSelectFlag(bool selectFlag)
{
	SelectFlag = selectFlag;
}

void Labyrinth::SetGoalFlag(bool goalFlag)
{
	GoalFlag = goalFlag;
}

void Labyrinth::ShowMap()
{
	for (int a = 0; a < MapHeight; a++)
	{
		for (int b = 0; b < MapWidth; b++)
		{

			if (Map[a][b] == Map::Road)
			{
				printf("　");
			}
			else
				if (Map[a][b] == Map::Player)
				{
					printf("Ｐ");
				}
				else
				{
					printf("■");
				}
		}
		printf("\n");
	}
}

void Labyrinth::ShowMapNumber()
{
	printf("\n");

	for (int a =0; a < MapHeight;a ++)
	{
		for (int i = 0; i < MapWidth; i++)
		{
			printf("%d ",Map[a][i]);
		}
		printf("\n");
	}

}

int Labyrinth::RoadJudge()
{
	//  -------------- 上が道かどうか ----------------  ----------------- 下が道かどうか --------------  -------------- 左が道かどうか -----------------  -------------- 右が道かどうか ----------------
	if ((Map[CreatePointRow - 1][CreatePointCol] == 0 && Map[CreatePointRow + 1][CreatePointCol] == 0) && (Map[CreatePointRow][CreatePointCol - 1] == 0 && Map[CreatePointRow][CreatePointCol + 1] == 0))
	{
		return 4;
	}

}



void Labyrinth::SelectWallCreatePoint()
{
	while (InputCheckFlag != true && GoalFlag == false)
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> Rand(BeginCreateWall, EndCreateWall);
		
		while (InputColFlag != true)
		{
			CreatePointCol = Rand(mt);

			if (CreatePointCol % 2 == 0)
			{
				InputColFlag = true;
			}
		}

		while (InputRowFlag != true)
		{
			CreatePointRow = Rand(mt);
			
			if (CreatePointRow % 2 == 0)
			{
				InputRowFlag = true;
			}

		}

		if (CreatePointRow % 2 != 0)
		{
			while (true)
			{

			}
		}
		
		if (CreatePointCol % 2 != 0)
		{
			while (true)
			{

			}
		}


		// プレイヤー or 既存の壁の上では無いかのチェック
		if (Map[CreatePointRow][CreatePointCol] == Map::Road)
		{
			InputCheckFlag = true;
			WallNumber += 1;
			Map[CreatePointRow][CreatePointCol] = WallNumber;
			
		}
		else
		{
			// 再度 Col Row を抽選
			InputColFlag = false;
			InputRowFlag = false;

			// 終了するかどうかのチェック
			if (CompletionCheck() == true)
			{
				GoalFlag = true;
			};
		}
	}
}

void Labyrinth::CreateLabyrinth(bool DeadFieldFlag, bool LoopFieldFlag)
{
	SetMakeLoopFieldFlag(LoopFieldFlag);
	SetMakeDeadFieldFlag(DeadFieldFlag);

	// デッドスペースを作成するか
	// true = 作成 false = 未作成 
	if (GetMakeDeadFieldFlag() != true) {}

	// ループ処理を作るかどうか
	// true = 作成 false = 未作成 
	if (GetMakeLoopFieldFlag() != true) {}

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> Rand(0, 3);
	
	while (InputDirectionFlag != true)
	{
		CreateDirection = Rand(mt);

		if (NotCreateDirection != CreateDirection)
		{
			InputDirectionFlag = true;
		}
	}

	switch (CreateDirection)
	{
	case up:
		NotCreateDirection = down;

		if(Map[CreatePointRow - 2][CreatePointCol] == WallNumber)
		{ 
			Map[CreatePointRow += 1][CreatePointCol] = WallNumber;
			Map[CreatePointRow += 1][CreatePointCol] = WallNumber;

		}else if ((Map[CreatePointRow - 1][CreatePointCol] == 0 && Map[CreatePointRow- 2][CreatePointCol] == 0))
		{
			Map[CreatePointRow -= 1][CreatePointCol] = WallNumber;
			Map[CreatePointRow -= 1][CreatePointCol] = WallNumber;

		}
		else if (Map[CreatePointRow - 1][CreatePointCol] == 0 && Map[CreatePointRow - 2][CreatePointCol] > 0)
		{
			Map[CreatePointRow -= 1][CreatePointCol] = WallNumber;


			NotCreateDirection = dead;
			InputCheckFlag = false;
			//InputDirectionFlag = false;
		}

		InputDirectionFlag = false;

		break;
	case down:
		NotCreateDirection = up;

		if (Map[CreatePointRow + 2][CreatePointCol] == WallNumber)
		{
			Map[CreatePointRow -= 1][CreatePointCol] = WallNumber;
			Map[CreatePointRow -= 1][CreatePointCol] = WallNumber;

		}else if ((Map[CreatePointRow + 1][CreatePointCol] == 0 && Map[CreatePointRow + 2][CreatePointCol] == 0))
		{
			Map[CreatePointRow += 1][CreatePointCol] = WallNumber;
			Map[CreatePointRow += 1][CreatePointCol] = WallNumber;
		}
		else if (Map[CreatePointRow + 1][CreatePointCol] == 0 && Map[CreatePointRow + 2][CreatePointCol] > 0)
		{
			Map[CreatePointRow += 1][CreatePointCol] = WallNumber;
			Map[CreatePointRow += 1][CreatePointCol] = WallNumber;

			NotCreateDirection = dead;
			InputCheckFlag = false;
			//InputDirectionFlag = false;
		}

		InputDirectionFlag = false;
		break;
	case right:
		NotCreateDirection = left;

		if (Map[CreatePointRow][CreatePointCol + 2] == WallNumber)
		{
			Map[CreatePointRow][CreatePointCol -= 1] = WallNumber;
			Map[CreatePointRow][CreatePointCol -= 1] = WallNumber;

		}else if ((Map[CreatePointRow][CreatePointCol + 1] == 0 && Map[CreatePointRow][CreatePointCol + 2] == 0))
		{
			Map[CreatePointRow][CreatePointCol += 1] = WallNumber;
			Map[CreatePointRow][CreatePointCol += 1] = WallNumber;
		}
		else if (Map[CreatePointRow][CreatePointCol + 1] == 0 && Map[CreatePointRow][CreatePointCol + 2] > 0)
		{
			Map[CreatePointRow][CreatePointCol += 1] = WallNumber;
			Map[CreatePointRow][CreatePointCol += 1] = WallNumber;

			NotCreateDirection = dead;
			InputCheckFlag = false;
			//InputDirectionFlag = false;
		}

		InputDirectionFlag = false;
		
		break;
	case left:
		NotCreateDirection = right;

		if (Map[CreatePointRow][CreatePointCol - 2] == WallNumber)
		{
			Map[CreatePointRow][CreatePointCol += 1] = WallNumber;
			Map[CreatePointRow][CreatePointCol += 1] = WallNumber;

		}else if ((Map[CreatePointRow][CreatePointCol - 1] == 0 && Map[CreatePointRow][CreatePointCol - 2] == 0))
		{
			Map[CreatePointRow][CreatePointCol -= 1] = WallNumber;
			Map[CreatePointRow][CreatePointCol -= 1] = WallNumber;
		}
		else if (Map[CreatePointRow][CreatePointCol - 1] == 0 && Map[CreatePointRow][CreatePointCol - 2] > 0)
		{
			Map[CreatePointRow][CreatePointCol -= 1] = WallNumber;
			Map[CreatePointRow][CreatePointCol -= 1] = WallNumber;

			NotCreateDirection = dead;
			InputCheckFlag = false;
			//InputDirectionFlag = false;
		}

		InputDirectionFlag = false;
		break;

	}

}

void Labyrinth::MovePlayer()
{
	/*
	while (GetSelectFlag() == false)
	{

		printf("移動したい方向を決めてください \n");
		printf("↑ : 0 , ↓ : 1 , → : 2 , ← : 3 \n");

		std::cin >> MoveSelect;

		if (MoveSelect < 4)
		{

			if (MoveSelect == up)
			{
				if (Map[PlayerSpotHeight - 1][PlayerSpotWidth] < 2 && PlayerSpotHeight > 1)
				{
					SetSelectFlag(true);
					Map[PlayerSpotHeight][PlayerSpotWidth] = 0;
					Map[PlayerSpotHeight -= 1][PlayerSpotWidth] = 1;
					std::cin.clear();
					std::cin.ignore();
					break;
				}
				else
				{
					printf("壁です　再入力しな!!! \n");
					std::cin.clear();
					std::cin.ignore();
				}
			}
			else
				if (MoveSelect == down)
				{
					if (Map[PlayerSpotHeight + 1][PlayerSpotWidth] < 2 && PlayerSpotHeight < 9)
					{
						SetSelectFlag(true);
						Map[PlayerSpotHeight][PlayerSpotWidth] = 0;
						Map[PlayerSpotHeight += 1][PlayerSpotWidth] = 1;
						std::cin.clear();
						std::cin.ignore();
						break;
					}
					else
					{
						printf("壁です　再入力しな!!! \n");
						std::cin.clear();
						std::cin.ignore();
					}
				}


			if (MoveSelect == right)
			{
				if (Map[PlayerSpotHeight][PlayerSpotWidth + 1] < 2 && PlayerSpotWidth < 9)
				{
					SetSelectFlag(true);
					Map[PlayerSpotHeight][PlayerSpotWidth] = 0;
					Map[PlayerSpotHeight][PlayerSpotWidth += 1] = 1;
					std::cin.clear();
					std::cin.ignore();
					break;
				}
				else
				{
					printf("壁です　再入力しな!!! \n");
					std::cin.clear();
					std::cin.ignore();
				}
			}
			else
				if (MoveSelect == left)
				{
					if (Map[PlayerSpotHeight][PlayerSpotWidth - 1] < 2 && PlayerSpotWidth > 1)
					{
						SetSelectFlag(true);
						Map[PlayerSpotHeight][PlayerSpotWidth] = 0;
						Map[PlayerSpotHeight][PlayerSpotWidth -= 1] = 1;
						std::cin.clear();
						std::cin.ignore();
						break;
					}
					else
					{
						printf("壁です　再入力しな!!! \n");
						std::cin.clear();
						std::cin.ignore();
					}
				}
		}
		else
		{
			printf("再入力してください \n");
			std::cin.clear();
			std::cin.ignore();
		}
	}

	std::system("cls");
	SetSelectFlag(false);
	std::cin.clear();
	std::cin.ignore();
	*/
}


void Labyrinth::SelectLoop()
{
	//printf("入力で次のステップに移行 \n");

	//std::cin >> SelectMode;

	if (/*SelectMode >= 0 &&*/ GoalFlag == false)
	{
		std::system("cls");
		//std::cin.clear();
		//std::cin.ignore();
	}

	
}

bool Labyrinth::CompletionCheck()
{
	map_height = 2;
	map_width = 2;
	
	for (int a = 0; a < 4; a++)
	{
		for (int b = 0; b < 4; b++)
		{
			if (Map[map_height][map_width] == 0)
			{

				return false;
			}
			map_width += 2;
		}

		map_width = 2;
		map_height += 2;
	}

	return true;
}