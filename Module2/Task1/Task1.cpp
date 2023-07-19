// Текстовая RPG на основе DnD

#include <locale.h>
#include <time.h>

#include "Interface.h"

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	//character* hero = createCharacter(1, 1, "HEROIN", 1);
	character * hero;
	startGame(&hero);
	//nextDay(&hero);
	//character* enemy = createCharacter(21, 21, "SKELETON", 1);
	//addPotion(&hero, 5);
	//addWeapon(&hero, 1);
	//addWeapon(&hero, 2);
	//addArmour(&hero, 3);
	//addWeapon(&hero, 3);
	//addPotion(&hero, 1);
	//addArmour(&hero, 3);
	//city(&hero);
	//chest(&hero);
	//mainInventory(&hero);
	//mainFight(&hero, &enemy);
	//mainInventory(&hero);
	//printCharacter(hero);
	//createTrader(&hero, 1);
	//mainInventory(&hero);
	//cave(&hero);
	clear(&hero);
	//clear(&enemy);
}

