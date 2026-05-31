#include "Boss.h"
#include "GameplayValue.h"
#include "DrawUI.h"

#include<random>
#include<Windows.h>

Boss::Boss() : State() {
	this->accTurn = 0;
	this->accAttackMax = 10;
	this->accAttackMin = 10;
	this->bombCount = 3;
	
}

Boss::Boss(string name, string ascii, int health, int attackMax, int attackMin, int defenceMax, int defenceMin, int heal, int evasion) : State(name, ascii,  health,  attackMax,  attackMin,  defenceMax,  defenceMin,  heal,  evasion) {
	this->accTurn = 0;
	this->accAttackMax = (int)(attackMax * ((double)50 / 100));
	this->accAttackMin = (int)(attackMin * ((double)50 / 100));
	this->bombCount = 3;
	this->attackMax = attackMax + accAttackMax;
	this->attackMin = attackMin + accAttackMin;
}

void Boss::takeDamage(int damage)
{
	if (damage < 0)
		damage = 0;
	this->health -= damage;
	if (this->health < 0) {
		this->health = 0;
	}
}

void Boss::AttackControlPlayer(State* player) {

	
	player->setControlByBoss(accTurn+1);

}

void Boss::AttackIncreaseEvenTurn() {
	if (accTurn == 0) {
		this->attackMax += accAttackMax;
		this->attackMin += accAttackMin;
	}
	else if(accTurn == 1)
	{
		this->attackMax -= accAttackMax;
		this->attackMin -= accAttackMin;
	}
}

int Boss::SuicideBomb() {
	this->bombCount--;
	if (bombCount == 0) {
		return 1;
	}
	return 0;
}
void Boss::StateUpdate(State* player) {
	accTurn++;
	accTurn %= 2;

	if (this->health <= 0) {
		return;
	}

	if (this->health >= 50) {
		
		AttackIncreaseEvenTurn();

	}
	//else if (this->health < 200 && this->health>50) {
	//	AttackControlPlayer(player);
	//}
	else {
		player->setControlByBoss(0);
		if (SuicideBomb() == 1) {
			DrawUI drawUI;
			player->takeDamage(999999);
			drawUI.DrawTextUI("ÀÚÆø!!!", "");
			drawUI.DrawInputUI("");
			Sleep(2000);
		}
	}
}
