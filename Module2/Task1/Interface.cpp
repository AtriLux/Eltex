#include "Interface.h"

void nextDay(character **hero) {
	
	puts("\nНажимте Enter для продолжения путешествия.");
	_getch();
	system("clear");
	//day = 99;
	day++;
	if (day % 100 == 0) {
		createTrader(hero, 1);
		createTrader(hero, 2);
		createTrader(hero, 3);
		character* enemy = createCharacter(100, 100, "DEATH", 20);
		int runaway = mainFight(hero, &enemy);
		if (!runaway) win();
		else lose();
		clear(&enemy);
	}
	else if (day % 10 == 0) {
		city(hero);
	}
	else {
		int enemy = 40, cave = enemy + 30, trader = cave + 15, nothing = trader + 10;
		int rnd = rand() % 100;
		if (rnd < enemy) {
			
			int race = rand() % ENEMY_RACE_CNT + 21;
			int class = rand() % ENEMY_CLASS_CNT + 21;
			character* enemy = createCharacter(race, class, "FOREST BEAST", (*hero)->lvl);
			
			int choice = 0;
			while (choice == 0) {
				printDayInterface();
				printf("Вы видите %s. Вступить в бой?\n\n", enemy->type);
				puts("1. Да.");
				puts("2. Нет.");
				puts("3. Открыть инвентарь.\n");
				while (choice < 1 || choice > 3) {
					printf("> ");
					scanf_s("%d", &choice);
					getchar();
				}
				if (choice == 1) {
					mainFight(hero, &enemy);
					clear(&enemy);
					nextDay(hero);
				}
				else if (choice == 3) {
					mainInventory(hero);
					choice = 0;
				}
				else {
					clear(&enemy);
					nextDay(hero);
				}
			}
		}
		else if (rnd < cave) {
			int choice = 0;
			while (choice == 0) {
				printDayInterface();
				puts("Вы видите пещеру. Хотите в нее войти?\n");
				puts("1. Да.");
				puts("2. Нет.");
				puts("3. Открыть инвентарь.\n");
				while (choice < 1 || choice > 3) {
					printf("> ");
					scanf_s("%d", &choice);
					getchar();
				}
				if (choice == 1) {
					enterCave(hero);
					nextDay(hero);
				}
				else if (choice == 3) {
					mainInventory(hero);
					choice = 0;
				}
				else nextDay(hero);
			}
		}
		else if (rnd < trader) {
			createTrader(hero, rand() % 3 + 1);
			nextDay(hero);
		}
		else if (rnd < nothing) {
			printDayInterface();
			puts("Сегодня ничего примечательного не произошло...");
			Sleep(2000);
			int choice = 0;
			while (choice == 0) {
				puts("\nВыберите действие:");
				puts("1. Открыть инвентарь.");
				puts("2. Ничего не делать.\n");
				while (choice < 1 || choice > 2) {
					printf("> ");
					scanf_s("%d", &choice);
					getchar();
				}
				if (choice == 1) {
					mainInventory(hero);
					choice = 0;
				}
			}
			nextDay(hero);
		}
		else {
			printDayInterface();
			chest(hero);
		}
	}
}

void printDayInterface() {
	system("clear");
	printf("%d ДЕНЬ\n\n", day);
}

void win() {
	system("clear");
	puts("Великое зло повержено. Вы исполнили предназначение. Теперь пора другим героям запечатлеть себя в фолиантах истории, а вам, о Великий, прожить остаток жизни в попытках превзойти собственый подвиг.");
	exit(0);
}

void lose() {
	system("clear");
	puts("Вы трусливо сбежали с поля боя. Зло торжествует. Мир медленно, но верно начнет умирать, пока другой герой, более смелый и умелый, чем вы, не сможет одолеть бестию. Вам же остается позорно доживать жизнь на задворках таверн, ожидая скорой гибели от пьянства. Но вы, хотя бы, смогли прожить до конца...");
	exit(0);
}

