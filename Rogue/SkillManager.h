#pragma once
#include <string>
using namespace std;	
class SkillManager
{
	friend class State;

	public:
	string skillNameList[SKILL_COUNT] = STRING_SKILL_LIST;

	string ChoiceSkill(int SkillNumber, State* Attacker, State* Defender);
	string Attack(State* Attacker, State* Defender);
	string Defend(State* Attacker);
	string Heal(State* Attacker);
	string Skill_for(State* Attacker, State* Defender);
	string Skill_overlock(State* Attacker);
	string Skill_deadlock(State* Attacker, State* Defender);
	string Skill_boolean_shield(State* Attacker);
	string Skill_multithreading(State* Attacker);
	int Evasion(State* Attacker, State* Defender);

};