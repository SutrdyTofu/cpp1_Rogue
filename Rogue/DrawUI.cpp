#include "DrawUI.h"
#include "GameplayValue.h"

#include <iostream>

using namespace std;

DrawUI::DrawUI()
{
	isDrawMap = 0;
}

void DrawUI::ClearScreen()
{

	cout << "\033[2J\033[1;1f";

}

void DrawUI::DrawAsciiMap(string ascii)
{
	cout << "\033["<< STATUS_UI_ROW <<";1f";
	cout << ascii << endl;
	isDrawMap = 1;
}

void DrawUI::DrawAsciiEnemy(string ascii) {
	
	cout << "\033[" << STATUS_UI_ROW << ";1f";
	cout << ascii << endl;
	isDrawMap = 0;

}

void DrawUI::DrawTextUI(string line1,string line2)
{
	if (isDrawMap == 1) {
		cout << "\033["<< STATUS_UI_ROW + ASCII_MAP_ROW + 1 <<";1f";
	}
	else {
		cout << "\033[" << STATUS_UI_ROW + ASCII_ENEMY_ROW + 1 << ";1f";
	}
	cout << "\033[2K" << line1 << "\033[1E";
	cout << "\033[2K" << line2 << "\033[1E";
}

void DrawUI::DrawInputUI(string text)
{
	if (isDrawMap == 1) {
		cout << "\033[" << STATUS_UI_ROW + ASCII_MAP_ROW + 3 << ";1f";
	}
	else {
		cout << "\033[" << STATUS_UI_ROW + ASCII_ENEMY_ROW + 3 << ";1f";
	}
	cout << "\033[2K" << text;
}


void DrawUI::DrawStatus(string player_name, string enemy_name, string player_HP, string enemy_HP) {

	string player_hp = "HP : " + player_HP;
	string enemy_hp;
	if(enemy_HP != "")
		enemy_hp = "HP : " + enemy_HP;

	string nameBlank = "";
	string HpBlank = "";

	for (int i = 0; i < 20 - player_name.length();i++) {
		nameBlank += " ";
	}

	for (int i = 0; i < 20 - player_hp.length();i++) {
		HpBlank += " ";
	}

	cout <<"\033[1;1f\033[2K" << player_name << nameBlank << enemy_name;
	cout << "\033[1E\033[2K" << player_hp << HpBlank << enemy_hp;
	DrawInputUI("");

}