#include "GameplayValue.h"
#include "SkillManager.h"
#include "State.h"

#include<random>

string SkillManager::ChoiceSkill(int SkillNumber, State* Attacker, State* Defender){

	if (Attacker->isDeadlock > 0) {
		Attacker->isDeadlock--;
		return STRING_CANT_ACT;
	}

	if (Attacker->isSkii_for > 0) {
		Attacker->isSkii_for--;
		SkillNumber = Attacker->previousSkill;

	}

	if (Attacker->name == ENEMY_NAME_MEMORY) {
		Defender->isMemoryDotDamaged = 1;
	}
	if (Attacker->name == ENEMY_NAME_SEGMENTATION) {
		Defender->isCantUseSkill = 1;
	}

	if (Attacker->isCantUseSkill == 1) {
		return STRING_ENEMY_CANTSKILL(Defender->getName());
	}



	switch (SkillNumber)
	{
	case STAY:
		if (Defender->isMemoryDotDamaged) {
			Attacker->health -= 5;
			return STRING_STAY(Attacker->name) + "\n\n" + STRING_ENEMY_DOTDAMAGE(Attacker->getName());
		}
		return STRING_STAY(Attacker->name);
	case ATTACK:
		return SkillManager::Attack(Attacker, Defender);
		break;
	case DEFEND:
		return SkillManager::Defend(Attacker);
		break;
	case HEAL:
		return SkillManager::Heal(Attacker);
		break;
	case SKILL_FOR:
		Attacker->isUsingSkill[SKILL_FOR] = 2;
		return SkillManager::Skill_for(Attacker, Defender);
		break;
	case SKILL_OVERLOCK:
		Attacker->isUsingSkill[SKILL_OVERLOCK] = 2;
		return SkillManager::Skill_overlock(Attacker);
		break;
	case SKILL_DEADLOCK:
		Attacker->isUsingSkill[SKILL_DEADLOCK] = 2;
		return SkillManager::Skill_deadlock(Attacker, Defender);
		break;
	case SKILL_BOOLEAN_SHIELD:
		Attacker->isUsingSkill[SKILL_BOOLEAN_SHIELD] = 2;
		return SkillManager::Skill_boolean_shield(Attacker);
		break;
	case SKILL_MULTITHREADING:
		Attacker->isUsingSkill[SKILL_MULTITHREADING] = 2;
		return SkillManager::Skill_multithreading(Attacker);
		break;
	default:
		break;
	}

	return STRING_TEST;
}

string SkillManager::Attack(State* Attacker, State* Defender)
{
	int attack, defence, damage;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> atk(Attacker->attackMin, Attacker->attackMax);
	std::uniform_int_distribution<> def(Defender->defenceMin, Defender->defenceMax);
	attack = atk(gen);
	defence = def(gen);

	if (Attacker->getRaceCondition() == 1) {
		std::uniform_int_distribution<> dis(1,100);
		int rand = dis(gen);

		if (rand <= 25) {
			return STRING_STAY(Attacker->name);
		}

	}

	if (SkillManager::Evasion(Attacker, Defender) == 0) {
		
		if (Defender->name == ENEMY_NAME_LOGIC) {
			Heal(Defender);
			return STRING_ENEMY_LOGIC_HEAL(Defender->name, Defender->heal);
		}

		return STRING_EVASION;
	}

	if (Defender->name == ENEMY_NAME_LOGIC) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 100);
		
		if (dis(gen) <= Attacker->evasion) {
			damage = attack;
			Defender->takeDamage(damage);
			Defender->isDefence = 0;
			Attacker->previousSkill = ATTACK;
			
			return STRING_ENEMY_LOGIC_IGNORE_DEFENCE(Attacker->name, damage);
		}
	}

	damage = attack -(Defender->isDefence * defence);
	damage < 0 ? damage =0: damage ;
	Defender->takeDamage(damage);
	Defender->isDefence = 0;
	Attacker->previousSkill = ATTACK;
	
	if (Defender->isMemoryDotDamaged) {
		Attacker->health -= 5;
		return STRING_ATTACK(Defender->name, damage) + "\n\n" + STRING_ENEMY_DOTDAMAGE(Attacker->getName());
	}
	return STRING_ATTACK(Defender->name,damage);
}

string SkillManager::Defend(State* Attacker)
{
	Attacker->isDefence = 1;
	Attacker->previousSkill = DEFEND;

	return STRING_DEFEND;
}

string SkillManager::Heal(State* Attacker)
{
	Attacker->health += Attacker->heal;
	//Attacker->previousSkill = HEAL;

	return STRING_HEAL;
}

string SkillManager::Skill_for(State* Attacker, State* Defender)
{
	Defender->isSkii_for = SKILL_FOR_REPEAT;
	Attacker->previousSkill = SKILL_FOR;

	return STRING_SKILL_FOR(Defender->name);
}

string SkillManager::Skill_overlock(State* Attacker)
{
	Attacker->attackMin += SKILL_OVERLOCK_ATK_UP;
	Attacker->attackMax += SKILL_OVERLOCK_ATK_UP;
	Attacker->previousSkill = SKILL_OVERLOCK;

	return STRING_SKILL_OVERLOCK(Attacker->name, SKILL_OVERLOCK_ATK_UP);
}

string SkillManager::Skill_deadlock(State* Attacker, State* Defender)
{
	Defender->isDeadlock = SKILL_DEADLOCK_TURN;
	Attacker->previousSkill = SKILL_DEADLOCK;

	return STRING_SKILL_DEADLOCK(Defender->name);
}

string SkillManager::Skill_boolean_shield(State* Attacker)
{
	Attacker->isBooleanShield = SKILL_BOOLEAN_SHIELD_REPEAT;
	Attacker->previousSkill = SKILL_BOOLEAN_SHIELD;

	return STRING_SKILL_BOOLEAN_SHIELD(Attacker->name);
}

string SkillManager::Skill_multithreading(State* Attacker)
{
	Attacker->isMultiThreading = SKILL_MULTITHREADING_REPEAT;
	Attacker->previousSkill = SKILL_MULTITHREADING;

	return STRING_SKILL_MULTITHREADING(Attacker->name);
}


int SkillManager::Evasion(State* Attacker, State* Defender)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int evasion = Defender->evasion;

	if (Defender->isBooleanShield > 0) {
		Defender->isBooleanShield--;
		evasion += 50;
	}

	if (evasion <= dis(gen))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}