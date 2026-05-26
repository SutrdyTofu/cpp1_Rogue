#pragma once


//게임에서 사용되는 ASCII 아트
#define ASCII_TEST \
"ASCII_ART//\n\
ASCII_ART//"
#define STATUS_UI_ROW 4
#define ASCII_MAP_ROW 10
#define ASCII_ENEMY_ROW 5
#define ASCII_MAP \
"MAP//MAP//MAP//MAP//MAP//MAP//\n\
MAP//MAP//MAP//MAP//MAP//MAP//\n\
MAP//MAP//MAP//MAP//MAP//MAP//\n\
MAP//MAP//MAP//MAP//MAP//MAP//\n\
MAP//MAP//MAP//MAP//MAP//MAP//\n\
MAP//MAP//MAP//MAP//MAP//MAP//\n\
MAP//MAP//MAP//MAP//MAP//MAP//"
#define ASCII_ENEMY_SYNTAX \
"SYNTAX_ERROR_ASCII//\n\
SYNTAX_ERROR_ASCII//\n\
SYNTAX_ERROR_ASCII//\n"
#define ASCII_ENEMY_LINKER \
"LINKER_ERROR_ASCII//\n\
LINKER_ERROR_ASCII//\n\
LINKER_ERROR_ASCII//\n"	
#define ASCII_ENEMY_LOGIC \
"LOGIC_ERROR_ASCII//\n\
LOGIC_ERROR_ASCII//\n\
LOGIC_ERROR_ASCII//\n"
#define ASCII_ENEMY_MEMORY \
"MEMORY_LEAK_ASCII//\n\
MEMORY_LEAK_ASCII//\n\
MEMORY_LEAK_ASCII//\n"
#define ASCII_ENEMY_SEGMENTATION \
"SEGMENTATION_FAULT_ASCII//\n\
SEGMENTATION_FAULT_ASCII//\n\
SEGMENTATION_FAULT_ASCII//\n"

#define ASCII_BOSS_FATAL_RUNTIME_ERROR \
"ASCII_BOSS_FATAL_RUNTIME_ERROR//\n\
ASCII_BOSS_FATAL_RUNTIME_ERROR//\n\
ASCII_BOSS_FATAL_RUNTIME_ERROR//\n"

//플레이어,적의 기본 능력치, 밸런스
#define PLAYER_NAME "Debuger"
#define PLAYER_HP 100
#define PLAYER_ATK_MIN 20
#define PLAYER_ATK_MAX 25
#define PLAYER_DEF_MIN 10
#define PLAYER_DEF_MAX 12
#define PLAYER_HEAL 20
#define PLAYER_EVASION 0

#define SKILL_FOR_REPEAT 3
#define SKILL_BOOLEAN_SHIELD_REPEAT 3
#define SKILL_MULTITHREADING_REPEAT 3
#define SKILL_OVERLOCK_ATK_UP 1
#define SKILL_DEADLOCK_TURN 2

//hp, atkMax, atkMin, defMax, defMin, heal, evasion 순서
#define ENEMY_NAME_SYNTAX "Syntax_Error"
#define ENEMY_NAME_LINKER "Linker_Error"
#define ENEMY_NAME_LOGIC "Logic_Error"
#define ENEMY_NAME_MEMORY "Memory_Leak"
#define ENEMY_NAME_SEGMENTATION "Segmentation_Fault"
#define ENEMY_SYNTAX_STATE "Syntax_Error",ASCII_ENEMY_SYNTAX, 69, 17, 17, 0, 0, 0, 0
#define ENEMY_LINKER_STATE "Linker_Error",ASCII_ENEMY_LINKER, 100, 15, 15, 0, 0, 0, 25
#define ENEMY_LOGIC_STATE "Logic_Error",ASCII_ENEMY_LOGIC, 60, 10, 10, 0, 0, 5, 33
#define ENEMY_MEMORY_STATE "Memory_Leak",ASCII_ENEMY_MEMORY, 120, 18, 18, 0, 0, 0, 0
#define ENEMY_MEMORY_DOTDAMAGE 5
#define ENEMY_SEGMENTATION_STATE "Segmentation_Fault",ASCII_ENEMY_SEGMENTATION, 150, 18, 18, 0, 0, 0, 0

#define ENEMY_ATTACK_CHANCE 66	

#define ENEMY_NUMBER_SYNTAX 0
#define ENEMY_NUMBER_LINKER 1
#define ENEMY_NUMBER_LOGIC 2
#define ENEMY_NUMBER_MEMORY 3
#define ENEMY_NUMBER_SEGMENTATION 4
#define ENEMY_MAP_DIFFICULTY 2
#define ENEMY_COUNT 5
#define ENEMY_EASY_COUNT 3
//#define ENEMY_NAME_LIST {"Syntax_Error", "Linker_Error", "Logic_Error", "Memory_Leak", "Segmentation_Fault"}