int load(character** hero, char chName[]) {
	FILE* save;
	save = fopen("save.txt", "r");
	if (save == NULL) {
		puts("Ошибка при открытии файла сохранения save.txt.");
		exit(1);
	}

	while (!feof(save)) {
		char name[NAME_SIZE];
		fscanf(save, "%s", &name);
		if (*chName == *name) {
			(*hero) = (character*)malloc(sizeof(character));
			(*hero)->ability = (ability*)malloc(sizeof(ability));
			(*hero)->equip = (equipment*)malloc(sizeof(equipment));

			strcpy((*hero)->name, name);

			char tmp[NAME_SIZE];
			fscanf(save, "%s", &(*hero)->type);
			fscanf(save, "%s", &tmp);
			strcat((*hero)->type, " ");
			strcat((*hero)->type, tmp);

			fscanf(save, "%d", &(*hero)->class);
			fscanf(save, "%d", &(*hero)->race);
			fscanf(save, "%d", &(*hero)->lvl);
			fscanf(save, "%d", &(*hero)->exp);
			
			for (int i = 0; i < (*hero)->lvl / 5 + 1; i++) {
				(*hero)->powers[i].id = (CLASS_CNT - 1) * ((*hero)->class - 1) + (*hero)->lvl / 5 + 1;
				readPower(&(*hero)->powers[i]);
			}

			fscanf(save, "%d", &(*hero)->maxHp);
			fscanf(save, "%d", &(*hero)->maxMp);
			(*hero)->hp = (*hero)->maxHp;
			(*hero)->mp = (*hero)->maxMp;

			fscanf(save, "%d", &(*hero)->money);

			fscanf(save, "%d", &(*hero)->ability->strength);
			fscanf(save, "%d", &(*hero)->ability->dexterity);
			fscanf(save, "%d", &(*hero)->ability->constitution);
			fscanf(save, "%d", &(*hero)->ability->intelligence);
			fscanf(save, "%d", &(*hero)->ability->charisma);

			int wpn1, wpn2, arm;
			fscanf(save, "%d", &wpn1);
			(*hero)->equip->weapon_1 = readWeapon(wpn1);
			fscanf(save, "%d", &wpn2);
			(*hero)->equip->weapon_2 = readWeapon(wpn2);
			fscanf(save, "%d", &arm);
			(*hero)->equip->armour = readArmour(arm);

			for (int i = 0; i < INV_SIZE; i++) {
				(*hero)->equip->inventory[i].type = 0;
				int type, id;
				fscanf(save, "%d", &type);
				if (type) fscanf(save, "%d", &id);
				switch (type) {
				case 1:
					addWeapon(hero, id);
					break;
				case 2:
					addArmour(hero, id);
					break;
				case 3:
					addPotion(hero, id);
					break;
				}
			}
			fscanf(save, "%d", &day);
			return 1;
		}
		break;
	}
	fclose(save);
	return 0;
}

void startGame(character** hero) {

	puts("Добро пожаловать, путник! Давненько я не принимал гостей. Как видишь, я слеп и почти полностью оглох... Опиши себя, порадуй старика.");
	puts("Как тебя зовут? Надеюсь, не очень замудренно. Я могу запомнить только имена до 9 букв.\n");

	//NAME
	char chName[10];
	printf("> ");
	scanf("%9s", chName);


	if (load(hero, chName)) {
		system("clear");
		puts("Точно, припоминаю тебя. Тогда продолжай свой рассказ, мне интересно, чем все кончилось.");
		nextDay(hero);
	}
	else {
		day = 0;
		//RACE
		puts("\nВпервые слышу такое имя. Видать, мы с тобой и правда незнакомы. Но учти, если мы уже встречались и ты назвал другое имя, прошлую встречу я забуду и уже никогда не вспомню. Так... Откуда ты родом?\n");

		FILE* race_conf;
		race_conf = fopen("config/race.conf", "r");
		if (race_conf == NULL) {
			puts("Ошибка при открытии файла конфигурации race.conf.");
			exit(1);
		}

		//skip first line
		char c = "";
		while (c != '\n') {
			c = fgetc(race_conf);
		}

		int id = 0, str[RACE_CNT], dex[RACE_CNT], con[RACE_CNT], intel[RACE_CNT], chr[RACE_CNT];
		int cnt = 0;

		while (!feof(race_conf) && id < RACE_CNT) {
			char name[6];
			fscanf(race_conf, "%d", &id);
			fscanf(race_conf, "%d", &str[cnt]);
			fscanf(race_conf, "%d", &dex[cnt]);
			fscanf(race_conf, "%d", &con[cnt]);
			fscanf(race_conf, "%d", &intel[cnt]);
			fscanf(race_conf, "%d", &chr[cnt]);
			fscanf(race_conf, "%s", &name);
			printf("%d. %8s\t\t", id, name);
			cnt++;
		}

		fclose(race_conf);

		puts("");
		for (int i = 0; i < cnt; i++) {
			printf("STR: %6d\t\t", str[i]);
		}
		puts("");
		for (int i = 0; i < cnt; i++) {
			printf("DEX: %6d\t\t", dex[i]);
		}
		puts("");
		for (int i = 0; i < cnt; i++) {
			printf("CON: %6d\t\t", con[i]);
		}
		puts("");
		for (int i = 0; i < cnt; i++) {
			printf("INT: %6d\t\t", intel[i]);
		}
		puts("");
		for (int i = 0; i < cnt; i++) {
			printf("CHR: %6d\t\t", chr[i]);
		}
		puts("\n");

		int race = 0;
		while (race < 1 || race > RACE_CNT) {
			printf("> ");
			scanf_s("%d", &race);
			getchar();
		}

		switch (race) {
		case 1:
			puts("\nХо-хо! Всегда приятно поболтать с человеком. Сейчас столько всяких тварей развелось, даже не знаешь, кто зайдет в избушку.");
			break;
		case 2:
			puts("\nПо голосу сразу понял, что ты из этих... Что ж, на безрыбье и орка приму.");
			break;
		case 3:
			puts("\nА я думал, вы все уже повымирали... Одни полукровки по округе бегают.");
			break;
		default:
			puts("\nПонял-понял.");
		}

		//CLASS
		puts("Чем по жизни занимался?\n");

		FILE* class_conf;
		class_conf = fopen("config/class.conf", "r");
		if (class_conf == NULL) {
			puts("Ошибка при открытии файла конфигурации class.conf.");
			exit(1);
		}

		//skip first line
		c = "";
		while (c != '\n') {
			c = fgetc(class_conf);
		}

		int health[CLASS_CNT], weapon_1[CLASS_CNT], weapon_2[CLASS_CNT], arm[CLASS_CNT];
		cnt = 0;
		id = 0;

		while (!feof(class_conf) && id < CLASS_CNT) {
			char name[10];
			fscanf(class_conf, "%d", &id);
			fscanf(class_conf, "%d", &health[cnt]);
			fscanf(class_conf, "%d", &weapon_1[cnt]);
			fscanf(class_conf, "%d", &weapon_2[cnt]);
			fscanf(class_conf, "%d", &arm[cnt]);
			fscanf(class_conf, "%s", &name);
			printf("%d. %16s\t", id, name);
			cnt++;
		}

		fclose(class_conf);

		puts("");
		for (int i = 0; i < cnt; i++) {
			printf("HP: %15d\t", health[i]);
		}
		puts("");
		for (int i = 0; i < cnt; i++) {
			weapon* wpn = readWeapon(weapon_1[i]);
			printf("WEAPON: %11s\t", wpn->name);
		}
		puts("");
		for (int i = 0; i < cnt; i++) {
			weapon* wpn = readWeapon(weapon_2[i]);
			if (wpn)
				printf("WEAPON: %11s\t", wpn->name);
			else
				printf("WEAPON: \t\t");
			free(wpn);
		}
		puts("");
		for (int i = 0; i < cnt; i++) {
			armour* ar = readArmour(arm[i]);
			printf("ARMOUR: %11s\t", ar->name);
			free(ar);
		}
		puts("\n");

		int class = 0;
		while (class < 1 || class > CLASS_CNT) {
			printf("> ");
			scanf_s("%d", &class);
			getchar();
		}

		switch (class) {
		case 1:
			puts("\nТогда тебя лучше не злить.");
			break;
		case 2:
			puts("\nБлагородное занятие.");
			break;
		case 3:
			puts("\nЛесной собрат, получается. Я раньше тоже таким промышлял, но потом ослеп.");
			break;
		case 4:
			puts("\nЕсли решишь что-нибудь у меня украсть, меняй на себя.");
			break;
		case 5:
			puts("\nА глаза сможешь мне подлатать? Хотя чего это я... Никто уже не сможет.");
			break;
		case 6:
			puts("\nМагия-шмагия... Не смыслю я в этом ничего. По мне, так все вы шарлатаны.");
			break;
		default:
			puts("\nПонял-понял.");
		}

		*hero = createCharacter(race, class, chName, 1);

		int choice = 0;
		printf("\nЗначит ты %s по имени %s. Уверен, что правильно себя описал? Лгунов я терпеть не могу.\n\n", (*hero)->type, (*hero)->name);
		puts("1. Да, все верно.");
		puts("2. Нет, вижу ошибку.");
		puts("3. Повтори, как я себя описал.\n");

		while (choice < 1 || choice > 3) {
			printf("> ");
			scanf_s("%d", &choice);
			getchar();
		}

		switch (choice) {
		case 3:
			choice = 0;
			printCharacter(*hero);
			puts("\nНу так что? Все правильно я запомнил?\n");
			puts("1. Да, все верно.");
			puts("2. Нет, вижу ошибку.\n");
			while (choice < 1 || choice > 2) {
				printf("> ");
				scanf_s("%d", &choice);
				getchar();
			}
			if (choice == 1) break;
		case 2:
			system("clear");
			puts("Тогда начнем сначала. Как же оно там было?.. Ах, точно.\n");
			clear(hero);
			startGame(hero);
			break;
		}
	}
	nextDay(hero);
}

