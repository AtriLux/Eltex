#pragma once

#include "Equipment.h"

#define RACE_CNT 3 // ���������� ����������� ���
#define CLASS_CNT 6 // ���������� ����������� �������
#define LVL_BUST 3 // �������� ����� � ������ ���������� � ����������� �� ��� ������
#define LVL_UP 5 // ���������� ������������ ����� ��������� ��� ��������� ������ � ������ ����� �������
#define LVL_POINTS 4 // ���������� ����� ������������� ��� ������������� ����� ������� ��������� �������
#define ENEMY_EXP 4 // ���������� ����� �� ������ � ����� (��� ����� ������������ �� ������)
#define ENEMY_RACE_CNT 1 // ���������� ��� �����������
#define ENEMY_CLASS_CNT 1 // ���������� ������� �����������

typedef struct ability {
	int strength;
	int dexterity;
	int constitution;
	int intelligence;
	int charisma;
} ability;

typedef struct character {
	char name[NAME_SIZE];
	char type[NAME_SIZE*2]; // "race class"
	int hp, mp;
	int maxHp, maxMp;
	int class, race;
	equipment* equip;
	ability* ability;
	power powers[5];
	int lvl, exp;
	int money;
} character;

void printCharacter(character* ch);
void printAbility(ability* ab);

void readRace(character** ch);
void readClass(character** ch);

character* createCharacter(int race, int class, char* name, int lvl);
void clear(character** ch);

//fight
void copyCharacter(character** copy, character** main);
int actPower(character** active, character** passive, int atk, power pwr);
int actPotion(character** active, character** passive, potion ptr);

//inventory
int addPotion(character** ch, int id);
int addWeapon(character** ch, int id);
int addArmour(character** ch, int id);
int checkMinAbility(ability* ab, weapon* wpn);

int addExp(character** ch, int points);