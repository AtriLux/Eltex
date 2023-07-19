#pragma once

#include <Windows.h> // Sleep, system("clear")
#include <conio.h> // _getch()

#include "Characters.h"

int day;

void startGame(character** hero);

//fight
int mainFight(character** hero, character** enemy);
void enemyFight(character** hero, character** enemy);
int heroFight(character** hero, character** enemy);
void weaponFight(character** hero, character** enemy);
void powerFight(character** hero, character** enemy);
void potionFight(character** hero, character** enemy);
void printFightInterface(character* hero, character* enemy);
void lvlUp(character** hero);
void giveReward(character** hero, int lvl);

//inventory
void mainInventory(character** hero);
int printInventoryInterface(character* hero); // return inventory size
int fullInventory(character** hero);

//traider
void createTrader(character** hero, int type);
void printTraderGoods(inventory goods[], int* tradeCnt, character* hero);
void trade(character** hero, inventory goods[], int* tradeCnt);

void city(character** hero);
void chest(character** hero);
void enterCave(character** hero);

void save(character** hero);
int load(character** hero, char chName[]);

void nextDay(character** hero);
void printDayInterface();
void win();
void lose();