void mainInventory(character** hero) {
	int invSize = printInventoryInterface(*hero);
	puts("\n\nВыберите действие:");
	puts("1. Изменить основное оружие");
	puts("2. Изменить вспомогательное оружие");
	puts("3. Изменить доспехи");
	puts("4. Использовать зелье лечения");
	puts("5. Изучить предмет");
	puts("6. Выбросить предмет");
	puts("7. <- Закрыть\n");

	int choice = 0;
	while (choice < 1 || choice > 7) {
		printf("> ");
		scanf_s("%d", &choice);
		getchar();
	}

	switch (choice) {
	case 1: {
		puts("\n\nВыберите оружие из инвентаря:\n");
		int id = 0;
		while (id < 1 || id > invSize + 1) {
			printf("> ");
			scanf_s("%d", &id);
			getchar();
		}
		equipment* eq = (*hero)->equip;
			if (eq->inventory[id - 1].type == 1) {
				if (checkMinAbility((*hero)->ability, eq->inventory[id - 1].wpn)) {
					weapon* wpn = eq->weapon_1;
					eq->weapon_1 = eq->inventory[id - 1].wpn;
					eq->inventory[id - 1].wpn = wpn;
					if (eq->weapon_1->isTwoHanded) {
						addWeapon(hero, eq->weapon_2->id);
						free(eq->weapon_2);
						eq->weapon_2 = NULL;
					}
				}
				else {
					puts("\nОружие не подходит по минимальным характеристикам.");
					Sleep(2000);
				}
			}
			else {
				puts("\nВыбрано НЕ оружие.");
				Sleep(2000);
			}
		mainInventory(hero);
		break;
	}
	case 2: {
		if ((*hero)->equip->weapon_1->isTwoHanded) {
			puts("\nНельзя взять вспомогательное оружие, поскольку основное - двуручное.");
			Sleep(3000);
		}
		else {
			puts("\nВыберите оружие из инвентаря:\n");
			int id = 0;
			while (id < 1 || id > invSize + 1) {
				printf("> ");
				scanf_s("%d", &id);
				getchar();
			}
			equipment* eq = (*hero)->equip;
			if (eq->inventory[id - 1].type == 1) {
				if (eq->inventory[id - 1].wpn->isTwoHanded) {
					puts("\nНельзя взять двуручное оружие в качестве вспомогательного.");
					Sleep(3000);
				}
				else {
					if (checkMinAbility((*hero)->ability, eq->inventory[id - 1].wpn)) {
						weapon* wpn = eq->weapon_2;
						eq->weapon_2 = eq->inventory[id - 1].wpn;
						eq->inventory[id - 1].wpn = wpn;
						if (!eq->inventory[id - 1].wpn) delInventoryItem(eq->inventory, id - 1, INV_SIZE);
					}
					else {
						puts("\nОружие не подходит по минимальным характеристикам.");
						Sleep(2000);
					}
				}
			}
			else {
				puts("\nВыбрано НЕ оружие.");
				Sleep(2000);
			}
		}
		mainInventory(hero);
		break;
	}
	case 3: {
		puts("\nВыберите доспех из инвентаря:\n");
		int id = 0;
		while (id < 1 || id > invSize + 1) {
			printf("> ");
			scanf_s("%d", &id);
			getchar();
		}
		equipment* eq = (*hero)->equip;
		if (eq->inventory[id - 1].type == 2) {
			armour* arm = eq->armour;
			eq->armour = eq->inventory[id - 1].arm;
			eq->inventory[id - 1].arm = arm;
		}
		else {
			puts("\nВыбран НЕ доспех.");
			Sleep(2000);
		}
		mainInventory(hero);
		break;
	}
	case 4: {
		puts("\nВыберите зелье лечения из инвентаря:\n");
		int id = 0;
		while (id < 1 || id > invSize + 1) {
			printf("> ");
			scanf_s("%d", &id);
			getchar();
		}
		inventory inv = (*hero)->equip->inventory[id - 1];
		if (inv.type == 3) {
			if (inv.ptn->type == 5) {
				actPotion(hero, NULL, *inv.ptn);
				delInventoryItem((*hero)->equip->inventory, id - 1, INV_SIZE);
			}
			else {
				puts("\nВыбрано НЕ зелье лечения.");
				Sleep(2000);
			}
		}
		else {
			puts("\nВыбрано НЕ зелье.");
			Sleep(2000);
		}
		mainInventory(hero);
		break;
	}
	case 5: {
		puts("\nВыберите предмет из инвентаря:\n");
		int id = 0;
		while (id < 1 || id > invSize + 1) {
			printf("> ");
			scanf_s("%d", &id);
			getchar();
		}
		inventory inv = (*hero)->equip->inventory[id - 1];
		switch (inv.type) {
		case 1:
			printWeapon(inv.wpn);
			_getch();
			break;
		case 2:
			printArmour(inv.arm);
			_getch();
			break;
		case 3:
			printPotion(inv.ptn);
			_getch();
			break;
		}
		mainInventory(hero);
		break;
	}
	case 6:
		puts("\nВыберите предмет из инвентаря:\n");
		int id = 0;
		while (id < 1 || id > invSize + 1) {
			printf("> ");
			scanf_s("%d", &id);
			getchar();
		}
		equipment* eq = (*hero)->equip;
		delInventoryItem(eq->inventory, id - 1, INV_SIZE);
		mainInventory(hero);
		break;
	case 7:
		return;
	}
}

