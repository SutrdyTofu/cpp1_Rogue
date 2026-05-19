#include "GameManager.h"
#include "GameplayValue.h"
#include "DrawUI.h"
#include "SkillManager.h"

#include <iostream>
#include <string>
#include <random>
#include <windows.h>

using namespace std;

GameManager::GameManager()
{
	boss;
	drawUI;
	skillManager;
	nodeMap;
	mapDetail;
	mapNameList;
	battleCount = 0;
	currentNode = MAP_ROW*10;
}

void GameManager::GameStart()
{
	State player(PLAYER_NAME,"", PLAYER_HP, PLAYER_ATK_MAX, PLAYER_ATK_MIN, PLAYER_DEF_MAX, PLAYER_DEF_MIN, PLAYER_HEAL, PLAYER_EVASION);
	State enemyList[ENEMY_COUNT] = {
		State(ENEMY_SYNTAX_STATE),
		State(ENEMY_LINKER_STATE),
		State(ENEMY_LOGIC_STATE),
		State(ENEMY_MEMORY_STATE),
		State(ENEMY_SEGMENTATION_STATE)
	};

	int playerChoice;
	
	for (int i = 0; i < MAP_ROW; i++) {

		drawUI.ClearScreen();
		drawUI.DrawStatus(player.getName(), "", to_string(player.getHealth()), "");
		drawUI.DrawAsciiMap(ASCII_MAP);
		playerChoice = StageChoice();
		StageEntrance(&player, enemyList, playerChoice);
	}
	

}

int GameManager::StageChoice()
{
	int node[MAP_COL];
	int nextNodeCount = 0;
	int sum = 0;
	string nodeString ="";
	int playerChoice;

	if (currentNode == MAP_ROW*10) {
		for (int i = 0; i < MAP_COL; i++) {
			node[i] = 1;
			nextNodeCount++;
		}
	}
	else {
		sum = this->nodeMap[currentNode / 10][currentNode % 10];
		for (int i = MAP_COL-1; i >= 0; i--) {
			node[i] = sum%10;
			nextNodeCount += node[i];
			sum /= 10;
		}
	}
	
	currentNode -= 10;
	int k = 0;
	for (int i = 0; i < MAP_COL; i++) {
		if(node[i] == 1)
			nodeString += mapNameList[mapDetail[currentNode/10][i]]+" :"+ to_string(++k) + "   ";
	}

	drawUI.DrawTextUI("", nodeString);
	drawUI.DrawInputUI(STRING_SELECT_MAP);
	playerChoice = PlayerInputNumber(nextNodeCount);
	currentNode /= 10;
	currentNode *= 10;
	currentNode += playerChoice - 1;
	return mapDetail[currentNode/10][playerChoice - 1];

}

void GameManager::StageEntrance(State *player, State enemyList[ENEMY_COUNT], int mapType)
{
	player->initSkill();

	switch (mapType)
	{
		case MAP_NAME_UNKNOWN:
			BattleMap(player, enemyList);
			break;
		case MAP_NAME_OPTIMIZATION:
			optimizationMap(player);
			break;
		case MAP_NAME_LEGACECODE:
			LegacyCodeMap(player, enemyList);
			break;
		case MAP_NAME_MAINERROR:
			Map_Main_cpp_Error(player);
			break;
	default:
		break;
	}
}

void GameManager::BattleMap(State *player, State enemyList[ENEMY_COUNT] )
{
	int enemynumber = 0;
	int i = 0;

	battleCount++;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, ENEMY_COUNT-1);

	enemynumber = dis(gen);

	if (battleCount < ENEMY_MAP_DIFFICULTY) {
		enemynumber %= ENEMY_EASY_COUNT;
	}
	else {
		enemynumber = enemynumber % (ENEMY_COUNT - ENEMY_EASY_COUNT) + ENEMY_EASY_COUNT;
	}

	//DebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebugDebug
	//enemynumber = ENEMY_NUMBER_MEMORY;

	State enemy = enemyList[enemynumber];
	drawUI.ClearScreen();
	drawUI.DrawAsciiEnemy(enemy.getAscii());
	drawUI.DrawStatus(player->getName(), enemy.getName(), to_string(player->getHealth()), to_string(enemy.getHealth()));

	while (true) {
		i++;
		i %= 2;
		Turn(&i,player,&enemy);
		if (player->getHealth() <= 0) {
			GameOver();
			break;
		}
		else if (enemy.getHealth() <= 0) {
			drawUI.DrawTextUI("Enemy Defeated!!", "Press any key to continue.");
			cin.ignore();
			cin.get();
			break;
		}
	}

}

