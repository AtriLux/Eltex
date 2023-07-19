#include "Characters.h"

void copyCharacter(character** copy, character** main) {

	(*copy)->ability->strength = (*main)->ability->strength;
	(*copy)->ability->dexterity = (*main)->ability->dexterity;
	(*copy)->ability->constitution = (*main)->ability->constitution;
	(*copy)->ability->intelligence = (*main)->ability->intelligence;

	(*copy)->equip->armour->magicDef = (*main)->equip->armour->magicDef;
	(*copy)->equip->armour->physDef = (*main)->equip->armour->physDef;
}

int actPower(character** active, character** passive, int atk, power pwr) {
	// check power->ability
	int abil;
	switch ((&pwr)->ability) {
	case 0:
		abil = 0;
		break;
	case 1:
		abil = (*active)->ability->strength;
		break;
	case 2:
		abil = (*active)->ability->dexterity;
		break;
	case 3:
		abil = (*active)->ability->constitution;
		break;
	case 4:
		abil = (*active)->ability->intelligence;
		break;
	case 5:
		abil = (*active)->ability->charisma;
		break;
	case 6:
		abil = (*active)->ability->strength;
		if ((*active)->ability->dexterity > abil) abil = (*active)->ability->dexterity;
		if ((*active)->ability->constitution > abil) abil = (*active)->ability->constitution;
		if ((*active)->ability->intelligence > abil) abil = (*active)->ability->intelligence;
		if ((*active)->ability->charisma > abil) abil = (*active)->ability->charisma;
		break;
	}
	//chance to miss
	int miss = 20 + (*passive)->ability->dexterity * 2 + pwr.points * 5 - (*active)->lvl * 10;
	if (rand() % 100 > miss) {
		//check power->type
		int points, def;
		switch ((&pwr)->type) {
		case 1:
			def = (*passive)->equip->armour->physDef + (*passive)->ability->constitution / 4;
			points = atk + (&pwr)->points * (abil / 5) - def;
			if (points < 0) points = 0;
			(*passive)->hp -= points;
			break;
		case 2:
			def = (*passive)->equip->armour->magicDef + (*passive)->ability->intelligence / 4;
			points = atk + (&pwr)->points * (abil / 5) - def;
			if (points < 0) points = 0;
			(*passive)->hp -= points;
			break;
		case 3:
			points = atk + (&pwr)->points * (abil / 3);
			(*active)->equip->armour->physDef += points;
			break;
		case 4:
			points = atk + (&pwr)->points * (abil / 3);
			(*active)->equip->armour->magicDef += points;
			break;
		case 5:
			points = atk + (&pwr)->points * (abil / 2);
			(*active)->hp += points;
			if ((*active)->hp > (*active)->maxHp)
				(*active)->hp = (*active)->maxHp;
			break;
		case 7:
			points = atk + (&pwr)->points * (abil / 2);
			(*active)->ability->strength += points;
			break;
		case 8:
			points = atk + (&pwr)->points * (abil / 2);
			(*active)->ability->dexterity += points;
			break;
		case 9:
			points = atk + (&pwr)->points * (abil / 2);
			(*active)->ability->constitution += points;
			break;
		case 10:
			points = atk + (&pwr)->points * (abil / 2);
			(*active)->ability->intelligence += points;
			break;
		case 11:
			points = atk + (&pwr)->points * (abil / 2);
			(*passive)->ability->strength -= points;
			if ((*passive)->ability->strength < 0)
				(*passive)->ability->strength = 0;
			break;
		case 12:
			points = atk + (&pwr)->points * (abil / 2);
			(*passive)->ability->dexterity -= points;
			if ((*passive)->ability->dexterity < 0)
				(*passive)->ability->dexterity = 0;
			break;
		case 13:
			points = atk + (&pwr)->points * (abil / 2);
			(*passive)->ability->constitution -= points;
			if ((*passive)->ability->constitution < 0)
				(*passive)->ability->constitution = 0;
			break;
		case 14:
			points = atk + (&pwr)->points * (abil / 2);
			(*passive)->ability->intelligence -= points;
			if ((*passive)->ability->intelligence < 0)
				(*passive)->ability->intelligence = 0;
			break;
		}
		return points;
	}
	else return 0;
}