int printInventoryInterface(character* hero) {
	system("clear");

	puts("ИНВЕНТАРЬ");
	printf("%d M\n\n", hero->money);

	puts("ОСН ОРУЖИЕ:");
	printWeapon(hero->equip->weapon_1);

	puts("\nВСПОМ ОРУЖИЕ:");
	printWeapon(hero->equip->weapon_2);

	puts("\nДОСПЕХ:");
	printArmour(hero->equip->armour);

	for (int i = 0; i < INV_SIZE; i++) {
		inventory inv = hero->equip->inventory[i];
		switch (inv.type) {
		case 1:
			printf("\n%d. %16s\tT: %s\tC: %3d M", i+1, inv.wpn->name, "ОРУЖИЕ", inv.wpn->cost);
			break;
		case 2:
			printf("\n%d. %16s\tT: %s\tC: %3d M", i+1, inv.arm->name, "ДОСПЕХ", inv.arm->cost);
			break;
		case 3:
			printf("\n%d. %16s\tT: %s\tC: %3d M", i+1, inv.ptn->name, "ЗЕЛЬЕ", inv.ptn->cost);
			break;
		case 0:
			return i + 1;
		}
	}
	return INV_SIZE;
}


int fullInventory(character** hero) { // попытка очистить инвентарь
	puts("\nНет места! Открыть инвентарь?");
	puts("1. Да");
	puts("2. Нет\n");

	int choice = 0;
	while (choice < 1 || choice > 2) {
		printf("> ");
		scanf_s("%d", &choice);
		getchar();
	}

	if (choice == 1)
		mainInventory(hero);

	return choice;
}

