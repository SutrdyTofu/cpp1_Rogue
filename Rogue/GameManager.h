#pragma once
#include "GameplayValue.h"
#include "DrawUI.h"
#include "SkillManager.h"
#include "State.h"
#include "Boss.h"

class GameManager {
	public:
		GameManager();
		void GameStart();
		int PlayerInputNumber(int range);
		int StageChoice();
		void StageEntrance(State *player,State enemyList[ENEMY_COUNT], int mapType);
		void BattleMap(State *player,State enemyList[ENEMY_COUNT]);
		void optimizationMap(State *player);
		void Map_Main_cpp_Error(State* player);
		void LegacyCodeMap(State* player,State enemyList[ENEMY_COUNT]);
		void Turn(int *isPlayer,State *player,State *enemey);
		void GameOver();
	private:
		DrawUI drawUI;
		SkillManager skillManager;
		Boss boss;
		int nodeMap[MAP_ROW][MAP_COL] = MAP_NODE;
		int currentNode;
		int mapDetail[MAP_ROW][MAP_COL] = MAP_DETAIL;
		string mapNameList[MAP_NAME_COUNT] = MAP_NAME_LIST;
		int battleCount;
};