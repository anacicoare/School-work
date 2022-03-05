#include <stdio.h>
#include <string.h>
#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include "functions.h"
int main()
{

	FILE* f;
	int i, n, nr_litere;
	char file_name[30][30], s[80], * p, * cod_html1, * cod_html2;
	site* site_web;

	f = fopen("master.txt", "r");
	n = 0;

	site_web = (struct site*)malloc(3 * sizeof(site)); //alocam dinamic site-ul
	n = 0;
	while (fscanf(f, "%s", &file_name[n]) != EOF)
	{
		n++;
		if (n % 3 == 0)
			site_web = (struct site*)realloc(site_web, (n + 3) * sizeof(site)); //realocam cand trecem de cate 3 siteuri deja alocate

	}
	fclose(f);
	for (i = 0; i < n; i++)
	{
		f = fopen(file_name[i], "r");
		fscanf(f, "%s", &(site_web + i)->url);
		fscanf(f, "%s", &(site_web + i)->lung_octeti);
		fscanf(f, "%s", &(site_web + i)->nr_access);
		fscanf(f, "%s", &(site_web + i)->checksum); //introducem in memorie primii termeni
		fscanf(f, "%s", &s);
		nr_litere = strlen(s);
		(site_web + i)->cod_html = malloc(nr_litere * sizeof(char) + 1); //alocam dinamic codul html pentru exact cate caractere contine
		strcpy((site_web + i)->cod_html, s);

		while (fgets(s, 80, f) != NULL)
		{
			nr_litere = nr_litere + strlen(s);
			(site_web + i)->cod_html = realloc((site_web + i)->cod_html, nr_litere * sizeof(char) + 1);
			strcat((site_web + i)->cod_html, s);
		}
		cod_html1 = malloc(nr_litere * sizeof(char) + 1);
		strcpy(cod_html1, (site_web + i)->cod_html); //facem o copie pentru a nu pierde sirul initial
		p = strstr(cod_html1, "<title>");
		p = strtok(p, "<>");
		p = strtok(NULL, "<>");
		strcpy((site_web + i)->title, p); //am gasit titlul
		cod_html2 = malloc(nr_litere * sizeof(char) + 1);
		strcpy(cod_html2, (site_web + i)->cod_html); //facem o copie pentru a nu pierde sirul initial
		p = strstr(cod_html2, "<p");
		p = strtok(p, "<>");
		p = strtok(NULL, "<>");
		nr_litere = strlen(p);
		(site_web + i)->content = malloc(nr_litere * sizeof(char) + 1);
		strcpy((site_web + i)->content, p);//am gasit titlul (ce se afla intre <p ... > si </p>

		fclose(f);
		free(cod_html1);
		free(cod_html2);
		//inchidem fisierul si eliberam memoria pt urmatoarea utilizare
	}
	int nr_site;
	nr_site = n;

	for (i = 0; i < n; i++) //vom introduce culorile de bg si text pentru fiecare dintre site-uri folosind enum 
	{
		nr_litere = strlen((site_web + i)->cod_html);
		cod_html1 = calloc(nr_litere + 1, sizeof(char));

		strcpy(cod_html1, (site_web + i)->cod_html);
		p = strstr(cod_html1, "<p");
		p = strtok(p, "<>");
		if (strlen(p) > 2) //exista css pentru site-ul respectiv
		{
			p = strstr(p, "\"color");
			if (p != NULL)
			{
				p = strtok(p, ":");
				p = strtok(NULL, ";");
				if (strcmp(p, "red") == 0)
					(site_web + i)->text_color = red;
				if (strcmp(p, "black") == 0)
					(site_web + i)->text_color = black;
				if (strcmp(p, "green") == 0)
					(site_web + i)->text_color = green;
				if (strcmp(p, "white") == 0)
					(site_web + i)->text_color = white;
				if (strcmp(p, "blue") == 0)
					(site_web + i)->text_color = blue;
				if (strcmp(p, "yellow") == 0)
					(site_web + i)->text_color = yellow;
				//pentru culoarea textului
			}
			else
				(site_web + i)->text_color = black; //daca nu avem css pt text

			strcpy(cod_html1, (site_web + i)->cod_html);
			p = strstr(cod_html1, "<p");
			p = strtok(p, "<>");
			p = strstr(p, "background-color");
			if (p != NULL) //daca avem css pentru bg
			{
				p = strtok(p, ":");
				p = strtok(NULL, ";");

				if (strcmp(p, "red") == 0)
					(site_web + i)->background_color = red;
				if (strcmp(p, "black") == 0)
					(site_web + i)->background_color = black;
				if (strcmp(p, "green") == 0)
					(site_web + i)->background_color = green;
				if (strcmp(p, "white") == 0)
					(site_web + i)->background_color = white;
				if (strcmp(p, "blue") == 0)
					(site_web + i)->background_color = blue;
				if (strcmp(p, "yellow") == 0)
					(site_web + i)->background_color = yellow;
			}
			else
				(site_web + i)->background_color = white; //daca nu avem css pt background
		}
		else
		{
			(site_web + i)->background_color = white;
			(site_web + i)->text_color = black;
		}

		free(cod_html1);
	}

	//task 1, incarcarea in memorie


	noecho();
	initscr(); //initializam modul curses
	cbreak(); //one-character-at-a-time (orice caractere care nu sunt citite raman in buffer pentru a fi introduse ulterior)

	WINDOW* win;
	int linii, coloane;
	getmaxyx(stdscr, linii, coloane); //in linii si coloane vor fi dimensiunile stdscr-ului

	curs_set(0);
	//initializam cursorul ca fiind invizibil

	attron(A_STANDOUT);
	move(linii - 4, 0);
	printw("Legenda:");
	move(linii - 3, 0);
	printw("Apasati C pentru a afisa bara de cautare");
	move(linii - 2, 0);
	printw("Apasati Q pentru a inchide programul");
	move(linii - 1, 0);
	attroff(A_STANDOUT);
	//legenda

	attron(A_BOLD);
	mvprintw(linii / 2, (coloane - strlen("BROWSERUL LUI BIJU")) / 2, "BROWSERUL LUI BIJU");
	attroff(A_BOLD);
	//titlul browserului 


	char choice1, choice2;
	choice1 = getch();
	while (choice1 != 'Q' && choice1 != 'C') //in cazul in care nu s-a introdus o tasta valida
	{
		curs_set(0);
		noecho();
		clear();
		printw("Ati introdus o tasta invalida. OPTIUNI: Q - quit sau C - cautare.\n");
		move(1, 0);
		printw("Tasta introdusa: %c", choice1);
		refresh();
		choice1 = getch();
		curs_set(1);
	}

	echo(); //toggle-on pentru afisarea unui caracter odata cu scrierea sa

	char input[100];
	int n_cautare_simpla, n_cautare_avansata;

	curs_set(1); //resetam cursorul vizibil pentru bara de cautare

	switch (choice1)
	{
	case 'Q': //cazul quit
		for (i = 0; i < n; i++)
		{
			free((site_web + i)->content);
			free((site_web + i)->cod_html);
		}
		free(site_web);
		endwin();
		return 0;

	case 'C': //cazul cautare
		clear();

		char input[30], caracter;
		int nr_caractere_input;

		for (i = 0; i < coloane; i++)
		{
			mvprintw(0, i, "_");
			mvprintw(3, i, "_");
		}
		//bara de cautare

		attron(A_STANDOUT);
		move(linii - 3, 0);
		printw("Legenda:");
		move(linii - 2, 0);
		printw("Apasati Q pentru a inchide browserul");
		move(linii - 1, 0);
		printw("Apasati ENTER pentru a bloca campul de cautare");
		attroff(A_STANDOUT);
		//legenda

		move(2, (coloane - 30) / 2);

		nr_caractere_input = 0; //incepem sa construim sirul input de la tastatura 
		caracter = getch();
		refresh();
		while (caracter != '\n')
		{
			delch();
			input[nr_caractere_input] = caracter;
			nr_caractere_input++;
			if (caracter == 'Q') //cazul quit
			{
				for (i = 0; i < n; i++)
				{
					free((site_web + i)->content);
					free((site_web + i)->cod_html);
				}
				free(site_web); //eliberam memoria

				endwin();//oprirea modului curses
				return 0;
			}
			if (caracter == 8) //cazul backspace
			{
				nr_caractere_input = nr_caractere_input - 2;
				//se sterg 2 caractere, BS si caracterul care se doreste a fi sters
			}
			caracter = getch();
		} //am blocat linia de cautare

		input[nr_caractere_input] = '\0'; //terminam sirul introdus
		refresh();

		for (i = 0; i <= strlen("Apasati ENTER pentru a bloca campul de cautare"); i++)
			mvprintw(linii - 1, i, " "); //golim ultima linie pentru a putea scrie peste

		attron(A_STANDOUT);
		move(linii - 4, 0);
		printw("Legenda:");
		move(linii - 3, 0);
		printw("Apasati S pentru a selecta cautarea simpla");
		move(linii - 2, 0);
		printw("Apasati A pentru a selecta cautarea avansata");
		move(linii - 1, 0);
		printw("Apasati Q pentru a parasi browserul");
		attroff(A_STANDOUT);
		//legenda

		choice2 = getch();
		while (choice2 != 'S' && choice2 != 'A' && choice2 != 'Q') //cat nu am introdus o tasta valida
		{
			noecho();
			clear();
			printw("Ati introdus o tasta invalida. OPTIUNI: S - cautare simpla, A - cautare avansata, Q - quit.\n");
			move(1, 0);
			printw("Tasta introdusa: %c", choice2);
			refresh();
			choice2 = getch();
		}
		if (choice2 == 'Q') //cazul quit
		{
			endwin();
			return 0;
		}
		if (choice2 == 'S') //cazul cautare simpla
		{
			clear();
			move(0, 0);

			char* word, * content;
			int aparitii[30];
			word = strtok(input, " ");
			int j = 0; //nu avem niciun element in aparitii, unde vom stoca numarul site-urilor care contin cuvinte
			while (word != NULL) //cat timp nu am analizat toate cuvintele
			{
				for (i = 0; i < nr_site; i++)
				{
					content = malloc(strlen((site_web + i)->content) * sizeof(char) + 1);
					strcpy(content, (site_web + i)->content); //facem o copie a continutului site-ului i

					if (check_word_in_string(content, word)) //verificam daca apare cuvantul in site
					{

						aparitii[j] = i; //notam site-ul care contine cuvantul
						int ok = 0;
						for (int k = 0; k < j; k++)
						{
							if (aparitii[k] == i)
								ok = 1;
						} //verificam daca este deja notat site-ul
						if (ok == 0)
						{
							aparitii[j] = i; //notam site-ul care contine cuvantul
							j++;
						}
					}
					free(content);
				}

				word = strtok(NULL, " "); //analizam urmatorul cuvant
			}
			int (*cmp[2])(char*, char*) = { cmp_crescator,cmp_descrescator };
			ordonare_task2(site_web, aparitii, j, cmp[0]);

			//task2 - cautare simpla

			int nr_site_afisate, linie_curenta;
			char linie_afisata[30][102];
			nr_site_afisate = j;
			linie_curenta = 0;
			move(linie_curenta, 0);
			if (nr_site_afisate == 0)
			{
				printw("Nu exista site-uri care contin cuvantul %s. Apasati orice tasta pentru a inchide browserul", input);
				getch();
				for (i = 0; i < n; i++)
				{
					free((site_web + i)->content);
					free((site_web + i)->cod_html);
				}
				free(site_web); //eliberam memoria
				free(word);
				endwin();
				return 0;
			}

			ITEM** items;
			int choice3;
			MENU* menu;
			ITEM* cur_item;
			//declarare elemente pentru meniu

			keypad(stdscr, TRUE);
			//accepta KEY_UP si KEY_DOWN

			items = (ITEM**)calloc(nr_site_afisate + 1, sizeof(ITEM*));
			for (i = 0; i < nr_site_afisate; ++i)
				items[i] = new_item((site_web + aparitii[i])->url, (site_web + aparitii[i])->title);
			items[nr_site_afisate] = (ITEM*)NULL;
			//creare itemi meniu

			noecho();
			menu = new_menu((ITEM**)items);
			menu_opts_off(menu, O_ONEVALUE);
			post_menu(menu);
			//creare si afisare meniu cu itemii initializati anterior

			refresh();

			attron(A_STANDOUT);
			move(linii - 3, 0);
			printw("Legenda");
			move(linii - 2, 0);
			printw("Apasati Q pentru a inchide browserul");
			move(linii - 1, 0);
			printw("Apasati ENTER pentru a selecta un site");
			attroff(A_STANDOUT);
			//legenda

			while ((choice3 = getch()) != 'Q')
			{
				switch (choice3)
				{
				case KEY_DOWN: //scroll in jos in meniu
					menu_driver(menu, REQ_DOWN_ITEM);
					break;
				case KEY_UP: //scroll in sus in meniu
					menu_driver(menu, REQ_UP_ITEM);
					break;
				case 10: //optiunea ENTER - selecteaza un item din meniu
					curs_set(0); //eliminam cursorul cand vizualizam pagina
					clear();
					refresh();

					attron(A_STANDOUT);
					move(linii - 3, 0);
					printw("Legenda:");
					move(linii - 2, 0);
					printw("Apasati Q pentru a parasi browserul");
					move(linii - 1, 0);
					printw("Apasati B pentru a reveni la pagina de rezultate");
					attroff(A_STANDOUT);
					//legenda

					char link[30];
					int site_de_afisat;
					strcpy(link, item_name(current_item(menu)));
					for (i = 0; i < nr_site_afisate; i++)
						if (strcmp(link, (site_web + aparitii[i])->url) == 0)
							site_de_afisat = aparitii[i];

					start_color();
					init_pair(site_de_afisat, (site_web + site_de_afisat)->text_color, (site_web + site_de_afisat)->background_color);
					//initializam culorile si perechea de culori specifica site-ului curent

					mvprintw(0, (coloane - strlen((site_web + site_de_afisat)->title)) / 2, "%s", (site_web + site_de_afisat)->title); //titlul

					attron(COLOR_PAIR(site_de_afisat));
					move(6, 0);
					printw("%s", (site_web + site_de_afisat)->content);
					attroff(COLOR_PAIR(site_de_afisat));

					pos_menu_cursor(menu);
					break;
				case 'Q': //opiunea QUIT - inchide programul
				{
					endwin();
					return 0;
				}
				break;
				case 'B': //optiunea BACK - intoarce utilizatorul la pagina cautarii
				{
					unpost_menu(menu);
					clear();
					refresh();
					post_menu(menu);
					refresh();
					//refacem meniul in cazul in care se doreste intoarcerea la el

					attron(A_STANDOUT);
					move(linii - 3, 0);
					printw("Legenda");
					move(linii - 2, 0);
					printw("Apasati Q pentru a inchide browserul");
					move(linii - 1, 0);
					printw("Apasati ENTER pentru a selecta un site");
					attroff(A_STANDOUT);
					//legenda
				}
				}
			}

			unpost_menu(menu);
			for (i = 0; i < n; i++)
			{
				free((site_web + i)->content);
				free((site_web + i)->cod_html);
			}
			free(site_web);
			free(word);
			for (i = 0; i < nr_site_afisate; ++i)
				free_item(items[i]);
			free_menu(menu);
			endwin();
			//dealocam memoria si oprim modul curses
		}
		if (choice2 == 'A')
		{
			clear();
			move(0, 0);

			char* copie_input, * input_vector_cuvinte, * word, * content;
			int nr_litere_input, aparitii[30];
			nr_litere_input = strlen(input);
			copie_input = (char*)malloc((nr_litere_input + 1) * sizeof(char));


			strcpy(copie_input, input);
			input_vector_cuvinte = strtok(copie_input, "-\"");
			word = strtok(input_vector_cuvinte, " ");
			int j = 0; //nu avem niciun element in aparitii, unde vom stoca numarul site-urilor care contin cuvinte

			while (word != NULL) //cat timp nu am analizat toate cuvintele
			{
				for (i = 0; i < n; i++)
				{
					content = malloc(strlen((site_web + i)->content) * sizeof(char) + 1);
					strcpy(content, (site_web + i)->content); //facem o copie a continutului site-ului i

					if (check_word_in_string(content, word)) //verificam daca apare cuvantul in site
					{

						aparitii[j] = i; //notam site-ul care contine cuvantul
						int ok = 0;
						for (int k = 0; k < j; k++)
						{
							if (aparitii[k] == i)
								ok = 1;
						} //verificam daca este deja notat site-ul
						if (ok == 0)
						{
							aparitii[j] = i; //notam site-ul care contine cuvantul
							j++;
						}
					}
					free(content);
				}

				word = strtok(NULL, " "); //analizam urmatorul cuvant
			}
			//pentru cuvintele simple

			char sequence[20];

			strcpy(copie_input, input);

			if (strstr(copie_input, "\"") != NULL)
			{
				strcpy(copie_input, input);
				find_sequence(copie_input, sequence);
				for (i = 0; i < n; i++)
				{
					content = malloc(strlen((site_web + i)->content) * sizeof(char) + 1);
					strcpy(content, (site_web + i)->content); //facem o copie a continutului site-ului i

					if (strstr(content, sequence) != NULL)
					{
						aparitii[j] = i; //notam site-ul care contine cuvantul
						int ok = 0;
						for (int k = 0; k < j; k++)
						{
							if (aparitii[k] == i)
								ok = 1;
						} //verificam daca este deja notat site-ul
						if (ok == 0)
						{
							aparitii[j] = i; //notam site-ul care contine cuvantul
							j++;
						}
					}

					free(content);
				}
			}

			// pentru secvente
			char word_excluded[20];


			int pozitii_removed;
			pozitii_removed = 0;
			strcpy(copie_input, input);

			if (strstr(copie_input, "-") != NULL)
			{
				strcpy(copie_input, input);
				find_excluded_word(copie_input, word_excluded);
				for (i = 0; i < n; i++)
				{
					content = malloc(strlen((site_web + i)->content) * sizeof(char) + 1);
					strcpy(content, (site_web + i)->content); //facem o copie a continutului site-ului i

					if (check_word_in_string(content, word_excluded)) //daca exista cuvantul in site vom parcurge aparitii si vom elimina site-ul din vector
					{
						for (int k = 0; k < j; k++)
							if (aparitii[k] == i) //daca site-ul care contine cuvantul este notat in aparitii
							{
								remove_position_from_vector(aparitii, k, j);
								j--;
								pozitii_removed++;
							}
					}

					free(content);
				}
			}
			//eliminam site-urile care contin excluded word
			free(copie_input);
			ordonare_task3(site_web, aparitii, j);

			//task3


			int linie_curenta, nr_site_afisate;
			linie_curenta = 0;
			nr_site_afisate = j;
			if (nr_site_afisate == 0) //daca nu exista site-uri
			{
				printw("Nu exista site-uri care contin cuvantul %s. Apasati orice tasta pentru a inchide browserul", input);
				getch();
				for (i = 0; i < n; i++)
				{
					free((site_web + i)->content);
					free((site_web + i)->cod_html);
				}
				free(site_web); //eliberam memoria
				free(word);
				endwin();
				return 0;
			}

			ITEM** items;
			int choice3;
			MENU* menu;
			ITEM* cur_item;
			//declarare elemente pentru meniu


			keypad(stdscr, TRUE);
			//enable pentru tastele KEY_UP, KEY_DOWN

			items = (ITEM**)calloc(nr_site_afisate + 1, sizeof(ITEM*));
			for (i = 0; i < nr_site_afisate; ++i)
				items[i] = new_item((site_web + aparitii[i])->url, (site_web + aparitii[i])->title);
			items[nr_site_afisate] = (ITEM*)NULL;
			//creare itemi meniu

			noecho();
			menu = new_menu((ITEM**)items);
			menu_opts_off(menu, O_ONEVALUE);
			post_menu(menu);
			//creare si afisare meniu cu itemii initializati anterior

			attron(A_STANDOUT);
			move(linii - 3, 0);
			printw("Legenda");
			move(linii - 2, 0);
			printw("Apasati Q pentru a inchide browserul");
			move(linii - 1, 0);
			printw("Apasati ENTER pentru a selecta un site");
			attroff(A_STANDOUT);
			//legenda

			refresh();
			while ((choice3 = getch()) != 'Q')
			{
				switch (choice3)
				{
				case KEY_DOWN: //scroll in jos in meniu
					menu_driver(menu, REQ_DOWN_ITEM);
					break;
				case KEY_UP: //scroll in sus in meniu
					menu_driver(menu, REQ_UP_ITEM);
					break;
				case ' ': //face highlight pe un item din meniu
					menu_driver(menu, REQ_TOGGLE_ITEM);
					break;
				case 10: //optiunea ENTER - selecteaza un item din meniu
					curs_set(0);
					clear();

					attron(A_STANDOUT);
					move(linii - 3, 0);
					printw("Legenda:");
					move(linii - 2, 0);
					printw("Apasati Q pentru a parasi browserul");
					move(linii - 1, 0);
					printw("Apasati B pentru a reveni la pagina de rezultate");
					attroff(A_STANDOUT);
					//legenda

					refresh();
					char link[30];
					int site_de_afisat;
					strcpy(link, item_name(current_item(menu)));
					for (i = 0; i < nr_site_afisate; i++)
						if (strcmp(link, (site_web + aparitii[i])->url) == 0)
							site_de_afisat = aparitii[i];
					//selectam site-ul curent

					start_color();
					init_pair(site_de_afisat, (site_web + site_de_afisat)->text_color, (site_web + site_de_afisat)->background_color);
					//initializam culorile

					mvprintw(0, (coloane - strlen((site_web + site_de_afisat)->title)) / 2, "%s", (site_web + site_de_afisat)->title);
					//titlu

					attron(COLOR_PAIR(site_de_afisat));
					move(6, 0);
					printw("%s", (site_web + site_de_afisat)->content);
					attroff(COLOR_PAIR(site_de_afisat));
					//continutul

					pos_menu_cursor(menu);
					break;
				case 'Q': //opiunea QUIT - inchide programul
				{
					for (i = 0; i < n; i++)
					{
						free((site_web + i)->content);
						free((site_web + i)->cod_html);
					}
					free(site_web);
					unpost_menu(menu);
					for (i = 0; i < nr_site_afisate; ++i)
						free_item(items[i]);
					free_menu(menu);
					endwin(); //dealocam memoria si oprim modul curses
					return 0;
				}
				break;
				case 'B': //optiunea BACK - intoarce utilizatorul la pagina cautarii
				{
					unpost_menu(menu);
					clear();
					refresh();
					post_menu(menu);
					refresh();
					attron(A_STANDOUT);
					move(linii - 3, 0);
					printw("Legenda");
					move(linii - 2, 0);
					printw("Apasati Q pentru a inchide browserul");
					move(linii - 1, 0);
					printw("Apasati ENTER pentru a selecta un site");
					attroff(A_STANDOUT);
					//legenda
				}
				break;
				}
			}
			for (i = 0; i < n; i++)
			{
				free((site_web + i)->content);
				free((site_web + i)->cod_html);
			}
			free(site_web);
			unpost_menu(menu);
			for (i = 0; i < nr_site_afisate; ++i)
				free_item(items[i]);
			free_menu(menu);
			endwin();
			refresh();


		}
		clear();
		refresh();
	}
	endwin();
	return 0;
}
