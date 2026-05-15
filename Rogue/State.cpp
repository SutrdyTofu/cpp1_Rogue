#include "State.h"

#include <random>

State::State(string name,string ascii, int health, int attackMax, int attackMin,int defenceMax,int defenceMin, int heal, int evasion)
{
	this->name = name;
	this->ascii = ascii;
	this->health = health;
	this->attackMax = attackMax;
	this->attackMin = attackMin;
	this->defenceMax = defenceMax;
	this->defenceMin = defenceMin;
	this->heal = heal;
	this->evasion = evasion;
	isDefence = 0;
	previousSkill = 0;
	isSkii_for = 0;
	isDeadlock = 0;
	isBooleanShield = 0;
	isMultiThreading = 0;
	isRaceCondition = 0;
	for(int i = 0; i < SKILL_COUNT; i++)
		isUsingSkill[i] = 0;
	isMemoryDotDamaged = 0;
	isCantUseSkill = 0;
	isControlByBoss = 0;
	
}
State::State()
{	
	name = "default";
	ascii = "default_ASCII";
	health = 100;
	attackMax = 10;
	attackMin = 5;
	defenceMax = 5;
	defenceMin = 2;
	heal = 5;
	evasion = 0;
	isDefence = 0;
	previousSkill = 0;
	isSkii_for = 0;
	isDeadlock = 0;
	isBooleanShield = 0;
	isMultiThreading = 0;
	isRaceCondition = 0;
	for (int i = 0; i < SKILL_COUNT; i++)
		isUsingSkill[i] = 0;
	isMemoryDotDamaged = 0;
	isCantUseSkill = 0;
	isControlByBoss = 0;

}

void State::takeDamage(int damage)
{
	if (damage < 0)
		damage = 0;
	this->health -= damage;
	if (this->health < 0) {
		this->health = 0;
	}
}

int State::getHealth()
{
	return this->health;
}

void State::multiplyHealth(double heal) {

	this->health = (int)((this->health) * (heal/100));
}

int State::getAttackMin() {

	return this->attackMin;
}

void State::multiplyAttackDamage(double addAttack) {

	this->attackMax = (int)((this->attackMax)*(addAttack/100));
	this->attackMin = (int)((this->attackMin) * (addAttack/100));
}

string State::getAscii()
{
	return this->ascii;
}

string State::getName() {

	return this->name;
}

void State::setRaceCondition() {
	this->isRaceCondition = 1;
}

int State::getRaceCondition() {
	return this->isRaceCondition;
}

void State::setControlByBoss(int value) {
	this->isControlByBoss = value;
}

int State::getControlByBoss() {
	return this->isControlByBoss;
}

int State::IsMultithreading() {
	if (this->isMultiThreading > 0) {
		return this->isMultiThreading--;
	}
	
	return 0;
}


int State::hasSkill() {

	for (int hasSkill : this->isUsingSkill) {
		if (hasSkill == 1)
			return hasSkill;
	}
	return 0;
}

void State::SkillList(int skillList[SKILL_COUNT]) {
	
	int k=1;
	
	for (int i = 0; i < SKILL_COUNT; i++) {
		if (this->isUsingSkill[i] == 1) {
			skillList[k] = i;
			k++;
		}
	}
}

void State::lockSkillList(int skillList[SKILL_COUNT]) {
	int k = 1;

	for (int i = SKILL_FOR; i < SKILL_COUNT; i++) {
		if (this->isUsingSkill[i] == 0) {
			skillList[k] = i;
			k++;
		}
	}
}

void State::initSkill() {

	this->previousSkill = 0;
	this->isBooleanShield = 0;
	this->isDeadlock = 0;
	this->isDefence = 0;
	this->isMultiThreading = 0;

	this->isCantUseSkill = 0;
	this->isMemoryDotDamaged = 0;

	for (int i = 0; i < SKILL_COUNT;i++) {
		if (this->isUsingSkill[i] == 2)
			this->isUsingSkill[i] = 1;
	}
}

void State::addSkill(int skillNumber) {
	this->isUsingSkill[skillNumber] = 1;
	
}