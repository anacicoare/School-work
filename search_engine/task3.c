#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct site {
	char url[50], title[50], checksum[10], nr_access[10], lung_octeti[10], * continut, * cod_html;
}site;
int check_word_in_string(char* str, char* word) {

	int i, j, flag, n, m;
	n = strlen(str);	// lungimea sirului
	m = strlen(word);	// lungimea cuvantului


	if (m > n)
		return 0;
	// daca lungimea cuvantului e mai mare decat lungimea sirului, atunci sirul nu poate contine cuvantul
	i = 0;
	while (i < n) {

		// vom verifica daca urmatorul cuvant este egal sau nu cu word
		j = 0;
		while (i < n && j < m && tolower(str[i]) == tolower(word[j])) {
			i++;
			j++;
		}

		if ((i == n || str[i] == ' ' || str[i] == ',' || str[i] == '!' || str[i] == '?' || str[i] == '.' || str[i] == ':' || str[i] == ';' || str[i] == '\n') && j == m)
			return 1;

		// daca j != m atunci cuvantul nu este egal cu word, deci continuam cautarea
		while (i < n && str[i] != ' ' && str[i] != ',' && str[i] != '!' && str[i] != '?' && str[i] != '.' && str[i] != ':' && str[i] != ';' && str[i] != '\n')
		{
			i++;
		}
		i++;

	}

	// daca am ajuns aici inseamna ca nu am facut "match pe cuvant", deci acesta nu exista in str
	return 0;

}
void find_excluded_word(char* str_from, char* word)
{
	char* str, * p;
	strcpy(word, "1");
	int n = strlen(str_from);
	str = malloc((n + 1) * sizeof(char));
	strcpy(str, str_from);
	p = strtok(str, "-");
	if (p != NULL)
	{
		p = strtok(NULL, " ");
		strcpy(word, p);
	}
	free(str);
}
void find_sequence(char* str_from, char* sequence)
{
	char* str, * p;
	strcpy(sequence, "1");
	int n = strlen(str_from);
	str = malloc((n + 1) * sizeof(char));
	strcpy(str, str_from);
	p = strtok(str, "\"");
	if (p != NULL)
	{
		p = strtok(NULL, "\"");
		strcpy(sequence, p);
	}
	free(str);
}
void swap(struct site* A, struct site* B)
{
	struct site temp = *A;
	*A = *B;
	*B = temp;
}
void ordonare(struct site* site_web, int aparitii[30], int n)
{
	int i, j, aux;
	long site_i_access, site_j_access;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (char_to_int((site_web + aparitii[i])->nr_access) > char_to_int((site_web + aparitii[j])->nr_access))
			{
				site_i_access = char_to_int((site_web + aparitii[i])->nr_access);
				site_j_access = char_to_int((site_web + aparitii[j])->nr_access);
				aux = aparitii[i];
				aparitii[i] = aparitii[j];
				aparitii[j] = aux;
			}
}
int char_to_int(char* str)
{
	int n, value, i, p;
	n = strlen(str);
	p = 1;
	value = 0;
	for (i = n - 1; i >= 0; i--)
	{
		value = value + (str[i] - '0') * p;
		p = p * 10;
	}
	return value;
}
void remove_position_from_vector(int v[30], int poz, int nr_elemente)
{
	int i;
	for (i = poz; i < nr_elemente - 1; i++)
		v[i] = v[i + 1];
}
int main()
{
	FILE* f;
	int i, n, nr_litere;
	char file_name[30][30], s[80], * p, * cod_html1, * cod_html2;
	site* site_web;



	f = fopen("master.txt", "r");
	n = 0;


	site_web = (struct site*)malloc(3 * sizeof(site));
	n = 0;
	while (fscanf(f, "%s", &file_name[n]) != EOF)
	{
		n++;
		if (n % 3 == 0)
			site_web = (struct site*)realloc(site_web, (n + 3) * sizeof(site));

	}
	fclose(f);
	for (i = 0; i < n; i++)
	{
		f = fopen(file_name[i], "r");
		fscanf(f, "%s", &(site_web + i)->url);
		fscanf(f, "%s", &(site_web + i)->lung_octeti);
		fscanf(f, "%s", &(site_web + i)->nr_access);
		fscanf(f, "%s", &(site_web + i)->checksum);
		fscanf(f, "%s", &s);
		nr_litere = strlen(s);
		(site_web + i)->cod_html = malloc(nr_litere * sizeof(char) + 1);
		strcpy((site_web + i)->cod_html, s);

		while (fgets(s, 80, f) != NULL)
		{
			nr_litere = nr_litere + strlen(s);
			(site_web + i)->cod_html = realloc((site_web + i)->cod_html, nr_litere * sizeof(char) + 1);
			strcat((site_web + i)->cod_html, s);
		}
		cod_html1 = malloc(nr_litere * sizeof(char) + 1);
		strcpy(cod_html1, (site_web + i)->cod_html);
		p = strstr(cod_html1, "<title>");
		p = strtok(p, "<>");
		p = strtok(NULL, "<>");
		strcpy((site_web + i)->title, p);
		cod_html2 = malloc(nr_litere * sizeof(char) + 1);
		strcpy(cod_html2, (site_web + i)->cod_html);
		p = strstr(cod_html2, "<p");
		p = strtok(p, "<>");
		p = strtok(NULL, "<>");
		nr_litere = strlen(p);
		(site_web + i)->continut = malloc(nr_litere * sizeof(char) + 1);
		strcpy((site_web + i)->continut, p);

		fclose(f);
		free(cod_html1);
		free(cod_html2);
	}

	//am introdus site-urile in baza de date

	char input_vector[255], * word, * continut, * input_vector_cuvinte, * copie_input;
	int aparitii[30];


	gets(input_vector);
	int nr_litere_input = strlen(input_vector);

	copie_input = (char*)malloc((nr_litere_input + 1) * sizeof(char));


	strcpy(copie_input, input_vector);
	input_vector_cuvinte = strtok(copie_input, "-\"");
	word = strtok(input_vector_cuvinte, " ");
	int j = 0; //nu avem niciun element in aparitii, unde vom stoca numarul site-urilor care contin cuvinte

	while (word != NULL) //cat timp nu am analizat toate cuvintele
	{
		for (i = 0; i < n; i++)
		{
			continut = malloc(strlen((site_web + i)->continut) * sizeof(char) + 1);
			strcpy(continut, (site_web + i)->continut); //facem o copie a continutului site-ului i

			if (check_word_in_string(continut, word)) //verificam daca apare cuvantul in site
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
			free(continut);
		}

		word = strtok(NULL, " "); //analizam urmatorul cuvant
	}
	//pentru cuvintele simple

	char sequence[20];

	strcpy(copie_input, input_vector);

	if (strstr(copie_input, "\"") != NULL)
	{
		strcpy(copie_input, input_vector);
		find_sequence(copie_input, sequence);
		for (i = 0; i < n; i++)
		{
			continut = malloc(strlen((site_web + i)->continut) * sizeof(char) + 1);
			strcpy(continut, (site_web + i)->continut); //facem o copie a continutului site-ului i

			if (strstr(continut, sequence) != NULL)
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

			free(continut);
		}
	}

	// pentru secvente
	char word_excluded[20];


	int pozitii_removed;
	pozitii_removed = 0;
	strcpy(copie_input, input_vector);

	if (strstr(copie_input, "-") != NULL)
	{
		strcpy(copie_input, input_vector);
		find_excluded_word(copie_input, word_excluded);
		for (i = 0; i < n; i++)
		{
			continut = malloc(strlen((site_web + i)->continut) * sizeof(char) + 1);
			strcpy(continut, (site_web + i)->continut); //facem o copie a continutului site-ului i

			if (check_word_in_string(continut, word_excluded)) //daca exista cuvantul in site vom parcurge aparitii si vom elimina site-ul din vector
			{
				for (int k = 0; k < j; k++)
					if (aparitii[k] == i) //daca site-ul care contine cuvantul este notat in aparitii
					{
						remove_position_from_vector(aparitii, k, j);
						j--;
						pozitii_removed++;
					}
			}

			free(continut);
		}
	}
	//eliminam site-urile care contin excluded word
	free(copie_input);
	ordonare(site_web, aparitii, j);
	for (i = 0; i < j; i++)
		printf("%s\n", (site_web + aparitii[i])->url);

	for (i = 0; i < n; i++)
	{
		free((site_web + i)->continut);
		free((site_web + i)->cod_html);
	}
	free(site_web);

	return 0;
}