#include"Labyrinth.h"
#include<windows.h>

int main()
{
	Labyrinth* labyrinth = new Labyrinth;
	while (labyrinth->GetGoalFlag() != true)
	{
		
		labyrinth->SelectWallCreatePoint();

		labyrinth->CreateLabyrinth(true,true);

		labyrinth->ShowMap();

		//Sleep(1000);
		
		labyrinth->SelectLoop();

		

	}

	labyrinth->ShowMapNumber();
	//labyrinth->MovePlayer();

	delete labyrinth;

}