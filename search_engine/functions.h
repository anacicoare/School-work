typedef struct site
{
	char url[50], title[50], checksum[10], nr_access[10], lung_octeti[10], * content, * cod_html;
	int background_color, text_color;
}site;
enum colors { black, red, green, yellow, blue, white };
void allocate_memory_for_sites(site* site_web, char file_name[30][30])
{
	FILE* f;
	f = fopen("master.txt", "r");
	int n;

	n = 0; // numarul de site-uri

	while (fscanf(f, "%s", &file_name[n]) != EOF)
	{
		n++;
		if (n % 3 == 0)
			site_web = (struct site*)realloc(site_web, (n + 3) * sizeof(site)); // realocam site-urile
	}
	fclose(f);
}
int number_of_sites()
{
	FILE* f;
	int n;
	char file_name[30];

	n = 0; // numarul de site-uri
	f = fopen("master.txt", "r");

	while (fscanf(f, "%s", &file_name[n]) != EOF)
		n++;
	fclose(f);
	return n;
}
void upload_site_to_database(site* site_web, char file_name[30][30], int i)
{
	char* cod_html1, * cod_html2, * p, s[80];
	int nr_litere;
	FILE* f;

	f = fopen(file_name[i], "r");

	fscanf(f, "%s", &(site_web + i)->url);
	fscanf(f, "%s", &(site_web + i)->lung_octeti);
	fscanf(f, "%s", &(site_web + i)->nr_access);
	fscanf(f, "%s", &(site_web + i)->checksum); //trecem primele elemente in memorie
	fscanf(f, "%s", &s);
	nr_litere = strlen(s);
	(site_web + i)->cod_html = malloc(nr_litere * sizeof(char) + 1);
	strcpy((site_web + i)->cod_html, s);

	while (fgets(s, 80, f) != NULL)
	{
		nr_litere = nr_litere + strlen(s);
		(site_web + i)->cod_html = realloc((site_web + i)->cod_html, nr_litere * sizeof(char) + 1); //alocam dinamic exact dimensiunea continutului
		strcat((site_web + i)->cod_html, s);
	}
	cod_html1 = malloc(nr_litere * sizeof(char) + 1);
	strcpy(cod_html1, (site_web + i)->cod_html);
	p = strstr(cod_html1, "<title>"); //sirul de caractere care incepe cu title
	p = strtok(p, "<>");
	p = strtok(NULL, "<>");
	strcpy((site_web + i)->title, p); //am gasit titlul
	cod_html2 = malloc(nr_litere * sizeof(char) + 1);
	strcpy(cod_html2, (site_web + i)->cod_html);
	p = strstr(cod_html2, "<p"); //sirul care incepe cu <p
	p = strtok(p, "<>");
	p = strtok(NULL, "<>");
	nr_litere = strlen(p);
	(site_web + i)->content = malloc(nr_litere * sizeof(char) + 1);
	strcpy((site_web + i)->content, p); //am gasit continutul

	free(cod_html1);
	free(cod_html2);
	fclose(f);
}
void upload_colors_to_sites(site* site_web, int i)
{
	int nr_litere;
	char* cod_html1, * p;

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
		if (p != NULL)
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
	} //daca nu exista css

	free(cod_html1);
}
void free_database(site* site_web, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		free((site_web + i)->content);
		free((site_web + i)->cod_html);
	}
	free(site_web); //eliberam memoria
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
} //realizeaza trecerea unui numar din tip char in tip int
int check_word_in_string(char* str, char* word)
{
	int i, j, flag, n, m;
	n = strlen(str);	// lungimea sirului
	m = strlen(word);	// lungimea cuvantului

	if (m > n)
		return 0;
	// daca lungimea cuvantului e mai mare decat lungimea sirului, atunci sirul nu poate contine cuvantul
	i = 0;
	while (i < n)
	{
		// vom verifica daca urmatorul cuvant este egal sau nu cu word
		j = 0;
		while (i < n && j < m && str[i] == word[j])
		{
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
void ordonare(struct site* site_web, int aparitii[30], int n, int(*cmp)(char* s1, char* s2))
{
	int i, j, aux;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			if (cmp((site_web + aparitii[i])->content, (site_web + aparitii[j])->content) > 0)
			{
				aux = aparitii[i];
				aparitii[i] = aparitii[j];
				aparitii[j] = aux;
			} //ordonam initial dupa content
			if (cmp((site_web + aparitii[i])->title, (site_web + aparitii[j])->title) == 0)
				if (char_to_int((site_web + aparitii[i])->nr_access) < char_to_int((site_web + aparitii[j])->nr_access))
				{
					aux = aparitii[i];
					aparitii[i] = aparitii[j];
					aparitii[j] = aux;
				} //site-urile cu acelasi titlu le ordonam dupa numarul de accesari

		}
}
int cmp_crescator(char* s1, char* s2)
{
	if (strcmp(s1, s2) > 0)
		return 1;
	else
		if (strcmp(s1, s2) == 0)
			return 0;
		else
			return -1;

} //verifica cum sunt 2 siruri dpdv lexico-grafic
int cmp_descrescator(char* s1, char* s2)
{
	if (char_to_int(s1) < char_to_int(s2))
		return 1;
	else
		if (char_to_int(s1) == char_to_int(s2))
			return 0;
		else
			if (char_to_int(s1) > char_to_int(s2))
				return -1;
} //verifica cum sunt 2 siruri de caractere ca numere
int site_exists(site* site_web, int i, int aparitii[30], int size_aparitii)
{
	for (int k = 0; k < size_aparitii; k++)
	{
		if (aparitii[k] == i)
			return 1;
	}
	return 0;
}
void upload_database(site* site_web)
{
	FILE* f;
	int i, n, nr_litere;
	char file_name[30][30], s[80], * p, * cod_html1, * cod_html2;

	allocate_memory_for_sites(site_web, file_name);

	n = number_of_sites();

	for (i = 0; i < n; i++)
		upload_site_to_database(site_web, file_name, i);

	for (i = 0; i < n; i++) //vom trece in memorie enumerarile
		upload_colors_to_sites(site_web, i);
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
void ordonare1(struct site* site_web, int aparitii[30], int n)
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
void remove_position_from_vector(int v[30], int poz, int nr_elemente)
{
	int i;
	for (i = poz; i < nr_elemente - 1; i++)
		v[i] = v[i + 1];
}
int rotl(char c, int d)
{
	d = d % 8;
	int n;
	n = c;
	int biti_rotiti = (n << d) | (n >> (8 - d));
	return biti_rotiti & 255;
} //roteste bitii la stanga
int rotr(char c, int d)
{
	d = d % 8;
	int n;
	n = c;
	int biti_rotiti = (n >> d) | (n << (8 - d));
	return biti_rotiti & 255;
} //roteste bitii la dreapta
int calculate_checksum(site* site_web, int i)
{
	int nr_caractere, j, checksum;
	nr_caractere = strlen((site_web + i)->cod_html);
	checksum = 0;
	for (j = 0; j < nr_caractere; j++)
	{
		if (j % 2 == 0) //pozitie para
		{
			int x = rotl((site_web + i)->cod_html[j], j);
			checksum = checksum ^ x;
		}
		if (j % 2 == 1) //pozitie impara
		{
			int x = rotr((site_web + i)->cod_html[j], j);
			checksum = checksum ^ x;
		}
	}
	return checksum;
}
void ordonare_task3(struct site* site_web, int aparitii[30], int n)
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
} //ordonarea pentru task3
void ordonare_task2(struct site* site_web, int aparitii[30], int n, int(*cmp)(char* s1, char* s2))
{
	int i, j, aux;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			if (cmp((site_web + aparitii[i])->content, (site_web + aparitii[j])->content) > 0)
			{
				aux = aparitii[i];
				aparitii[i] = aparitii[j];
				aparitii[j] = aux;
			}
			if (cmp((site_web + aparitii[i])->title, (site_web + aparitii[j])->title) == 0)
				if (char_to_int((site_web + aparitii[i])->nr_access) < char_to_int((site_web + aparitii[j])->nr_access))
				{
					aux = aparitii[i];
					aparitii[i] = aparitii[j];
					aparitii[j] = aux;
				}

		}
} //ordonarea pentru task2