void GameManager::optimizationMap(State* player) {


	this->drawUI.ClearScreen();
	drawUI.DrawStatus(player->getName(), "", to_string(player->getHealth()), "");

	string StringSelection = "1. HP 20% 회복  ";
	string StringResult = "";
	int playerChoice = -1;
	int unlockSkillCount = 0;
	int randSkill_1, randSkill_2;
	int skillList[SKILL_COUNT] = { 0 };
	int unlockSkillList[SKILL_COUNT - SKILL_FOR] = { 0 };
	player->lockSkillList(skillList);

	for (int i = 1; i < SKILL_COUNT-SKILL_FOR+1; i++) {
		if (skillList[i] > 0) {
			
			unlockSkillList[unlockSkillCount++] = skillList[i];
			
			//cin >> StringResult;
		}
		
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, unlockSkillCount - 1);

	
		randSkill_1 = unlockSkillList[dis(gen)];
		randSkill_2 = unlockSkillList[dis(gen)];
	
		//cout << to_string(unlockSkillCount) << "                    " << to_string(randSkill_1) << "                    " << to_string(randSkill_2) << endl;
		//cin >> StringResult;
	
	if (unlockSkillCount == 1) {
		StringSelection += "2." + this->skillManager.skillNameList[randSkill_1] + "  ";
	}
	else if (unlockSkillCount >= 2) {
		StringSelection += "2." + this->skillManager.skillNameList[randSkill_1] + "  ";
		StringSelection += "3." + this->skillManager.skillNameList[randSkill_2] + "  ";

	}


	drawUI.DrawTextUI(StringSelection,"");
	drawUI.DrawInputUI("획득할 효과를 선택하세요 : ");
	playerChoice = PlayerInputNumber(unlockSkillCount+1);
	switch (playerChoice) {
	case 1:
		StringResult  = this->skillManager.Heal(player);
		break;
	case 2:
		player->addSkill(randSkill_1);
		StringResult = this->skillManager.skillNameList[randSkill_1] + " 스킬을 획득하였습니다.";
		break;
	case 3:
		player->addSkill(randSkill_2);
		StringResult = this->skillManager.skillNameList[randSkill_2] + " 스킬을 획득하였습니다.";
		break;
	default:
		break;
	}

	drawUI.DrawStatus(player->getName(), "", to_string(player->getHealth()), "");
	drawUI.DrawTextUI(StringResult,"");
	drawUI.DrawInputUI("");
	Sleep(2000);
}

void GameManager::LegacyCodeMap(State* player, State enemyList[ENEMY_COUNT]) {
	this->drawUI.ClearScreen();
	drawUI.DrawStatus(player->getName(), "", to_string(player->getHealth()), "");
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis1(50, 120);
	std::uniform_int_distribution<int> dis2(1, 100);
	int playerChoice, rand;

	drawUI.DrawTextUI("1.Direct_Memory_Access  2.Dangling_Pointer  3.Race_Condition", "");
	drawUI.DrawInputUI("획득할 효과를 선택하세요 : ");
	playerChoice = PlayerInputNumber(3);

	switch (playerChoice) {
		
	case 1:
		rand = dis1(gen);
		for (int i = 0; i < ENEMY_COUNT; i++) {
			enemyList[i].multiplyHealth((double)rand);
		}
		drawUI.DrawTextUI("몬스터들의 체력을 기존의 " + to_string(rand) + "%로 변경했습니다", "");
		drawUI.DrawInputUI("");
		Sleep(2000);
		break;
	case 2:
		rand = dis2(gen);
		player->multiplyAttackDamage(150);
		drawUI.DrawTextUI(player->getName()+"의 공격력이 기존의 " + to_string(150) + "%로 증가했습니다", "");
		drawUI.DrawInputUI("");
		Sleep(2000);
		if (rand <= 15) {
			player->takeDamage(player->getAttackMin());
			drawUI.DrawTextUI(to_string(15) + "의  확률로 자기 자신을 공격했습니다.", "");
			drawUI.DrawInputUI("");
		}
		drawUI.DrawStatus(player->getName(), "", to_string(player->getHealth()), "");
		Sleep(2000);
		break;
	case 3:
		player->setRaceCondition();
		drawUI.DrawTextUI("앞으로 플레이어가 공격 시 방어가 함께 적용됩니다.", "하지만 공격 시 "+to_string(25)+"% 확률로 아무것도 하지 않을 수도 있게 됩니다.");
		drawUI.DrawInputUI("");
		Sleep(2000);
		break;
	default:
		break;
	}

}

void GameManager::Map_Main_cpp_Error(State* player) {
	
	Boss boss(BOSS_STATE_FATAL_RUNTIME_ERROR);
	int i = 0;
	int bossUpdate = 1;

	drawUI.ClearScreen();
	drawUI.DrawAsciiEnemy(boss.getAscii());
	drawUI.DrawStatus(player->getName(), boss.getName(), to_string(player->getHealth()), to_string(boss.getHealth()));

	while (true) {
		i++;
		i %= 2;

		if (bossUpdate != i) {
			boss.StateUpdate(player);
		}

		
		if (player->getHealth() <= 0) {
			GameOver();
			break;
		}
		else if (boss.getHealth() <= 0) {
			drawUI.DrawTextUI("Boss Defeated!!", "Congratulations!");
			cin.ignore();
			cin.get();
			break;
		}
		
		Turn(&i, player, &boss);
	}
}