int mainFight(character** hero, character** enemy) {

	// сохранить начальные параметры персонажа
	character* copy = (character*)malloc(sizeof(character));
	ability* ab = (ability*)malloc(sizeof(ability));
	equipment* eq = (equipment*)malloc(sizeof(equipment));
	armour* arm = (armour*)malloc(sizeof(armour));
	eq->armour = arm;
	copy->equip = eq;
	copy->ability = ab;
	copyCharacter(&copy, hero);

	int runaway = 0;

	while ((*hero)->hp > 0) {
		runaway = heroFight(hero, enemy);
		if (runaway || (*enemy)->hp <= 0) break;
		enemyFight(hero, enemy);
	}
	if ((*hero)->hp <= 0) {
		puts("\nВы мертвы.");
		Sleep(3000);
		exit(0);
	}
	else if ((*enemy)->hp <= 0) {
		system("clear");
		puts("Победа!");
		giveReward(hero, (*enemy)->lvl / 3);

		copyCharacter(hero, &copy);

		int exp = (*enemy)->lvl * ENEMY_EXP;
		int money = rand() % 5 + (*enemy)->lvl * ENEMY_EXP;
		printf("Получено %d опыта и %d золота\n", exp, money);
		(*hero)->money += money;
		if (addExp(hero, exp))
			lvlUp(hero);
	}
	return runaway;
}

int heroFight(character** hero, character** enemy) {
	printFightInterface(*hero, *enemy);
	puts("Выберите действие:");
	puts("1. Использовать оружие");
	puts("2. Использовать способность");
	puts("3. Использовать зелье");
	puts("4. Попытаться сбежать\n");

	int choice = 0;
	while (choice < 1 || choice > 4) {
		printf("> ");
		scanf_s("%d", &choice);
		getchar();
	}

	switch (choice) {
	case 1:
		weaponFight(hero, enemy);
		break;
	case 2:
		if ((*hero)->mp == 0) {
			puts("\nВы слишком устали для этого.");
			Sleep(1000);
			heroFight(hero, enemy);
		}
		else
			powerFight(hero, enemy);
		break;
	case 3:
		potionFight(hero, enemy);
		break;
	case 4: {
		int r = rand() % 10;
		puts("\nПопытка побега...");
		Sleep(1500);
		if (r > 5 + (*hero)->ability->dexterity / 5) {
			puts("\nСбежать не удалось!");
			Sleep(3000);
		}
		else {
			puts("\nВы сбежали!");
			Sleep(3000);
			return 1;
		}
		break;
	}
	}
	return 0;
}

void printFightAct(character* ch, char act[], int points) {
	if (points)
		printf("\n%s использует %s с силой %d.", ch->name, act, points);
	else
		printf("\n%s использует %s и промахивается!", ch->name, act);
	Sleep(3000);
}

void enemyFight(character** hero, character** enemy) {

	int id = rand() % 2;
	weapon* wpn = (*enemy)->equip->weapon_1;

	printFightInterface(*hero, *enemy);
	int lvlBust = ((*enemy)->lvl - 1) * LVL_BUST;
	int points = actPower(enemy, hero, wpn->attack + lvlBust, wpn->powers[id]);
	printFightAct(*enemy, wpn->powers[id].name, points);
}

void weaponFight(character** hero, character** enemy) {
	printFightInterface(*hero, *enemy);

	weapon* wpn1 = (*hero)->equip->weapon_1;
	weapon* wpn2 = (*hero)->equip->weapon_2;
	int isWpn2 = 5;

	puts("Выберите действие:");
	printf("1. %s\n", wpn1->powers[0].name);
	printf("2. %s\n", wpn1->powers[1].name);
	if (wpn2) {
		printf("3. %s\n", wpn2->powers[0].name);
		printf("4. %s\n", wpn2->powers[1].name);
		puts("5. <- Назад\n");
	}
	else {
		puts("3. <- Назад\n");
		isWpn2 = 3;
	}

	int choice = 0;
	while (choice < 1 || choice > isWpn2) {
		printf("> ");
		scanf_s("%d", &choice);
		getchar();
	}

	int points;
	switch (choice) {
	case 1:
		points = actPower(hero, enemy, wpn1->attack, wpn1->powers[0]);
		printFightAct(*hero, wpn1->powers[0].name, points);
		break;
	case 2:
		points = actPower(hero, enemy, wpn1->attack, wpn1->powers[1]);
		printFightAct(*hero, wpn1->powers[1].name, points);
		break;
	case 3:
		if (wpn2) {
			points = actPower(hero, enemy, wpn2->attack, wpn1->powers[0]);
			printFightAct(*hero, wpn2->powers[0].name, points);
		}
		else
			heroFight(hero, enemy);
		break;
	case 4:
		points = actPower(hero, enemy, wpn2->attack, wpn1->powers[1]);
		printFightAct(*hero, wpn2->powers[1].name, points);
		break;
	case 5:
		heroFight(hero, enemy);
		break;
	}
}

void powerFight(character** hero, character** enemy) {
	printFightInterface(*hero, *enemy);

	int pwrCnt = (*hero)->lvl / 5 + 1;
	puts("Выберите действие:");
	printf("1. %s\n", (*hero)->powers[0].name);
	for (int i = 1; i < pwrCnt; i++) {
		printf("%d. %s\n", i+1, (*hero)->powers[i].name);
	}
	printf("%d. <- Назад\n\n", pwrCnt+1);

	int id = 0;
	while (id < 1 || id > pwrCnt + 1) {
		printf("> ");
		scanf_s("%d", &id);
		getchar();
	}

	if (pwrCnt >= id) {
		(*hero)->mp--;
		int points = actPower(hero, enemy, 0, (*hero)->powers[id-1]);
		printFightAct(*hero, (*hero)->powers[id-1].name, points);
	}
	else
		heroFight(hero, enemy);
}

