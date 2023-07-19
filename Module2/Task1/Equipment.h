#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define NAME_SIZE 16 // размеры массивов для имен и названий
#define INV_SIZE 10 // размер инвентаря
#define TRADE_CNT 5 // количество товаров у торговцев
#define WEAPON_CNT 7 // общее количество оружия
#define ARMOUR_CNT 4 // общее количество доспехов
#define POTION_CNT 39 // общее количество зелий

typedef struct power {
	int id;
	char name[NAME_SIZE];
	int points;
	int type; // 1-ps_atk, 2-mg_atk, 3-ps_def, 4-mg_def, 5-heal, 6-mp_heal, 7-add_str, 8-add_dex, 9-add_con, 10-add_int, 11-del_str, 12-del_dex, 13-del_con, 14-del_int
	int ability; // 0-none, 1-str, 2-dex, 3-con, 4-int, 5-chr, 6-max
} power;

typedef struct potion {
	int id;
	char name[NAME_SIZE];
	int points;
	int type; // 1-ps_atk, 2-mg_atk, 3-ps_def, 4-mg_def, 5-heal, 6-mp_heal, 7-add_str, 8-add_dex, 9-add_con, 10-add_int, 11-del_str, 12-del_dex, 13-del_con, 14-del_int
	int cost;
} potion;

typedef struct weapon {
	int id;
	char name[NAME_SIZE];
	int attack;
	int minStr, minDex, minInt;
	power powers[2];
	int isTwoHanded; // bool
	int cost;
} weapon;

typedef struct armour {
	int id;
	char name[NAME_SIZE];
	int physDef, magicDef;
	int minStr, minDex, minInt;
	int cost;
} armour;

typedef struct inventory {
	int type; // 0 - none, 1 - wpn, 2 - arm, 3 - ptn
	weapon* wpn;
	armour* arm;
	potion* ptn;
} inventory;

typedef struct equipment {
	weapon* weapon_1, * weapon_2;
	armour* armour;
	inventory inventory[INV_SIZE];
} equipment;

void printWeapon(weapon* wpn);
void printArmour(armour* arm);
void printPower(power* pwr);
void printPotion(potion* ptn);

weapon* readWeapon(int wpn_id);
armour* readArmour(int arm_id);
potion* readPotion(int ptn_id);
void readPower(power* pwr);

void delInventoryItem(inventory inv[], int id, int size);