int actPotion(character** active, character** passive, potion ptn) {
	//check potion->type
	switch ((&ptn)->type) {
	case 1:
		(*passive)->hp -= ptn.points;
		break;
	case 2:
		(*passive)->hp -= ptn.points;
		break;
	case 3:
		(*active)->equip->armour->physDef += ptn.points;
		break;
	case 4:
		(*active)->equip->armour->magicDef += ptn.points;
		break;
	case 5:
		(*active)->hp += ptn.points;
		if ((*active)->hp > (*active)->maxHp)
			(*active)->hp = (*active)->maxHp;
		break;
	case 7:
		(*active)->ability->strength += ptn.points;
		break;
	case 8:
		(*active)->ability->dexterity += ptn.points;
		break;
	case 9:
		(*active)->ability->constitution += ptn.points;
		break;
	case 10:
		(*active)->ability->intelligence += ptn.points;
		break;
	case 11:
		(*passive)->ability->strength -= ptn.points;
		break;
	case 12:
		(*passive)->ability->dexterity -= ptn.points;
		break;
	case 13:
		(*passive)->ability->constitution -= ptn.points;
		break;
	case 14:
		(*passive)->ability->intelligence -= ptn.points;
		break;
	}
	return ptn.points;
}

int checkMinAbility(ability* ab, weapon* wpn) {
	if ((ab->strength >= wpn->minStr) && (ab->dexterity >= wpn->minDex) && (ab->intelligence >= wpn->minInt))
		return 1;
	else
		return 0;
}

int addPotion(character** ch, int id) {
	potion* ptn = readPotion(id);

	int i;
	for (i = 0; i < INV_SIZE; i++) {
		inventory* inv = &(*ch)->equip->inventory[i];
		if ((*inv).type == 0) { // empty slot
			(*inv).ptn = ptn;
			(*inv).type = 3;
			break;
		}
	}
	printf("%s\n", ptn->name);
	return i;	
}

int addWeapon(character** ch, int id) {
	weapon* wpn = readWeapon(id);

	int i;
	for (i = 0; i < INV_SIZE; i++) {
		inventory* inv = &(*ch)->equip->inventory[i];
		if ((*inv).type == 0) { // empty slot
			(*inv).wpn = wpn;
			(*inv).type = 1;
			break;
		}
	}
	printf("%s\n", wpn->name);
	return i;
}

int addArmour(character** ch, int id) {
	armour* arm = readArmour(id);

	int i;
	for (i = 0; i < INV_SIZE; i++) {
		inventory* inv = &(*ch)->equip->inventory[i];
		if ((*inv).type == 0) { // empty slot
			(*inv).arm = arm;
			(*inv).type = 2;
			break;
		}
	}
	printf("%s\n", arm->name);
	return i;
}

void printCharacter(character* ch) {
	printf("%16s\n", ch->name);
	printf("%12d LVL\n", ch->lvl);
	printf("HP: %7d / %2d\n", ch->hp, ch->maxHp);
	printf("MP: %7d / %2d\n", ch->mp, ch->maxMp);
	if (ch->lvl != 20) printf("%7d / %2d EXP\n", ch->exp, ch->lvl * LVL_UP);
	printf("%16s\n\n", ch->type);
	printf("%14d M\n\n", ch->money);

	printAbility(ch->ability);

	puts("MAIN WEAPON:");
	printWeapon(ch->equip->weapon_1);

	puts("\nEXTRA WEAPON:");
	printWeapon(ch->equip->weapon_2);

	puts("\nARMOUR:");
	printArmour(ch->equip->armour);
}

void printAbility(ability* ab) {
	puts("CHARACTERISTICS:");
	printf("STR: %11d\n", ab->strength);
	printf("DEX: %11d\n", ab->dexterity);
	printf("CON: %11d\n", ab->constitution);
	printf("INT: %11d\n", ab->intelligence);
	printf("CHR: %11d\n\n", ab->charisma);
}

character* createCharacter(int race, int class, char* name, int lvl) {

	character* ch = (character*)malloc(sizeof(character));
	ch->mp = 2;
	ch->maxMp = ch->mp;
	ch->exp = 0;
	ch->lvl = lvl;
	ch->money = 10;
	strcpy(ch->name, name);
	ch->race = race;
	ch->class = class;
	readRace(&ch);
	readClass(&ch);
	for (int i = 0; i < INV_SIZE; i++) { // обнулить инвентарь
		ch->equip->inventory[i].type = 0;
	}
	return ch;
}