void potionFight(character** hero, character** enemy) {
	printFightInterface(*hero, *enemy);

	puts("Выберите действие:");
	int ptnCnt = 0;
	int ptnNums[10] = { -1 };
	for (int i = 0; i < INV_SIZE; i++) {
		inventory inv = (*hero)->equip->inventory[i];
		if (inv.type == 3) {
			printf("%d. %s\n", ptnCnt + 1, inv.ptn->name);
			ptnNums[ptnCnt] = i;
			ptnCnt++;
		}
	}
	if (ptnCnt == 0)
		puts("Запас зелий иссяк!\n");
	printf("%d. <- Назад\n\n", ptnCnt + 1);

	int id = 0;
	while (id < 1 || id > ptnCnt + 1) {
		printf("> ");
		scanf_s("%d", &id);
		getchar();
	}

	if (ptnCnt >= id) {
		int num = ptnNums[id - 1];
		actPotion(hero, enemy, *(*hero)->equip->inventory[num].ptn);
		printFightAct(*hero, (*hero)->equip->inventory[num].ptn->name, (*hero)->equip->inventory[num].ptn->points);
		delInventoryItem((*hero)->equip->inventory, num, INV_SIZE);
		Sleep(3000);
	}
	else
		heroFight(hero, enemy);
}

void lvlUp(character** hero) {
	puts("\nУровень повышен!\n");
	printf("Вам доступно %d очков характеристик.\n", LVL_POINTS);

	for (int i = 0; i < LVL_POINTS; i++) {
		printf("\nВыберите %d увеличиваемую характеристику:\n", i+1);
		puts("1. СИЛА");
		puts("2. ЛОВКОСТЬ");
		puts("3. ТЕЛОСЛОЖЕНИЕ");
		puts("4. ИНТЕЛЛЕКТ");
		puts("5. ХАРИЗМА");
		puts("6. Посмотреть характеристики персонажа\n");

		int choice = 0;
		while (choice < 1 || choice > 6) {
			printf("> ");
			scanf_s("%d", &choice);
			getchar();
		}

		switch (choice) {
		case 1:
			(*hero)->ability->strength++;
			break;
		case 2:
			(*hero)->ability->dexterity++;
			break;
		case 3:
			(*hero)->ability->constitution++;
			break;
		case 4:
			(*hero)->ability->intelligence++;
			break;
		case 5:
			(*hero)->ability->charisma++;
			break;
		case 6:
			system("clear");
			printCharacter(*hero);
			i--;
			_getch();
			break;
		}
		system("clear");
	}
	puts("");
}

void printFightInterface(character* hero, character* enemy) {
	system("clear");
	printf("%16s\t\t\t\t%16s\n", hero->name, enemy->name);
	printf("%16s\t\t\t\t%16s\n", hero->type, enemy->type);
	printf("%12d LVL\t\t\t\t%12d LVL\n", hero->lvl, enemy->lvl);
	printf("HP: %7d / %2d\t\t\t\tHP: %7d / %2d\n", hero->hp, hero->maxHp, enemy->hp, enemy->maxHp);
	printf("MP: %7d / %2d\n\n", hero->mp, hero->maxMp);
	//graphic?
}

void createTrader(character** hero, int type) {
	system("clear");
	printDayInterface();
	puts("Вы встречаете бродячего торговца!");
	// spawn and print goods
	inventory goods[TRADE_CNT];
	switch (type) {
	case 1: // weapon
		puts("В его сумках есть немного оружия для вас.\n");
		Sleep(2000);
		for (int i = 0; i < TRADE_CNT; i++) {
			int id = rand() % WEAPON_CNT + 1;
			goods[i].type = 1;
			goods[i].wpn = readWeapon(id);
		}
		break;
	case 2: // armour
		puts("В его сумках есть немного доспехов для вас.\n");
		Sleep(2000);
		for (int i = 0; i < TRADE_CNT; i++) {
			int id = rand() % ARMOUR_CNT + 1;
			goods[i].type = 2;
			goods[i].arm = readArmour(id);
		}
		break;
	case 3: // potion
		puts("В его сумках есть немного зелий для вас.\n");
		Sleep(2000);
		for (int i = 0; i < TRADE_CNT; i++) {
			int id = rand() % POTION_CNT + 1;
			goods[i].type = 3;
			goods[i].ptn = readPotion(id);
		}
		break;
	}

	int tradeCnt = 0;
	trade(hero, goods, &tradeCnt);

	switch (goods[0].type) {
	case 1: // weapon
		for (int i = 0; i < TRADE_CNT - tradeCnt; i++) {
			if (goods[i].type) free(goods[i].wpn);
		}
		break;
	case 2: // armour
		for (int i = 0; i < TRADE_CNT - tradeCnt; i++) {
			if (goods[i].type) free(goods[i].arm);
		}
		break;
	case 3: // potion
		for (int i = 0; i < TRADE_CNT - tradeCnt; i++) {
			if (goods[i].type) free(goods[i].ptn);
		}
		break;
	}
}

