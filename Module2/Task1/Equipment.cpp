#include "Equipment.h"

void delInventoryItem(inventory inv[], int id, int size) {
	switch (inv[id].type) {
	case 1:
		free(inv[id].wpn);
		break;
	case 2:
		free(inv[id].arm);
		break;
	case 3:
		free(inv[id].ptn);
		break;
	}
	for (int i = id; i < size - 1; i++) {
		inv[i] = inv[i + 1];
	}
	inv[size - 1].type = 0;
}

void printPotion(potion* ptn) {
	printf("NAME: %11s\n", ptn->name);
	printf("COST: %11d\n", ptn->cost);
	switch (ptn->type) {
	case 1:
		printf("Наносит физический урон противнику, равный %d.", ptn->points);
		break;
	case 2:
		printf("Наносит магический урон противнику, равный %d.", ptn->points);		
		break;
	case 3:
		printf("Увеличивает физическую защиту персонажа на %d.", ptn->points);		
		break;
	case 4:
		printf("Увеличивает магическую защиту персонажа на %d.", ptn->points);		
		break;
	case 5:
		printf("Увеличивает здоровье персонажа на %d.", ptn->points);		
		break;
	case 6:
		printf("Увеличивает ману персонажа на %d.", ptn->points);
		break;
	case 7:
		printf("Увеличивает силу (STR) персонажа на %d.", ptn->points);		
		break;
	case 8:
		printf("Увеличивает ловкость (DEX) персонажа на %d.", ptn->points);		
		break;
	case 9:
		printf("Увеличивает телосложение (CON) персонажа на %d.", ptn->points);		
		break;
	case 10:
		printf("Увеличивает интеллект (INT) персонажа на %d.", ptn->points);		
		break;
	case 11:
		printf("Уменьшает силу (STR) противника на %d.", ptn->points);		
		break;
	case 12:
		printf("Уменьшает ловкость (DEX) противника на %d.", ptn->points);		
		break;
	case 13:
		printf("Уменьшает телосложение (CON) противника на %d.", ptn->points);		
		break;
	case 14:
		printf("Уменьшает интеллект (INT) противника на %d.", ptn->points);		
		break;
	}
}

void printArmour(armour* ar) {
	printf("NAME: %11s\n", ar->name);
	printf("PHYS DEF: %7d\n", ar->physDef);
	printf("MAGIC DEF: %6d\n", ar->magicDef);
	printf("MIN STR: %8d\n", ar->minStr);
	printf("MIN DEX: %8d\n", ar->minDex);
	printf("MIN INT: %8d\n", ar->minInt);
	printf("COST: %11d\n", ar->cost);
}

void printWeapon(weapon* wpn) {
	if (wpn) {
		printf("NAME: %11s\n", wpn->name);
		if (wpn->isTwoHanded) puts("TWO-HANDED");
		else puts("ONE-HANDED");
		printf("ATK: %12d\n", wpn->attack);
		printf("MIN STR: %8d\n", wpn->minStr);
		printf("MIN DEX: %8d\n", wpn->minDex);
		printf("MIN INT: %8d\n", wpn->minInt);
		printf("POWER 1: %8s\n", wpn->powers[0].name);
		printf("POWER 2: %8s\n", wpn->powers[1].name);
		printf("COST: %11d\n", wpn->cost);
	}
	else {
		puts("none");
	}
}

weapon* readWeapon(int wpn_id) {
	if (!wpn_id) {
		return NULL;
	}
	else {
		weapon* wpn = (weapon*)malloc(sizeof(weapon));

		FILE* config;
		config = fopen("config/weapon.conf", "r");
		if (config == NULL) {
			puts("Ошибка при открытии файла конфигурации weapon.conf.");
			exit(1);
		}

		while (!feof(config)) {
			int id;
			char name[16];
			fscanf(config, "%d", &id);
			if (id == wpn_id) {
				wpn->id = id;
				fscanf(config, "%d", &wpn->minStr);
				fscanf(config, "%d", &wpn->minDex);
				fscanf(config, "%d", &wpn->minInt);
				fscanf(config, "%d", &wpn->isTwoHanded);
				fscanf(config, "%d", &wpn->attack);
				fscanf(config, "%d", &wpn->powers[0].id);
				readPower(&wpn->powers[0]);
				fscanf(config, "%d", &wpn->powers[1].id);
				readPower(&wpn->powers[1]);
				fscanf(config, "%d", &wpn->cost);
				fscanf(config, "%s", &name);
				strcpy(wpn->name, name);
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
		return wpn;
	}
}

armour* readArmour(int ar_id) {
	armour* ar = (armour*)malloc(sizeof(armour));

	FILE* config;
	config = fopen("config/armour.conf", "r");
	if (config == NULL) {
		puts("Ошибка при открытии файла конфигурации armour.conf.");
		exit(1);
	}

	while (!feof(config)) {
		int id;
		char name[16];
		fscanf(config, "%d", &id);
		if (id == ar_id) {
			ar->id = id;
			fscanf(config, "%d", &ar->minStr);
			fscanf(config, "%d", &ar->minDex);
			fscanf(config, "%d", &ar->minInt);
			fscanf(config, "%d", &ar->physDef);
			fscanf(config, "%d", &ar->magicDef);
			fscanf(config, "%d", &ar->cost);
			fscanf(config, "%s", &name);
			strcpy(ar->name, name);
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
	return ar;
}

void readPower(power* pwr) {

	FILE* config;
	config = fopen("config/power.conf", "r");
	if (config == NULL) {
		puts("Ошибка при открытии файла конфигурации power.conf.");
		exit(1);
	}

	while (!feof(config)) {
		int id;
		char name[16];
		fscanf(config, "%d", &id);
		if (id == pwr->id) {
			fscanf(config, "%d", &pwr->points);
			fscanf(config, "%d", &pwr->type);
			fscanf(config, "%d", &pwr->ability);
			fscanf(config, "%s", &name);
			strcpy(pwr->name, name);
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
}

potion* readPotion(int ptn_id) {

	potion* ptn = (potion*)malloc(sizeof(potion));

	FILE* config;
	config = fopen("config/potion.conf", "r");
	if (config == NULL) {
		puts("Ошибка при открытии файла конфигурации potion.conf.");
		exit(1);
	}

	while (!feof(config)) {
		int id;
		char name[16];
		fscanf(config, "%d", &id);
		if (id == ptn_id) {
			ptn->id = id;
			fscanf(config, "%d", &ptn->points);
			fscanf(config, "%d", &ptn->type);
			fscanf(config, "%d", &ptn->cost);
			fscanf(config, "%s", &name);
			strcpy(ptn->name, name);
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
	return ptn;
}