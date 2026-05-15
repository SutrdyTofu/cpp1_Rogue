#pragma once

#include "State.h"


class Boss : public State {

	public:
		Boss();
		Boss(string name, string ascii, int health, int attackMax, int attackMin, int defenceMax, int defenceMin, int heal, int evasion);
		virtual void takeDamage(int damage) override;
		//void Attack();
		void StateUpdate(State *player);
		void AttackIncreaseEvenTurn();
		void AttackControlPlayer(State *player);
		int SuicideBomb();
private:
	int accTurn,accAttackMax,accAttackMin,bombCount;

};