void readRace(character** ch) {

	ability* ab = (ability*)malloc(sizeof(ability));

	FILE* config;
	config = fopen("config/race.conf", "r");
	if (config == NULL) {
		puts("Ошибка при открытии файла конфигурации race.conf.");
		exit(1);
	}

	while (!feof(config)) {
		int id;
		char type[NAME_SIZE];
		fscanf(config, "%d", &id);
		if (id == (*ch)->race) {
			fscanf(config, "%d", &ab->strength);
			fscanf(config, "%d", &ab->dexterity);
			fscanf(config, "%d", &ab->constitution);
			fscanf(config, "%d", &ab->intelligence);
			fscanf(config, "%d", &ab->charisma);
			fscanf(config, "%s", &type);
			strcpy((*ch)->type, type);
			break;
		}
		else {
			char c = "";
			while (c != '\n' && c != EOF) {
				c = fgetc(config);
			}
		}
	}
	fclose(config);
	(*ch)->ability = ab;
}

void readClass(character** ch) {
	equipment* eq = (equipment*)malloc(sizeof(equipment));
	FILE* config;
	config = fopen("config/class.conf", "r");
	if (config == NULL) {
		puts("Ошибка при открытии файла конфигурации class.conf.");
		exit(1);
	}

	while (!feof(config)) {
		int id, wpn_1, wpn_2, ar;
		char type[NAME_SIZE];
		fscanf(config, "%d", &id);
		if (id == (*ch)->class) {
			fscanf(config, "%d", &(*ch)->hp);
			(*ch)->hp *= (*ch)->lvl; // скалирование здоровья в зависимости от уровня (для врагов)
			(*ch)->maxHp = (*ch)->hp;

			fscanf(config, "%d", &wpn_1);
			eq->weapon_1 = readWeapon(wpn_1);

			fscanf(config, "%d", &wpn_2);
			eq->weapon_2 = readWeapon(wpn_2);

			fscanf(config, "%d", &ar);
			eq->armour = readArmour(ar);
			// если противник, то скалируем броню от уровня
			if ((*ch)->race >= RACE_CNT) {
				eq->armour->magicDef += ((*ch)->lvl - 1) * LVL_BUST;
				eq->armour->physDef += ((*ch)->lvl - 1) * LVL_BUST;
			}

			fscanf(config, "%s", &type);
			strcat((*ch)->type, " ");
			strcat((*ch)->type, type);
			break;
		}
		else {
			char c = "";
			while (c != '\n' && c != EOF) {
				c = fgetc(config);
			}
		}
	}
	fclose(config);
	(*ch)->equip = eq;

	//powers for heroes
	if ((*ch)->class <= CLASS_CNT) {
		(*ch)->powers[0].id = (CLASS_CNT - 1) * ((*ch)->class - 1) + (*ch)->lvl / 5 + 1;
		readPower(&(*ch)->powers[0]);
	}
}

void clear(character** ch) {
	free((*ch)->ability);
	free((*ch)->equip->weapon_1);
	free((*ch)->equip->weapon_2);
	free((*ch)->equip->armour);
	for (int i = 0; i < INV_SIZE; i++) {
		switch ((*ch)->equip->inventory[i].type) {
		case 1:
			free((*ch)->equip->inventory[i].wpn);
			break;
		case 2:
			free((*ch)->equip->inventory[i].arm);
			break;
		case 3:
			free((*ch)->equip->inventory[i].ptn);
			break;
		}
	}
	free((*ch)->equip);
	free(*ch);
}

int addExp(character** ch, int points) {
	(*ch)->exp += points;
	if ((*ch)->exp > (*ch)->lvl * LVL_UP) {
		(*ch)->exp -= (*ch)->lvl * LVL_UP;
		(*ch)->lvl++;
		(*ch)->maxHp += (*ch)->ability->constitution / 3;
		(*ch)->hp = (*ch)->maxHp;
		if ((*ch)->lvl % 2 == 1) (*ch)->maxMp++;
		(*ch)->mp = (*ch)->maxMp;
		return 1;
	}
	return 0;
}