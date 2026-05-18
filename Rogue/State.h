#pragma once

#include "GameplayValue.h"

#include <string>
using namespace std;


class State
{
	friend class SkillManager;

public:
	State();
	State(string name,string ascii, int health, int attackMax, int attackMin, int defenceMax, int defenceMin, int heal, int evasion);
	virtual void takeDamage(int damage);
	string getAscii();
	string getName();
	int getHealth();
	void multiplyHealth(double heal);
	int getAttackMin();
	void multiplyAttackDamage(double addAttack);
	void setRaceCondition();
	void setControlByBoss(int value);
	int getControlByBoss();
	int getRaceCondition();
	int IsMultithreading();
	int hasSkill();
	void SkillList(int skillList[SKILL_COUNT]);
	void lockSkillList(int skillList[SKILL_COUNT]);
	void initSkill();
	void addSkill(int skillNumber);
	int enemyActionOrStay;

protected:
	string name,ascii;
	int health,attackMin,attackMax,defenceMin,defenceMax,heal,evasion,previousSkill,isDefence,isSkii_for,isDeadlock,isBooleanShield,isMultiThreading,isRaceCondition,isControlByBoss;
	int isMemoryDotDamaged, isCantUseSkill;
	
	//¹ÌÈ¹µæ 0, »ç¿ë°¡´É 1, »ç¿ëÇÔ 2
	int isUsingSkill[SKILL_COUNT];
};
	