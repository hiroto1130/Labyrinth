#ifndef LABYRINTH_H
#define LABYRINTH_H

#include<stdio.h>
#include <iostream>
#include <random>

class Labyrinth
{
private:
	// 死ぬ領域を作るかどうか
	bool MakeDeadFieldFlag;

	// ループしてしまう領域を作るかどうか
	bool MakeLoopFieldFlag;

	static const int MapHeight = 11;
	static const int MapWidth = 11;
	
	// 壁が作成出来る作成範囲の最小範囲
	static const int BeginCreateWall = 2;

	// 壁が作成出来る作成範囲の最大範囲
	static const int EndCreateWall = 8;

	// マップの二次元配列
	int Map[MapHeight][MapWidth] =
	{ { 2,2,2,2,2,2,2,2,2,2,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2}, 
	  { 2,0,0,0,0,0,0,0,0,0,2},
	  { 2,2,2,2,2,2,2,2,2,2,2}} ;
	  
	// 行動を入れる変数
	int MoveSelect;
	// 行動が選択されたかどうかのFlag
	int SelectFlag = false;

	// マップ上のプレイヤーのいる位置(高さ)
	int PlayerSpotHeight = 1;

	// マップ上のプレイヤーのいる位置(横)
	int PlayerSpotWidth  = 1;

	// ゴールしたかどうかのFlag
	bool GoalFlag = false;

	// 壁を作る方向
	bool InputDirectionFlag = false;
	int CreateDirection;
	int NotCreateDirection = 0;
	
		// 壁作成開始地点
	int CreatePointCol;
	bool InputColFlag = false;
	int CreatePointRow;
	bool InputRowFlag = false;

    // 何番目に作成された壁の情報
	int WallNumber = 2;

	// ちゃんと値が入力されたかどうか
	bool InputCheckFlag = false;

	// モードの選択
	int SelectMode;

	int map_height = 2;
	int map_width  = 2;

public:

	Labyrinth();
	~Labyrinth();

	// ループするスペースを作るか
	bool GetMakeLoopFieldFlag();
	void SetMakeLoopFieldFlag(bool LoopFieldFlag);

	// 迷路上で迷路が死ぬスペースを作るかどうか
	bool GetMakeDeadFieldFlag();
	void SetMakeDeadFieldFlag(bool DeadFieldFlag);
	
	// 行動選択がされてるかどうか
	bool GetSelectFlag();
	void SetSelectFlag(bool SelectFlag);
	
	// ゴールしたかどうか
	bool GetGoalFlag();
	void SetGoalFlag(bool GoalFlag);

	// 壁の作成する場所の選定
	void SelectWallCreatePoint();

	// マップ表示関数
	void ShowMap();
	
	// 配列描画
	void ShowMapNumber();

	// 迷路生成関数
	void CreateLabyrinth(bool DeadFieldFlag, bool LoopFieldFlag);

	// 自キャラ操作関数
	void MovePlayer();

	// 次のループを選ぶ
	void SelectLoop();

	// 左右が道か
	int RoadJudge();

	// 迷路が完成しているかどうか
	bool CompletionCheck();
};

enum Move
{
	up,
	down,
	right,
	left,
	dead,

};

enum Map
{
	Road,
	Player,
	Wall,
	
};

#endif