int GameManager::PlayerInputNumber(int range)
{
	
	string playerInput;
	while(true) {
		cin >> playerInput;
		cout << "\033[1F";
		if (playerInput.length() == 1 && playerInput[0] > '0' && playerInput[0] <= range+'0') {
			return playerInput[0] - '0';
		}
		else {
			drawUI.DrawInputUI(STRING_PLAYER_INPUT_ERROR);
		}

	}
	return -1;
}

void GameManager::Turn(int *isPlayer,State *player, State *enemy)
{
	int Action = -1;
	int enemyChance;
	string turnResult;


	if (*isPlayer == 1) {

		if (enemy->enemyActionOrStay == -1) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(1, 100);


			enemy->enemyActionOrStay = dis(gen);
		}

		enemyChance = enemy->enemyActionOrStay;
		
		drawUI.DrawTextUI(STRING_TURN(player->getName()), "");
		Sleep(1000);

		if (enemyChance >= ENEMY_ATTACK_CHANCE) {
			
			drawUI.DrawTextUI(enemy->getName() + "은(는) 대기하려고 한다.", STRING_SELECT_SKILL_LIST);
		}
		else { 
			drawUI.DrawTextUI(enemy->getName() + "은(는) "+to_string(enemy->getAttackMin())+"데미지로 공격하려고 한다.", STRING_SELECT_SKILL_LIST);
		}

		//drawUI.DrawTextUI(STRING_TURN(player->getName()),STRING_SELECT_SKILL_LIST);
		drawUI.DrawInputUI(STRING_SELECT_SKILL);
		Action = PlayerInputNumber(SKILL_SELECTION_RANGE);
		if (player->getControlByBoss() == Action) {
			drawUI.DrawTextUI("보스에 의해 금지당했습니다.", "");
			drawUI.DrawInputUI("계속하려면 Enter");
			cin.ignore();
			cin.get();
			cout << "\033[1F";
			(*isPlayer)++;
			return;
		}

		if (Action == UNIQUE_SKILL_LIST && player->hasSkill() == 1) {
			int skillList[SKILL_COUNT] = {0};
			string skillListString = "";
			int UniqueSkillRange = 0;
			player->SkillList(skillList);
			for (int i = 1; i < SKILL_COUNT; i++) {
				if (skillList[i] > 0) {
					skillListString += to_string(i) + "." + this->skillManager.skillNameList[skillList[i]]+"  ";
					UniqueSkillRange++;
				}
			}
			drawUI.DrawTextUI(skillListString, "");
			drawUI.DrawInputUI("");
			Action = skillList[PlayerInputNumber(UniqueSkillRange)];
		}
		else if (Action == UNIQUE_SKILL_LIST && player->hasSkill() == 0) {

			drawUI.DrawTextUI("사용 가능한 스킬이 없습니다.", "");
			drawUI.DrawInputUI("계속하려면 Enter");
			cin.ignore();
			cin.get();
			cout << "\033[1F";
			(*isPlayer)++;
			return;
		}
		turnResult = this->skillManager.ChoiceSkill(Action, player, enemy);
		drawUI.DrawTextUI(turnResult, "");
		drawUI.DrawStatus(player->getName(), enemy->getName(), to_string(player->getHealth()), to_string(enemy->getHealth()));
		drawUI.DrawInputUI("");
		Sleep(2000);
		if (*isPlayer == 1 && player->getRaceCondition() == 1) {

			turnResult = this->skillManager.ChoiceSkill(DEFEND, player, enemy);
			drawUI.DrawTextUI(turnResult, "");
			drawUI.DrawStatus(player->getName(), enemy->getName(), to_string(player->getHealth()), to_string(enemy->getHealth()));
			drawUI.DrawInputUI("");
			Sleep(2000);
		}

	}
	else {
		if (enemy->enemyActionOrStay == -1) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(1, 100);


			enemy->enemyActionOrStay = dis(gen);
		}

		enemyChance = enemy->enemyActionOrStay;

		if (enemyChance >= ENEMY_ATTACK_CHANCE) {
			Action = 0;
		}
		else {
			Action = 1;
		}
		drawUI.DrawTextUI(STRING_TURN(enemy->getName()),"");
		Sleep(1000);
		turnResult = skillManager.ChoiceSkill(Action, enemy, player);
		drawUI.DrawTextUI(turnResult, "");
		drawUI.DrawStatus(player->getName(), enemy->getName(), to_string(player->getHealth()), to_string(enemy->getHealth()));
		drawUI.DrawInputUI("");
		Sleep(2000);

		enemy->enemyActionOrStay = -1;
	}

	if (player->IsMultithreading() > 0) {
		(*isPlayer)++;
	}

}

void GameManager::GameOver()
{
	drawUI.ClearScreen();
	drawUI.DrawAsciiMap(ASCII_TEST);
	drawUI.DrawTextUI("Game Over", "Press any key to exit.");
	cin.ignore();
	cin.get();
	exit(0);

}