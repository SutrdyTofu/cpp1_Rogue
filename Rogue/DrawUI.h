#pragma once
#include <string>
using namespace std;

class DrawUI {

public:
	DrawUI();
	void ClearScreen();
	void DrawAsciiMap(string ascii);
	void DrawAsciiEnemy(string ascii);
	void DrawTextUI(string line1,string line2);
	void DrawInputUI(string text);
	void DrawStatus(string player_name,string enemy_name,string player_HP,string enemy_HP);
private:
	int isDrawMap;
};