#define BOSS_NAME_FATAL_RUNTIME_ERROR "Fatal_Runtime_Error"
#define BOSS_STATE_FATAL_RUNTIME_ERROR          BOSS_NAME_FATAL_RUNTIME_ERROR, ASCII_BOSS_FATAL_RUNTIME_ERROR, 180, 14, 14, 0, 0, 0, 0

//게임에서 사용되는 문자열
#define STRING_TEST "테스트"
#define STRING_TURN(Attacker) (Attacker + "의 차례")
#define STRING_SELECT_SKILL "스킬 번호를 입력하세요 : "
#define STRING_SELECT_SKILL_LIST "1.공격  2.방어  3.특수스킬"
#define STRING_CANT_ACT "행동할 수 없습니다."
#define STRING_STAY(attacker) (attacker + "은(는) 아무것도 하지 않았다!")
#define STRING_ATTACK(attacker,damage) (attacker + "에게 "+ to_string(damage)+ "데미지!!")
#define STRING_EVASION "회피!!"
#define STRING_DEFEND "방어!!"
#define STRING_HEAL " 회복!!"
#define STRING_SKILL_FOR(defender) (defender + "에게 스킬_for!!")
#define STRING_SKILL_OVERLOCK(attacker,value) (attacker + "의 공격력 "+to_string(value)+" 증가!!")
#define STRING_SKILL_DEADLOCK(defender) (defender + "에게 스킬_deadlock!!")
#define STRING_SKILL_BOOLEAN_SHIELD(attacker) (attacker + "에게 스킬_boolean_shield!!")
#define STRING_SKILL_MULTITHREADING(attacker) (attacker + "에게 스킬_multithreading!!")
#define STRING_ENEMY_LOGIC_HEAL(enemy,heal) (enemy + "이(가) 공격을 무시하고 " + to_string(heal) + " 회복!!")
#define STRING_ENEMY_LOGIC_IGNORE_DEFENCE(enemy,damage) (enemy + "이(가) 방어를 무시하고 " + to_string(damage) + " 데미지!!")
#define STRING_ENEMY_CANTSKILL(enemy) (enemy+"에 의해 사용 불가능...")
#define STRING_ENEMY_DOTDAMAGE(enemy) (enemy+"에 의해 "+to_string(ENEMY_MEMORY_DOTDAMAGE)+" 도트 데미지!!")

#define STRING_PLAYER_INPUT_ERROR "잘못된 입력입니다. 범위 내의 숫자를 입력해주세요 : "
#define STRING_SELECT_MAP "맵을 선택하세요 : "


//맵 정보
#define MAP_ROW 5
#define MAP_COL 3
#define MAP_NODE \
{{000,000,000},\
 {100,000,100},\
 {100,100,010},\
 {100,011,011},\
 {110,110,001} };
#define MAP_NULL -1
#define MAP_NAME_UNKNOWN 1
#define MAP_NAME_OPTIMIZATION 2
#define MAP_NAME_LEGACECODE 3
#define MAP_NAME_MAINERROR 4
#define MAP_NAME_COUNT 5
#define MAP_NAME_LIST {"","???", "Optimization", "Legace_Code", "Main.cpp Error"}
#define MAP_DETAIL \
{{MAP_NAME_MAINERROR,     MAP_NULL,              MAP_NULL},\
 {MAP_NAME_OPTIMIZATION,  MAP_NAME_LEGACECODE,   MAP_NULL},\
 {MAP_NAME_LEGACECODE,    MAP_NAME_UNKNOWN,      MAP_NAME_UNKNOWN},\
 {MAP_NAME_UNKNOWN,       MAP_NAME_OPTIMIZATION, MAP_NAME_UNKNOWN},\
 {MAP_NAME_UNKNOWN,       MAP_NAME_UNKNOWN,      MAP_NAME_OPTIMIZATION} };

//스킬
#define STRING_SKILL_LIST {"","공격","방어","특수스킬","회복","For","OverLock","DeadLock","Boolean_Shield","Multi_Threading"}
#define STAY 0
#define ATTACK 1
#define DEFEND 2
#define UNIQUE_SKILL_LIST 3
#define SKILL_SELECTION_RANGE 3
#define HEAL 4
#define SKILL_FOR 5
#define SKILL_OVERLOCK 6
#define SKILL_DEADLOCK 7
#define SKILL_BOOLEAN_SHIELD 8
#define SKILL_MULTITHREADING 9
#define SKILL_COUNT 10