void trade(character** hero, inventory goods[], int* tradeCnt) {

	printTraderGoods(goods, tradeCnt, *hero);

	puts("Выберите действие:");
	puts("1. Купить товар.");
	puts("2. Продать товар.");
	puts("3. Покинуть торговца.\n");

	int choice = 0;
	while (choice < 1 || choice > 3) {
		printf("> ");
		scanf_s("%d", &choice);
		getchar();
	}

	switch (choice) {
	case 1: {
		system("clear");
		printTraderGoods(goods, tradeCnt, *hero);
		puts("Выберите номер товара:");
		puts("0. Отказаться от покупки.\n");

		int id = -1;
		while (id < 0 || id > TRADE_CNT - *tradeCnt) { // tradeCnt - количество купленного товара
			printf("> ");
			scanf_s("%d", &id);
			getchar();
		}

		if (id) {
			id--;
			int chr = (*hero)->ability->charisma / 4;
			switch (goods[id].type) {
			case 1:
				if (goods[id].wpn->cost - chr <= (*hero)->money) {
					addWeapon(hero, goods[id].wpn->id);
					(*hero)->money -= goods[id].wpn->cost - chr;
					delInventoryItem(goods, id, TRADE_CNT - (*tradeCnt));
					(*tradeCnt)++;
				}
				else {
					puts("Недостаточно денег!");
					Sleep(3000);
				}
				break;
			case 2:
				if (goods[id].arm->cost - chr <= (*hero)->money) {
					addArmour(hero, goods[id].arm->id);
					(*hero)->money -= goods[id].arm->cost - chr;
					delInventoryItem(goods, id, TRADE_CNT - (*tradeCnt));
					(*tradeCnt)++;
				}
				else {
					puts("Недостаточно денег!");
					Sleep(3000);
				}
				break;
			case 3:
				if (goods[id].ptn->cost - chr <= (*hero)->money) {
					addPotion(hero, goods[id].ptn->id);
					(*hero)->money -= goods[id].ptn->cost - chr;
					delInventoryItem(goods, id, TRADE_CNT - (*tradeCnt));
					(*tradeCnt)++;
				}
				else {
					puts("Недостаточно денег!");
					Sleep(3000);
				}
				break;
			}
		}
		break;
	}
	case 2: {
		int size = printInventoryInterface(*hero);
		puts("\n\nВыберите номер товара:");
		puts("0. Отказаться от продажи.\n");

		int id = -1;
		while (id < 0 || id > size) {
			printf("> ");
			scanf_s("%d", &id);
			getchar();
		}

		if (id) {
			int chr = (*hero)->ability->charisma / 4;
			switch ((*hero)->equip->inventory[id - 1].type) {
			case 1:
				(*hero)->money += (*hero)->equip->inventory[id - 1].wpn->cost + chr;
				break;
			case 2:
				(*hero)->money += (*hero)->equip->inventory[id - 1].arm->cost + chr;
				break;
			case 3:
				(*hero)->money += (*hero)->equip->inventory[id - 1].ptn->cost + chr;
				break;
			}
			delInventoryItem((*hero)->equip->inventory, id - 1, INV_SIZE);
		}
		break;
	}
	case 3:
		return;
		break;
	}
	trade(hero, goods, tradeCnt);
}

void printTraderGoods(inventory goods[], int* tradeCnt, character* hero) {
	switch (goods[0].type) {
	case 1: // weapon
		for (int i = 0; i < TRADE_CNT - *tradeCnt; i++) {
			printf("%d.\n", i + 1);
			printWeapon(goods[i].wpn);
			puts("");
		}
		break;
	case 2: // armour
		for (int i = 0; i < TRADE_CNT - *tradeCnt; i++) {
			printf("%d.\n", i + 1);
			printArmour(goods[i].arm);
			puts("");
		}
		break;
	case 3: // potion
		for (int i = 0; i < TRADE_CNT - *tradeCnt; i++) {
			printf("%d.\n", i + 1);
			printPotion(goods[i].ptn);
			puts("");
		}
		break;
	}
	printf("\nБлагодаря своему красноречию вы можете покупать и продавать товары на %d M выгоднее.\n", hero->ability->charisma / 4);
	printf("У вас есть %d M.\n\n", hero->money);
}

void save(character** hero) {
	FILE* save;
	save = fopen("save.txt", "w");
	if (save == NULL) {
		puts("Ошибка при открытии файла сохранения save.txt.");
		exit(1);
	}

	fprintf(save, "%s ", (*hero)->name);
	fprintf(save, "%s ", (*hero)->type);
	fprintf(save, "%d ", (*hero)->class);
	fprintf(save, "%d ", (*hero)->race);
	fprintf(save, "%d ", (*hero)->lvl);
	fprintf(save, "%d ", (*hero)->exp);
	fprintf(save, "%d ", (*hero)->maxHp);
	fprintf(save, "%d ", (*hero)->maxMp);
	fprintf(save, "%d ", (*hero)->money);
	fprintf(save, "%d ", (*hero)->ability->strength);
	fprintf(save, "%d ", (*hero)->ability->dexterity);
	fprintf(save, "%d ", (*hero)->ability->constitution);
	fprintf(save, "%d ", (*hero)->ability->intelligence);
	fprintf(save, "%d ", (*hero)->ability->charisma);
	fprintf(save, "%d ", (*hero)->equip->weapon_1->id);
	if (!(*hero)->equip->weapon_1->isTwoHanded)
		fprintf(save, "%d ", (*hero)->equip->weapon_2->id);
	else
		fprintf(save, "%d ", 0);
	fprintf(save, "%d ", (*hero)->equip->armour->id);
	for (int i = 0; i < INV_SIZE; i++) {
		fprintf(save, "%d ", (*hero)->equip->inventory[i].type);
		switch ((*hero)->equip->inventory[i].type) {
		case 1:
			fprintf(save, "%d ", (*hero)->equip->inventory[i].wpn->id);
			break;
		case 2:
			fprintf(save, "%d ", (*hero)->equip->inventory[i].arm->id);
			break;
		case 3:
			fprintf(save, "%d ", (*hero)->equip->inventory[i].ptn->id);
			break;
		}
	}
	fprintf(save, "%d", day);
	fclose(save);
}

void city(character** hero) {
	system("clear");
	printDayInterface();
	puts("Вы попали в город!\n");

	puts("Ваше здоровье и мана восстановлены.\n");
	(*hero)->hp = (*hero)->maxHp;
	(*hero)->mp = (*hero)->maxMp;

	puts("Ваш прогресс сохранен.");
	save(hero);
	
	nextDay(hero);
}

void chest(character** hero) {
	puts("Перед вами сундук.");
	int reward = 0;
	int abil = rand() % 5 + 1;
	switch (abil) {
	case 1:
		puts("На нем нет замка, но вы понимаете, что, приложив достаточно силы, можно разломать крышку и добраться до содержимого...\n");
		Sleep(2000);
		if (rand() % 10 > 5 - (*hero)->ability->strength / 5) {
			puts("Вы без труда пробиваете крышку своим кулаком.");
			reward = 1;
		}
		break;
	case 2:
		puts("Он закрыт на тяжелый резной замок. Вы можете попробовать взломать его...\n");
		Sleep(2000);
		if (rand() % 10 > 5 - (*hero)->ability->dexterity / 5) {
			puts("Вы легко взламываете замок.");
			reward = 1;
		}
		break;
	case 3:
		puts("Вместо замка на крышке располагается механизм, похожий на песочные часы. Кажется, если дождаться определенного времени, сундук откроется сам...\n");
		Sleep(2000);
		if (rand() % 10 > 5 - (*hero)->ability->constitution / 5) {
			puts("Спустя несколько часов безделья сундук наконец открылся.");
			reward = 1;
		}
		break;
	case 4: 
		puts("Он весь покрыт странными письменами на неизвестном языке. Возможно, если разобраться в написаннном, то вам удасться вскрыть замок...\n");
		Sleep(2000);
		if (rand() % 10 > 5 - (*hero)->ability->intelligence / 5) {
			puts("Вскоре слова начинают обретать смысл, и вы читаете вслух заклинание. Замок рассыпается в пыль.");
			reward = 1;
		}
		break;
	case 5:
		puts("Там, где должен располагаться замок, находится нечто, похожее на лицо. Оно улыбается при виде вас. Похоже, придется разговорить странного собеседника, чтобы добраться до сокровищ...\n");
		Sleep(2000);
		if (rand() % 10 > 5 - (*hero)->ability->strength / 5) {
			puts("После пару удачных шуток и спетой народной песни, лицо широко раскрывает свой рот, внутри которого вы видете содержимое сундука.");
			reward = 1;
		}
		break;
	}
	Sleep(1000);
	if (reward) {
		giveReward(hero, (*hero)->lvl / 3);
	}
	else {
		puts("\nВы устали пытаться.");
		puts("Повезет в следующий раз!");
	}
	nextDay(hero);
}

void giveReward(character** hero, int lvl) {
	int id, type = rand() % 3 + 1;
	puts("\nВаша награда:");
	switch (type) {
	case 1:
		id = rand() % 6 + lvl * 6 + 1;
		while (addWeapon(hero, id) == INV_SIZE) { // если функция вернула длину массива, значит цикл был пройден насквозь и оружие НЕ добавлено
			if (fullInventory(hero) == 2) break; // если игрок отказался очищать инвентарь
			else {
				system("clear");
				puts("\nВаша награда:");
			}
		}
		break;
	case 2:
		id = rand() % 4 + lvl * 4 + 1;
		while (addArmour(hero, id) == INV_SIZE) {
			if (fullInventory(hero) == 2) break;
			else {
				system("clear");
				puts("\nВаша награда:");
			}
		}
		break;
	case 3:
		id = rand() % (13 * (lvl + 1)) + 1;
		while (addPotion(hero, id) == INV_SIZE) {
			if (fullInventory(hero) == 2) break;
			else {
				system("clear");
				puts("\nВаша награда:");
			}
		}
		break;
	}
}

void enterCave(character** hero) {
	int type = rand() % 3;
	switch (type) {
	case 0:
		printDayInterface();
		puts("В пещере пусто!");
		nextDay(hero);
		break;
	case 1:
		printDayInterface();
		puts("В пещере оказался враг!");
		Sleep(2000);
		int race = rand() % ENEMY_RACE_CNT + 21;
		int class = rand() % ENEMY_CLASS_CNT + 21;
		character* enemy = createCharacter(race, class, "CAVE BEAST", (*hero)->lvl);
		mainFight(hero, &enemy);
		clear(&enemy);
		break;
	case 2:
		printDayInterface();
		chest(hero);
		break;
	}
}